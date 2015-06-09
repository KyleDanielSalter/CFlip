#include "Gw2ItemDB.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QTime>
#include "Gw2ItemIDListParser.h"
#include "Gw2ItemsParser.h"
#include "ImageDownloader.h"

QString Gw2ItemDB::path = "data/item.db";
QString Gw2ItemDB::itemsTableScheme =
	"CREATE TABLE ITEMS("
	"ID INT PRIMARY KEY NOT NULL,"
	"NAME TEXT NOT NULL,"
	"ICONURL TEXT,"
	"JSONDATASTRING TEXT NOT NULL);";
QSqlDatabase Gw2ItemDB::db;
QHash<qint32, QString> Gw2ItemDB::idNameHashMap;
QHash<QString, qint32> Gw2ItemDB::nameIDHashMap;
QHash<qint32, QString> Gw2ItemDB::idIconUrlHashMap;
QHash<qint32, QString> Gw2ItemDB::idJsonStringHashMap;

void Gw2ItemDB::init() {
	qDebug() << "Initializing Gw2ItemDB...";
	QTime t; t.start();
	//Check if there is an existing database, if there is not, create one
	QFileInfo dbInfo(path);
	if(dbInfo.exists() && dbInfo.isFile()) {
		db = QSqlDatabase::addDatabase("QSQLITE");
		db.setDatabaseName(path);
		loadCache();
		//if there is something wrong, recreate the db.
		if(!ready())
			create();
	} else
		create();
	qDebug("Time elapsed: %d ms", t.elapsed());
}

void Gw2ItemDB::clear() {
	idNameHashMap.clear();
	nameIDHashMap.clear();
	idIconUrlHashMap.clear();
	idJsonStringHashMap.clear();
}

void Gw2ItemDB::create() {
	format();
	QStringList allIDs = Gw2ItemIDListParser::get();
	QList<Gw2ItemData> allItems;
	//Max number of IDs that can be queried at once is 200
	//List of IDs partitioned into lists of 200 IDs max
	QList<QStringList> partitionedIDLists;
	QStringList partition;
	qint32 partitionIndex = 0;
	qint32 numMaxIndices = 199;
	for(auto i : allIDs) {
		if(partitionIndex > numMaxIndices) {
			partitionIndex = 0;
			partitionedIDLists << partition;
			partition.clear();
		}
		partition << i;
		partitionIndex++;
	}
	//If there are leftover IDs in the partition, add it to the list
	if(!partition.empty())
		partitionedIDLists << partition;

	//Download item data for all IDs
	for(auto i : partitionedIDLists) {
		allItems.append(Gw2ItemsParser::get(i).values());
	}
	//For each item data, load the cache and write to the database.
	for(auto i : allItems) {
		qDebug() << i.id;
		Gw2ItemData item = i;
		idNameHashMap[item.id] = item.name;
		nameIDHashMap[item.name] = item.id;
		idIconUrlHashMap[item.id] = item.iconUrl;
		idJsonStringHashMap[item.id] = item.jsonString;
		QSqlQuery q;
		q.prepare("INSERT INTO ITEMS VALUES(:ID,:NAME,:ICONURL,:JSONSTRING);");
		q.bindValue(":ID", item.id);
		q.bindValue(":NAME", item.name);
		q.bindValue(":ICONURL", item.iconUrl);
		q.bindValue(":JSONSTRING", item.jsonString);
		q.exec();
	}
	db.commit();
	db.close();
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

QString Gw2ItemDB::getIconUrl(qint32 itemID) {
	if(ready())
		return idIconUrlHashMap[itemID];
	else
		qDebug() << "Warning! Attempt to query iconUrl with ID " +
			QString::number(itemID) + "while db is not ready."
			"Returning empty string";
	return "";
}

QString Gw2ItemDB::getIconUrl(QString itemName) {
	if(ready())
		return idIconUrlHashMap[getItemID(itemName)];
	else
		qDebug() << "Warning! Attempt to query iconUrl with ID " + itemName +
			"while db is not ready. Returning empty string";
	return "";
}

QString Gw2ItemDB::getJsonDataString(qint32 itemID) {
	if(ready())
		return idJsonStringHashMap[itemID];
	else
		qDebug() << "Warning! Attempt to query jsonDataString with ID " +
			QString::number(itemID) + "while db is not ready."
			"Returning empty string";
	return "";
}

QString Gw2ItemDB::getJsonDataString(QString itemName) {
	if(ready())
		return idJsonStringHashMap[getItemID(itemName)];
	else
		qDebug() << "Warning! Attempt to query jsonDataString with ID " + itemName +
			"while db is not ready. Returning empty string";
	return "";
}

QHash<qint32, QString> Gw2ItemDB::getIDNameHashMap() {
	if(!ready())
		qDebug() << "Warning! Attempt to return idNameHashMap from item db while db is not ready. Returning empty hashmap.";
	return idNameHashMap;
}

QHash<QString, qint32> Gw2ItemDB::getNameIDHashMap() {
	if(!ready())
		qDebug() << "Warning! Attempt to return nameIDHashMap from item db while db is not ready. Returning empty hashmap.";
	return nameIDHashMap;
}

QHash<qint32, QString> Gw2ItemDB::getIDIconUrlHashMap() {
	if(!ready())
		qDebug() << "Warning! Attempt to return idIconUrlHashMap from item db while db is not ready. Returning empty hashmap.";
	return idIconUrlHashMap;
}

QHash<qint32, QString> Gw2ItemDB::getIDJsonDataStringHashMap() {
	if(!ready())
		qDebug() << "Warning! Attempt to return idJsonStringHashMap from item db while db is not ready. Returning empty hashmap.";
	return idJsonStringHashMap;
}

bool Gw2ItemDB::open() {
	if(!db.isOpen()) {
		db.open();
		if(db.isOpenError()) {
			qDebug() << "Error opening item database. Error string: " + db.lastError().text();
			db.close();
			return false;
		}
		return true;
	}
	qDebug() << "Warning! Attempting to open database while it is already opened.";
	return true;
}


bool Gw2ItemDB::close() {
	if(db.isOpen()) {
		db.close();
		return true;
	}
	qDebug() << "Warning! Attempting to close database while it is already closed.";
	return false;
}

bool Gw2ItemDB::ready() {
	//check if the caches are filled
	if(!(idNameHashMap.isEmpty() &&
		nameIDHashMap.isEmpty() &&
		idIconUrlHashMap.isEmpty() &&
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
	//If the new databased successfully opened, create the item table
	if(open()) {
		QSqlQuery q;
		q.exec(itemsTableScheme);
	}
}

void Gw2ItemDB::loadCache() {
	QFileInfo dbInfo(path);
	if(dbInfo.exists() && dbInfo.isFile() && open()) {
		QSqlQueryModel model;
		model.setQuery("SELECT * FROM ITEMS");
		//Make sure to load the entire db
		while(model.canFetchMore())
			model.fetchMore();
		qint32 rowCount = model.rowCount();
		for(qint32 i = 0; i < rowCount; ++i) {
			QSqlRecord record = model.record(i);
			qint32 id = record.value("ID").toInt();
			QString name = record.value("NAME").toString();
			QString iconUrl = record.value("ICONURL").toString();
			QString jsonDataString = record.value("JSONDATASTRING").toString();
			idNameHashMap[id] = name;
			nameIDHashMap[name] = id;
			idIconUrlHashMap[id] = iconUrl;
			idJsonStringHashMap[id] = jsonDataString;
		}
	} else
		qDebug() << "Error loading database into cache. Database is not opened or does not exist";
	close();
}
