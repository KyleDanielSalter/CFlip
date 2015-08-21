#ifndef GW2LISTINGSPARSER_H
#define GW2LISTINGSPARSER_H

#include <QStringList>
#include <QList>
#include <QHash>
#include <QJsonObject>
#include <memory>
#include "Gw2API.h"
#include "Gw2APIParser.h"
#include "Gw2APIResult.h"

class Listings {
public:
	enum ListingType {
		BUYS,
		SELLS,
	};
	struct Order {
		Order();
		Order(qint32 listings, qint32 unit_price, qint32 quantity);
		qint32 listings, unit_price, quantity;
	};
	Listings();
	Listings(const Listings &other);
	Listings(qint32 itemID);
	Listings(qint32 itemID, QList<Order> buys, QList<Order> sells);
	qint32 getItemID() const;
	qint32 getBoundaryPrice(ListingType type);
	float getAveragePrice(ListingType type, qint32 quantity);
	QHash<ListingType, QList<Order> > getOrders() const;
	Listings& operator=(const Listings &rhs);
	static qint32 getListingFee(qint32 value);
	static qint32 getTransactionFee(qint32 value);
	static qint32 getTotalFees(qint32 value);
private:
	qint32 itemID;
	QHash<ListingType, QList<Order> > ordersHash;
};


class Gw2ListingsParser{
public:
	static Listings get(qint32 itemID);
	static Listings get(QString itemID);
	static QHash<qint32, Listings> get(QList<qint32> itemIDs);
	static QHash<qint32, Listings> get(QStringList itemIDs);
	static Gw2API* getAPIEndPoint();
	static Gw2API* getMultiAPIEndPoint();

private:
	static QString singleListingURIStr, multiListingURIStr;
	static Gw2API singleListingAPIEndPoint, multiListingAPIEndPoint;
	static Listings extract(QJsonObject jsonObj);

};

#endif // GW2LISTINGSPARSER_H
