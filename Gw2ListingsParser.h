#ifndef GW2LISTINGSPARSER_H
#define GW2LISTINGSPARSER_H

#include <QStringList>
#include <QList>
#include <QHash>
#include <QJsonObject>

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
private:
	qint32 itemID;
	QHash<ListingType, QList<Order> > ordersHash;
};


class Gw2ListingsParser {
public:
	static Listings get(QString itemID);
	static QHash<qint32, Listings> get(QStringList itemIDs);
	static bool isValidItemID(qint32 itemID);
	static QList<qint32> getPossibleIDs();
	static void loadPossibleIDs();
private:
	static QString singleListingURIStr, multiListingURIStr;
	static QList<qint32> possibleIDs;
	static Listings extract(QJsonObject jsonObj);

};

#endif // GW2LISTINGSPARSER_H
