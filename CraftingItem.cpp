#include "CraftingItem.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QPair>
#include "Gw2ItemDB.h"

CraftingItem::CraftingItem(
	qint32 outputItemID,
	OrderType buyMethod,
	OrderType sellMethod,
	qint32 quantity,
	bool isOutput)
	: outputItemID(outputItemID)
	, buyMethod(buyMethod)
	, sellMethod(sellMethod)
	, quantity(quantity)
	, type(isOutput ? OUTPUT : COMPONENT)
	, vendorValue(0)
{
	//setTradingAndVendorValues();
	constructIngredientTree();
}

CraftingItem::CraftingItem(
	QString outputItemName,
	OrderType buyMethod,
	OrderType sellMethod,
	qint32 quantity,
	bool isOutput)
	: outputItemID(Gw2ItemDB::getItemID(outputItemName))
	, buyMethod(buyMethod)
	, sellMethod(sellMethod)
	, quantity(quantity)
	, type(isOutput ? OUTPUT : COMPONENT)
	, vendorValue(0)
{
	//setTradingAndVendorValues();
	constructIngredientTree();
}

void CraftingItem::setTradingAndVendorValues() {
	QString dataString = Gw2ItemDB::getJsonDataString(outputItemID);
	if(!dataString.isEmpty()) {
		QJsonDocument jsonDoc = QJsonDocument::fromJson(dataString.toUtf8());
		QJsonObject jsonObj = jsonDoc.object();
		vendorValue = jsonObj["vendor_value"].toInt();
	} else {
		qDebug() << "Error getting vendor value from itemDB with id " + QString::number(outputItemID);
	}
	if(Gw2ListingsParser::isValidItemID(outputItemID)) {
		outputItemListings = Gw2ListingsParser::get(QString::number(outputItemID));
		//Will be reused.
		/*if(outputItemListings.getItemID() != -1) {
			if(type == OUTPUT) {
				if(sellMethod == BUY)
					tradingPostValue = outputItemListings.getAveragePrice(Listings::BUYS, quantity);
				else
					tradingPostValue = outputItemListings.getAveragePrice(Listings::SELLS, quantity);
			} else {
				if(buyMethod == BUY)
					tradingPostValue = outputItemListings.getAveragePrice(Listings::BUYS, quantity);
				else
					tradingPostValue = outputItemListings.getAveragePrice(Listings::SELLS, quantity);
			}
		} else {
			qDebug() << "Error getting gw2 ItemListings " + QString::number(outputItemID);
		}*/
	}
}

void CraftingItem::constructIngredientTree() {
	qint32 recipeID = Gw2RecipesParser::getRecipeID(QString::number(outputItemID));
	if(recipeID != -1) {
		Recipe recipe = Gw2RecipesParser::getRecipe(QString::number(recipeID));
		for(QPair<qint32, qint32> i : recipe.ingredients)
			components.append(CraftingItem(i.first,buyMethod, sellMethod, i.second, false));
	}
}
