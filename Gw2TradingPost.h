#ifndef GW2TRADINGPOST_H
#define GW2TRADINGPOST_H

#include <QHash>
#include "Gw2ListingsParser.h"

class Gw2TradingPost {
public:
	static void init();
	static Listings get(qint32 itemID);
private:
	static QHash<qint32, Listings> listingsHash;
};

#endif // GW2TRADINGPOST_H
