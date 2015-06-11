#include "Gw2ListingsParser.h"
#include <qDebug>
#include <utility>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

QString Gw2ListingsParser::singleListingURIStr = "commerce/listings/";
QString Gw2ListingsParser::multiListingURIStr = "commerce/listings?ids=";
Gw2API Gw2ListingsParser::singleListingAPIEndPoint(singleListingURIStr);
Gw2API Gw2ListingsParser::multiListingAPIEndPoint(multiListingURIStr);

Listings::Listings()
{}

Listings::Listings(qint32 itemID)
	: itemID(itemID)
{}

Listings::Listings(qint32 itemID, QList<Order> buys, QList<Order> sells)
	: itemID(itemID)
	, ordersHash({std::make_pair(BUYS, buys), std::make_pair(SELLS, sells)})
{}

Listings::Order::Order()
	: listings(0)
	, unit_price(0)
	, quantity(0)
{}

Listings::Listings(const Listings &other)
	: itemID(other.getItemID())
	, ordersHash(other.getOrders())
{}

Listings::Order::Order(qint32 listings, qint32 unit_price, qint32 quantity)
	: listings(listings)
	, unit_price(unit_price)
	, quantity(quantity)
{}

qint32 Listings::getItemID() const {
	return itemID;
}

qint32 Listings::getBoundaryPrice(ListingType type) {
	QList<Listings::Order> orderList = ordersHash[type];
	if(!orderList.isEmpty()) {
		return orderList[0].unit_price;
	} else
		qDebug() << "Warning! Attempting to return boundary price of item " + QString::number(itemID) + "when hash is empty.";
	return -1;
}

float Listings::getAveragePrice(ListingType type, qint32 quantity) {
	QList<Listings::Order> orderList = ordersHash[type];
	if(!orderList.isEmpty()) {
		float totalValue(0), totalQuantity(0);
		for(auto i : orderList) {
			if(totalQuantity + i.quantity > quantity) {
				qint32 adjQuantity = quantity - totalQuantity;
				totalQuantity += adjQuantity;
				totalValue += i.unit_price * adjQuantity;
				return totalValue / totalQuantity;
			} else {
				totalQuantity += i.quantity;
				totalValue += i.unit_price;
			}
		}
		return totalValue / totalQuantity;
	} else
		qDebug() << "Warning! Attempting to return avg price of item " + QString::number(itemID) + "when hash is empty.";
	return -1.0;
}

QHash<Listings::ListingType, QList<Listings::Order> > Listings::getOrders() const {
	return ordersHash;
}

Listings Gw2ListingsParser::get(qint32 itemID) {
	return get(QString::number(itemID));
}

Listings Gw2ListingsParser::get(QString itemID) {
	singleListingAPIEndPoint.setParams(itemID);
	QString dataString = singleListingAPIEndPoint.get();
	if(!dataString.isEmpty()) {
		QJsonDocument jsonDoc = QJsonDocument::fromJson(dataString.toUtf8());
		return extract(jsonDoc.object());
	} else
		qDebug() << "Warning! Error getting gw2 listings for itemID: " + itemID;
	return Listings();
}

QHash<qint32, Listings> Gw2ListingsParser::get(QList<qint32> itemIDs) {
	return get(Gw2API::intIDListToStringList(itemIDs));
}

QHash<qint32, Listings> Gw2ListingsParser::get(QStringList itemIDs) {
	multiListingAPIEndPoint.setParams(itemIDs.join(','));
	QHash<qint32, Listings> retHash;
	QString dataString = multiListingAPIEndPoint.get();
	if(!dataString.isEmpty()) {
		QJsonDocument jsonDoc = QJsonDocument::fromJson(dataString.toUtf8());
		QJsonArray jsonArray = jsonDoc.array();
		for(auto i : jsonArray) {
			Listings listings(extract(i.toObject()));
			retHash[listings.getItemID()] = listings;
		}
	} else
		qDebug() << "Warning! Error getting gw2 listings for itemIDs: " + itemIDs.join(',');
	return retHash;
}

Gw2API* Gw2ListingsParser::getAPIEndPoint() {
	return &singleListingAPIEndPoint;
}

Gw2API* Gw2ListingsParser::getMultiAPIEndPoint() {
	return &multiListingAPIEndPoint;
}

Listings Gw2ListingsParser::extract(QJsonObject jsonObj) {
	QList<Listings::Order> buys, sells;
	qint32 id = jsonObj["id"].toInt();
	QJsonArray jsonBuyArray = jsonObj["buys"].toArray(), jsonSellArray = jsonObj["sells"].toArray();
	for(auto i : jsonBuyArray) {
		QJsonObject iObj = i.toObject();
		qint32 listings(iObj["listings"].toInt()),
			unit_price(iObj["unit_price"].toInt()),
			quantity(iObj["quantity"].toInt());
		buys << Listings::Order(listings, unit_price, quantity);
	}
	for(auto i : jsonSellArray) {
		QJsonObject iObj = i.toObject();
		qint32 listings(iObj["listings"].toInt()),
			unit_price(iObj["unit_price"].toInt()),
			quantity(iObj["quantity"].toInt());
		sells << Listings::Order(listings, unit_price, quantity);
	}
	return Listings(id, buys, sells);
}
