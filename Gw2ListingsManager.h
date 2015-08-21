#ifndef GW2LISTINGSMANAGER_H
#define GW2LISTINGSMANAGER_H

#include <QHash>
#include "Gw2ListingsParser.h"

class Gw2ListingsManager {
public:
	static void add(qint32 itemID);
	static Listings get(qint32 itemID);
	static Listings forceGet(qint32 itemID);
	static void load();
	static void clear();
	static void clearIDList();
	static void clearHash();
	static void refresh();
private:
	static QHash<qint32, Listings> itemIDListingsHash;
	static QList<qint32> idList;
};

#endif // GW2LISTINGSMANAGER_H
