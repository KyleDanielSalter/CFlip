#include "Gw2ItemDB.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include "Gw2ItemIDListParser.h"
#include "Gw2ItemsParser.h"
#include "ImageDownloader.h"

QString Gw2ItemDB::path = "data/item.db";
QString Gw2ItemDB::scheme =
	"CREATE TABLE ITEMS("
	"ID INT PRIMARY KEY NOT NULL,"
	"NAME TEXT NOT NULL,"
	"ICON BLOB,"
	"JSONDATASTRING TEXT NOT NULL);";
QSqlDatabase Gw2ItemDB::db;
QHash<qint32, QString> Gw2ItemDB::idNameHashMap;
QHash<QString, qint32> Gw2ItemDB::nameIDHashMap;
QHash<qint32, QPixmap> Gw2ItemDB::idIconHashMap;
QHash<qint32, QString> Gw2ItemDB::idJsonStringHashMap;

void Gw2ItemDB::init() {
	//Check if there is an existing database, if there is not, create one
	QFileInfo dbInfo(path);
	if(dbInfo.exists() && dbInfo.isFile()) {
		loadCache();
		//if there is something wrong, recreate the db.
		if(!ready()) {
			create();
		}
	} else {
		create();
	}
}

void Gw2ItemDB::create() {
	format();
	QStringList allIDs = Gw2ItemIDListParser::get();
	QList<Gw2ItemData> allItemData = Gw2ItemsParser::get(allIDs);
	ImageDownloader iconDownloader;
	for(auto i : allItemData) {
		qDebug() << QString::number(i.id);
		idNameHashMap[i.id] = i.name;
		nameIDHashMap[i.name] = i.id;
		//Get image as a byte array to make the QPixmap and to store to database
		QByteArray iconByteArray = iconDownloader.getImageAsByteArray(i.iconUrl);
		QPixmap icon(iconByteArray);
		idIconHashMap[i.id] = icon;
		idJsonStringHashMap[i.id] = i.jsonString;
		QSqlQuery q;
		q.prepare("INSERT INTO ITEMS VALUES(:ID,:NAME:,:ICON,:JSONSTRING");
		q.bindValue(":ID", i.id);
		q.bindValue(":NAME", i.name);
		q.bindValue(":ICON", iconByteArray);
		q.exec();
	}
}

QString Gw2ItemDB::getItemName(qint32 itemID) {
	if(ready())
		return idNameHashMap[itemID];
	else
		qDebug() << "Warning! Attempt to query itemID with ID " +
			QString::number(itemID) + "while db is not ready."
			"Returning empty string";
	return "";
}

qint32 Gw2ItemDB::getItemID(QString itemName) {
	if(ready())
		return nameIDHashMap[itemName];
	else
		qDebug() << "Warning! Attempt to query itemID with name " + itemName +
			"while db is not ready. Returning -1";
	return -1;
}

bool Gw2ItemDB::ready() {
	//check if database is opened and caches are filled.
	if(
		db.isOpen() &&
		!(idNameHashMap.isEmpty() &&
		nameIDHashMap.isEmpty() &&
		idIconHashMap.isEmpty() &&
		idJsonStringHashMap.isEmpty()))
		return true;
	else
		return false;
}

void Gw2ItemDB::format() {
	//Check if an existing database file exists, if true then delete it
	QFileInfo dbInfo(path);
	if(dbInfo.exists() && dbInfo.isFile()) {
		QFile dbFile(path);
		if(!dbFile.remove())
			qDebug() << "Error deleting item database file: " + dbFile.errorString();
	}
	//Create a new DB
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(path);
	if(db.open()) {
		QSqlQuery q;
		q.exec(scheme);
	}
}

void Gw2ItemDB::loadCache() {
	if(ready()) {

	}
}
