#ifndef CRAFTINGITEM_H
#define CRAFTINGITEM_H

#include <QString>
#include <QList>
#include <memory>
#include "Gw2ListingsParser.h"
#include "Gw2RecipesParser.h"

class CraftingItem {
public:
	enum ItemType {
		OUTPUT,			//root
		COMPONENT,		//internal vertex
		TRADING_POST,	//leaf
		VENDOR,			//leaf
	};
	enum OrderType {
		BUY,
		SELL,
	};

	explicit CraftingItem(
		qint32 outputItemID,
		OrderType buyMethod,	//How items are bought, i.e. post buy order
		OrderType sellMethod,	//How items are sold, i.e. post sell order
		qint32 quantity = 1,
		bool isOutput = true);
	explicit CraftingItem(
		QString outputItemName,
		OrderType buyMethod,	//How items are bought, i.e. BUY == post buy order
		OrderType sellMethod,	//How items are sold, i.e. SELL == post sell order
		qint32 quantity = 1,
		bool isOutput = true);

private:
	qint32 outputItemID, quantity, vendorValue;
	//floats due to average price calculations
	Listings outputItemListings;
	ItemType type;
	OrderType buyMethod, sellMethod;
	QList<CraftingItem> components;

	void setTradingAndVendorValues();
	void constructIngredientTree();

};

#endif // CRAFTINGITEM_H
