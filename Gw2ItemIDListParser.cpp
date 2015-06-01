#include "Gw2ItemIDListParser.h"
#include "Gw2API.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>

QString Gw2ItemIDListParser::itemIDListURI = "items";

QStringList Gw2ItemIDListParser::get() {
	Gw2API api(itemIDListURI); QStringList ret;
	QString dataString = api.get();
	if(!dataString.isEmpty()) {
		QJsonDocument data = QJsonDocument::fromJson(dataString.toUtf8());
		QJsonArray array = data.array();
		for(auto i : array)
			ret << QString::number(i.toInt());
	} else
		qDebug() << "Warning! Empty string returned from calling Gw2 API items. "
			"Returning empty list.";
	return ret;
}
