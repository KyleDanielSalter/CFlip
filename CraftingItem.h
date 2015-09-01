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
		KARMA,
	};
	enum OrderType {
		BUY,
		SELL,
	};
	explicit CraftingItem(
		qint32 outputItemID,
		OrderType buyMethod = BUY,		//How items are bought, i.e. post buy order
		OrderType sellMethod = SELL,	//How items are sold, i.e. post sell order
		qint32 quantity = 1,			//Leave 1 if root item
		bool isOutput = true);			//Leave true if root item
	explicit CraftingItem(
		QString outputItemName,
		OrderType buyMethod = BUY,		//How items are bought, i.e. BUY == post buy order
		OrderType sellMethod = SELL,	//How items are sold, i.e. SELL == post sell order
		qint32 quantity = 1,
		bool isOutput = true);			//Leave true if root item
	~CraftingItem();
	qint32 getOutputItemID();
	qint32 getQuantity();
	qint32 getVendorValue();
	ItemType getType();
	OrderType getBuyMethod();
	OrderType getSellMethod();
	Listings getListings();
	Recipe getRecipe();
	QList<CraftingItem*> getComponents();
	void calculateTree();
	float calculateCostToCraft();
	void setQuantity(qint32 num);
	qint32 print();
private:
	qint32 outputItemID, quantity, vendorValue;
	//floats due to average price calculations
	float costToCraft, avgPrice;
	OrderType buyMethod, sellMethod;
    ItemType type;
	Listings listings;
	Recipe recipe;
	QList<CraftingItem*> components;
	void setTradingAndVendorValues();
	void constructIngredientTree();
	float getListingMethodAvgPrice();
};

#endif // CRAFTINGITEM_H
