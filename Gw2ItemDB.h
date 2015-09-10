#ifndef GW2ITEMDB_H
#define GW2ITEMDB_H

#include <QSqlDatabase>
#include <QHash>
#include <QString>
#include <QPixmap>

class Gw2ItemDB {
public:
	static void init();
	static void clear();
	static void create();
	static QString getItemName(qint32 itemID);
	static qint32 getItemID(QString itemName);
	static QString getIconUrl(qint32 itemID);
	static QString getIconUrl(QString itemName);
	static QString getJsonDataString(qint32 itemID);
	static QString getJsonDataString(QString itemName);
	static QHash<qint32, QString> getIDNameHashMap();
	static QHash<QString, qint32> getNameIDHashMap();
	static QHash<qint32, QString> getIDIconUrlHashMap();
	static QHash<qint32, QString> getIDJsonDataStringHashMap();
private:
	static QString path;
	static QString itemsTableScheme;
	static QSqlDatabase db;
	static QHash<qint32, QString> idNameHashMap;
	static QHash<QString, qint32> nameIDHashMap;
	static QHash<qint32, QString> idIconUrlHashMap;
	static QHash<qint32, QString> idJsonStringHashMap;
	static bool open();
	static bool close();
	static bool ready();
	static void format();
	static void loadCache();
};

#endif // GW2ITEMDB_H
