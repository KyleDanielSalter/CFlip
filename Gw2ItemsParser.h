#ifndef GW2ITEMSPARSER_H
#define GW2ITEMSPARSER_H

#include <QHash>
#include <QStringList>

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
	static Gw2ItemData get(QString itemID);
	static QHash<qint32, Gw2ItemData> get(QStringList itemIDs);
private:
	static QString singleItemURIStr, multiItemURIStr;
};

#endif // GW2ITEMSPARSER_H
