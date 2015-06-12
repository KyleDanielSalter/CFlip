#include "CraftingItem.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QPair>
#include "Gw2ItemDB.h"
#include "Gw2API.h"
#include "MultiListingCaller.h"
#include "Gw2Currency.h"

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
	, vendorValue(-1)
	, costToCraft(0)
	, avgPrice(-1.0)
{
	setTradingAndVendorValues();
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
	, vendorValue(-1)
	, costToCraft(0)
	, avgPrice(-1.0)
{
	setTradingAndVendorValues();
	constructIngredientTree();
}

CraftingItem::~CraftingItem() {
	qDebug() << "Destroying " + QString::number(outputItemID);
	for(auto i : components)
		delete i;
}

qint32 CraftingItem::getOutputItemID() {
	return outputItemID;
}

qint32 CraftingItem::getQuantity() {
	if(type == OUTPUT)
		return quantity * recipe.outputItemCount;
	else
		return quantity;
}

qint32 CraftingItem::getVendorValue() {
	return vendorValue;
}

CraftingItem::ItemType CraftingItem::getType() {
	return type;
}

CraftingItem::OrderType CraftingItem::getBuyMethod() {
	return buyMethod;
}

CraftingItem::OrderType CraftingItem::getSellMethod() {
	return sellMethod;
}

Listings CraftingItem::getListings() {
	return listings;
}

Recipe CraftingItem::getRecipe() {
	return recipe;
}

QList<CraftingItem*> CraftingItem::getComponents() {
	return components;
}


void CraftingItem::setTradingAndVendorValues() {
	QString dataString = Gw2ItemDB::getJsonDataString(outputItemID);
	if(!dataString.isEmpty()) {
		QJsonDocument jsonDoc = QJsonDocument::fromJson(dataString.toUtf8());
		QJsonObject jsonObj = jsonDoc.object();
		vendorValue = jsonObj["vendor_value"].toInt();
	}
	if(Gw2ListingsParser::getAPIEndPoint()->checkID(outputItemID)) {
		listings = Listings(outputItemID);
		MultiListingCaller::add(outputItemID, listings);
	}
}

void CraftingItem::constructIngredientTree() {
	qint32 recipeID = Gw2RecipesParser::getRecipeID(QString::number(outputItemID));
	if(recipeID != -1) {
		recipe = Gw2RecipesParser::getRecipe(QString::number(recipeID));
		for(QPair<qint32, qint32> i : recipe.ingredients)
			components.append(new CraftingItem(i.first, buyMethod, sellMethod, i.second * quantity, false));
	}
	if(type == OUTPUT) {
		MultiListingCaller::load();
		calculateTree();
	}
}

void CraftingItem::calculateTree() {
	//Will continue tree transversal if there is a recipe
	for(auto i : components)
		i->calculateTree();
	//calculate all non root vertexes as if they are leaves
	if(type != OUTPUT) {
		avgPrice = getListingMethodAvgPrice();
		type = avgPrice == -1 ? KARMA : TRADING_POST;
	} else {
		//Returned to root, traverse through the tree to calculate the CTC
		avgPrice = getListingMethodAvgPrice();
		calculateCostToCraft();
	}
}

float CraftingItem::calculateCostToCraft() {
	if(components.size() == 0) {
		if(type == KARMA)
			return 0;
		else if (type == TRADING_POST)
			return avgPrice * quantity;
	} else {
		for(auto i : components)
			costToCraft += i->calculateCostToCraft();
		if(type != OUTPUT) {
			if(costToCraft < avgPrice * quantity) {
				type = COMPONENT;
				return costToCraft;
			} else
				return avgPrice * quantity;
		}
	}
	return costToCraft;
}

qint32 CraftingItem::print() {
	static qint32 tab = 0;
	QString debug;
	QString name = Gw2ItemDB::getItemName(outputItemID);
	QString typeStr;
	qint32 value = 0;
	if(type == OUTPUT) {
		typeStr = "OUTPUT";
		if(costToCraft < avgPrice * quantity) {
			value = costToCraft;
			typeStr += " CRAFT";

		} else {
			value = avgPrice;
			typeStr += " BUY";
		}
	}
	else if(type == COMPONENT) {
		typeStr = "COMPONENT";
		value = costToCraft;
	}
	else if(type == TRADING_POST) {
		typeStr = "TRADING_POST";
		value = avgPrice;
	}
	else if(type == KARMA) {
		typeStr = "KARMA";
		value = 0;
	}
	for(qint32 i = 0; i < tab; ++i)
		debug += "\t";
	debug += QString::number(quantity) + " " + name + " " + typeStr + " " + Gw2Currency::string(value);
	qDebug() << debug;
	tab++;
	for(auto i : components)
		tab -= i->print();
	if(type == OUTPUT)
		tab = 0;
	return 1;
}

void CraftingItem::setQuantity(qint32 num) {
	quantity = num;
	avgPrice = -1;
	costToCraft = 0;
	if(type != OUTPUT)
		type = COMPONENT;
	if(recipe.recipeID != -1) {
		for(qint32 i = 0; i < components.size(); ++i) {
			for(qint32 j = 0; j < recipe.ingredients.size(); ++j) {
				if(recipe.ingredients[j].first = components[i]->getOutputItemID()) {
					components[i]->setQuantity(recipe.ingredients[i].second * quantity);
					break;
				}
			}

		}
	}
	calculateTree();
}

float CraftingItem::getListingMethodAvgPrice() {
	if(listings.getItemID() != -1) {
		if(type == OUTPUT) {
			if(sellMethod == BUY)
				return listings.getAveragePrice(Listings::BUYS, quantity);
			else
				return listings.getAveragePrice(Listings::SELLS, quantity);
		} else {
			if(buyMethod == BUY)
				return listings.getAveragePrice(Listings::BUYS, quantity);
			else
				return listings.getAveragePrice(Listings::SELLS, quantity);
		}
	}
	return -1;
}
