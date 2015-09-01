#include "Gw2ItemsParser.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

QString Gw2ItemsParser::singleItemURIStr = "items/";
QString Gw2ItemsParser::multiItemURIStr = "items?ids=";
Gw2API Gw2ItemsParser::singleItemAPIEndPoint(singleItemURIStr);
Gw2API Gw2ItemsParser::multiItemAPIEndPoint(multiItemURIStr);

Gw2ItemData::Gw2ItemData()
	: id(-1)
{}

Gw2ItemData Gw2ItemsParser::get(qint32 itemID) {
	return get(QString::number(itemID));
}

Gw2ItemData Gw2ItemsParser::get(QString itemID) {
	singleItemAPIEndPoint.setParams(itemID);
	Gw2ItemData ret;
	QString dataString = singleItemAPIEndPoint.get();
	if(!dataString.isEmpty()) {
		ret.jsonString = dataString;
		QJsonDocument jsonDoc = QJsonDocument::fromJson(dataString.toUtf8());
		QJsonObject jsonObj = jsonDoc.object();
		ret.id = jsonObj["id"].toInt();
		ret.name = jsonObj["name"].toString();
		ret.iconUrl = jsonObj["icon"].toString();
	} else
		qDebug() << "Warning! Error getting gw2 item info for itemID: " + itemID;
	return ret;
}

QHash<qint32, Gw2ItemData> Gw2ItemsParser::get(QList<qint32> itemIDs) {
	return get(Gw2API::intIDListToStringList(itemIDs));
}

QHash<qint32, Gw2ItemData> Gw2ItemsParser::get(QStringList itemIDs) {
	multiItemAPIEndPoint.setParams(itemIDs.join(','));
	QHash<qint32, Gw2ItemData> retHash;
	QString dataString = multiItemAPIEndPoint.get();
	if(!dataString.isEmpty()) {
		QJsonDocument jsonDoc = QJsonDocument::fromJson(dataString.toUtf8());
		QJsonArray array = jsonDoc.array();
		for(QJsonValue val : array) {
			Gw2ItemData ret;
			QJsonObject jsonObj = val.toObject();
			ret.jsonString = QJsonDocument(jsonObj).toJson();
			ret.id = jsonObj["id"].toInt();
			ret.name = jsonObj["name"].toString();
			ret.iconUrl = jsonObj["icon"].toString();
			retHash[ret.id] = ret;
		}
	} else
		qDebug() << "Warning! Error getting gw2 item info for itemIDs: " + itemIDs.join(',');
	return retHash;
}

Gw2API* Gw2ItemsParser::getAPIEndPoint() {
	return &singleItemAPIEndPoint;
}
