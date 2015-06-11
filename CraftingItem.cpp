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
	, costToCraft(-1.0)
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
	, costToCraft(-1.0)
	, avgPrice(-1.0)
{
	setTradingAndVendorValues();
	constructIngredientTree();
}

CraftingItem::~CraftingItem() {
	qDebug() << "Destroying " +QString::number(outputItemID);
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

float CraftingItem::getOptimalValue() {
	return 0;
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
		Recipe recipe = Gw2RecipesParser::getRecipe(QString::number(recipeID));
		for(QPair<qint32, qint32> i : recipe.ingredients)
			components.append(new CraftingItem(i.first, buyMethod, sellMethod, i.second, false));
	}
	if(type == OUTPUT) {
		MultiListingCaller::load();
		calculateTree();
	}
}

void CraftingItem::optimizeTree() {
	/*//If there is no vendor value, vendor value = -1
	//If there is no listing, avgPrice = -1
	//if there all are -1/no recipe, this is a karma item
	avgPrice = getListingMethodAvgPrice();
	if(type != OUTPUT) {
		//If there is a recipe, reset the CTC
		if(recipe.recipeID != -1) {
			costToCraft = 0;
			//sum the CTC
			for(auto i : components)
				costToCraft += i.getOptimalValue();
			//If there are no listings or a vendor value, crafting is the best
			if(avgPrice == -1) {
				if(vendorValue == -1)
					type = COMPONENT;
				//if there is a vendor, type is now the best of the CTC and vendor
				else
					type = costToCraft < vendorValue ? COMPONENT : VENDOR;
			} else {
				//There is a listing, if no vendor, best of listing and CTC
				if(vendorValue == -1)
					type = costToCraft < avgPrice ? COMPONENT : TRADING_POST;
				//there is all 3, compare all
				else {
					if(costToCraft < avgPrice && costToCraft < vendorValue)
						type = COMPONENT;
					else
						type = avgPrice < vendorValue ? TRADING_POST : VENDOR;
				}
			}
		}
		//No recipe, so it is either a vendor, trading post, or karma item
		if(listings.getItemID() == -1) {
			if(vendorValue == -1)
				type = KARMA;
			else
				type = VENDOR;
		}
		//Use the best price of the vendor or listing
		type = avgPrice < vendorValue ? TRADING_POST : VENDOR;
	}*/
}

float CraftingItem::calculateCTC() {
	if(components.size() == 0) {
		if(type == KARMA)
			return 0;
		else if (type == VENDOR)
			return vendorValue;
		else if (type == TRADING_POST)
			return avgPrice;
	} else {
		float ret = 0;
		for(auto i : components)
			ret += i->calculateCTC() * i->getQuantity();
		return ret;
	}
	return 0;
}

void CraftingItem::calculateTree() {
	//Will continue tree transversal if there is a recipe
	for(auto i : components)
		i->calculateTree();
	//calculate all non root vertexes as if they are leaves
	if(type != OUTPUT) {
		avgPrice = getListingMethodAvgPrice();
		if(avgPrice != -1 && vendorValue != -1) {
			type = avgPrice < vendorValue ? TRADING_POST : VENDOR;
		}
		else if(avgPrice == -1 && vendorValue == -1)
			type = KARMA;
		else if(avgPrice == -1)
			type = KARMA;
	} else {
		//Returned to root, traverse through the tree to calculate the CTC
		costToCraft = calculateCTC();
	}
}

float CraftingItem::getListingMethodAvgPrice() {
	if(listings.getItemID() != -1) {
		if(type == OUTPUT) {
			if(sellMethod == BUY)
				return listings.getAveragePrice(Listings::BUYS, quantity * recipe.outputItemCount);
			else
				return listings.getAveragePrice(Listings::SELLS, quantity * recipe.outputItemCount);
		} else {
			if(buyMethod == BUY)
				return listings.getAveragePrice(Listings::BUYS, quantity);
			else
				return listings.getAveragePrice(Listings::SELLS, quantity);
		}
	}
	return -1;
}
