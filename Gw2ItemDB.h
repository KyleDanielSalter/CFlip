#ifndef GW2ITEMDB_H
#define GW2ITEMDB_H

#include <QSqlDatabase>
#include <QHash>
#include <QString>
#include <QPixmap>

class Gw2ItemDB {
public:
	static void init();
	static void create();
	static QString getItemName(qint32 itemID);
	static qint32 getItemID(QString itemName);
private:
	static QString path;
	static QString scheme;
	static QSqlDatabase db;
	static QHash<qint32, QString> idNameHashMap;
	static QHash<QString, qint32> nameIDHashMap;
	static QHash<qint32, QPixmap> idIconHashMap;
	static QHash<qint32, QString> idJsonStringHashMap;

	static bool ready();
	static void format();
	static void loadCache();
};

#endif // GW2ITEMDB_H
