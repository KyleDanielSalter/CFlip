#ifndef GW2ITEMSPARSER_H
#define GW2ITEMSPARSER_H

#include <QHash>
#include <QStringList>
#include "Gw2API.h"

struct Gw2ItemData {
	Gw2ItemData();
	qint32 id;
	QString name;
	QString iconUrl;
	//Contains the rest of the item document
	QString jsonString;
};

class Gw2ItemsParser {
public:
	static Gw2ItemData get(qint32 itemID);
	static Gw2ItemData get(QString itemID);
	static QHash<qint32, Gw2ItemData> get(QList<qint32> itemIDs);
	static QHash<qint32, Gw2ItemData> get(QStringList itemIDs);
	static Gw2API* getAPIEndPoint();
private:
	static QString singleItemURIStr, multiItemURIStr;
	static Gw2API singleItemAPIEndPoint, multiItemAPIEndPoint;
};

#endif // GW2ITEMSPARSER_H
