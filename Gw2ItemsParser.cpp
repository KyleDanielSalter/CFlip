#include "Gw2ItemsParser.h"
#include <qDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "Gw2API.h"

QString Gw2ItemsParser::singleItemURIStr = "/items/";
QString Gw2ItemsParser::multiItemURIStr = "/items?ids=";

Gw2ItemData::Gw2ItemData()
	: id(-1)
{}

Gw2ItemData Gw2ItemsParser::get(QString itemID) {
	Gw2API api(singleItemURIStr, itemID); Gw2ItemData ret;
	QString dataString = api.get();
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

QList<Gw2ItemData> Gw2ItemsParser::get(QStringList itemIDs) {
	Gw2API api(multiItemURIStr, itemIDs.join(','));
	QList<Gw2ItemData> retList;
	QString dataString = api.get();
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
			retList.append(ret);
		}
	} else
		qDebug() << "Warning! Error getting gw2 item info for itemIDs: " + itemIDs.join(',');
	return retList;
}
