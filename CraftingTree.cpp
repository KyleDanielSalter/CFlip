#include "CraftingTree.h"
#include <QDebug>
#include <QtMath>
#include <QTreeWidgetItem>
#include "Gw2ListingsManager.h"
#include "Gw2ItemDB.h"
#include "Gw2Currency.h"

CraftingTreeVertex::CraftingTreeVertex(
	qint32 outputItemID,
	std::function<void (RecipeTreeVertex *)> constructFunc,
	qint32 outputQuantityRequired,
	RecipeTreeVertex *parent)
	: RecipeTreeVertex(outputItemID, constructFunc, outputQuantityRequired, parent)
	, craftType(BUY)
	, craftCount(0)
	, quantityReq(0)
	, marketUnitValue(0)
	, totalMarketValue(0)
	, totalCraftCost(0)
{
	Gw2ListingsManager::add(outputItemID);
}

void CraftingTreeVertex::setCount(qint32 count, QList<QPair<qint32, qint32>> &overflow) {
	//If this is a component, count is the number of crafts required
	//Else this is a leaf, and count is only the quantity required (i.e. to buy)
	if(vertexType == COMPONENT || vertexType == OUTPUT) {
		craftCount = count;
		quantityReq = count * recipe.outputItemCount;
	}
	else
		quantityReq = count;
	//Compute the craftCount required or quantity required for each component
	for(auto i : components) {
		qint32 componentQuantity, numOverflow, nextCount;
		CraftingTreeVertex* next = static_cast<CraftingTreeVertex*>(i.first.get());
		//If one of our components is also a component, we need to know how many
		//crafts of this component give us the required quantity
		//Else this is something that needs to bought, therefore only need to
		//know how many to buy
		if(next->vertexType == COMPONENT) {
			componentQuantity = craftCount * i.second;
			//There will be an overflow of materials if we cannot exactly output
			//the required amount, and that must be taken note of or at certain
			//quantities a recipes profitability will be underestimated.
			numOverflow = componentQuantity % next->recipe.outputItemCount;
			if(numOverflow != 0) {
				float exactCount = (float)componentQuantity / (float)next->recipe.outputItemCount;
				numOverflow = (qCeil(exactCount) * next->recipe.outputItemCount) - componentQuantity;
				componentQuantity += numOverflow;
				overflow.append(QPair<qint32, qint32>(next->outputItemID, numOverflow));
			}
			//At this point the integer division is guarenteed to be exact
			nextCount = componentQuantity / next->recipe.outputItemCount;
		} else {
			componentQuantity = craftCount * i.second;
			nextCount = componentQuantity;
		}
		next->setCount(nextCount, overflow);
	}
}

void CraftingTreeVertex::calculateTree() {
	//Calculate the market value based on the quantity required (n/a for output)
	//Note: KARMA items are 0 value items
	//Temp var so recalculation only assigns values to object, not add to.
	qint32 tempCraftCost = 0;
	marketListings = Gw2ListingsManager::get(outputItemID);
	if(marketListings.getItemID() != -1) {
		marketUnitValue = marketListings.getBoundaryPrice(Listings::SELLS);
		totalMarketValue = marketUnitValue * quantityReq;
	}
	//Continue building the tree so that the leaves' values can be calculated.
	for(auto i : components) {
		CraftingTreeVertex* next = static_cast<CraftingTreeVertex*>(i.first.get());
		next->calculateTree();
	}
	//If this is a component or output item, calculate costs from our children
	if(vertexType == COMPONENT || vertexType == OUTPUT) {
		/*
		 * If this is the second to last level of the tree (lv = n-1)
		 * totalCraftCost is determined from the market values only
		 * A vertex is on the second to last level if all of its children
		 * are either trading post or karma items (i.e. leaves)
		 */
		bool isLastComponent = true;
		for(auto i : components) {
			if(i.first->vertexType != TRADING_POST && i.first->vertexType != KARMA)
				isLastComponent = false;
		}
		if(isLastComponent) {
			for(auto i : components) {
				CraftingTreeVertex* next = static_cast<CraftingTreeVertex*>(i.first.get());
				tempCraftCost += next->totalMarketValue;
			}
		} else {
			for(auto i : components) {
				CraftingTreeVertex* next = static_cast<CraftingTreeVertex*>(i.first.get());
				if(next->vertexType == COMPONENT)
					tempCraftCost += next->craftType == BUY ? next->totalMarketValue : next->totalCraftCost;
				else
					tempCraftCost += next->totalMarketValue;
			}
		}
		totalCraftCost = tempCraftCost;
		craftType = totalMarketValue <= totalCraftCost ? BUY : CRAFT;
	}
}

qint32 CraftingTreeVertex::print() {
	static qint32 tab = 0;
	QString text;
	for(qint32 i = 0; i < tab; ++i)
		text += "\t";
	text += Gw2ItemDB::getItemName(outputItemID);
	if(vertexType == COMPONENT)
		text += " COMPONENT craftCount = " + QString::number(craftCount) + " quantityReq = " + QString::number(quantityReq);
	else if(vertexType == OUTPUT)
		text += " ROOT craftCount = " + QString::number(craftCount) + " OutputQuantity = " + QString::number(craftCount * recipe.outputItemCount);
	else
		text += " LEAF quantityReq = " + QString::number(quantityReq);
	if(craftType == BUY) {
		text += vertexType == KARMA ? " KARMA" : " BUY " + Gw2Currency::string(totalMarketValue);
	} else
		text += " CRAFT " + Gw2Currency::string(totalCraftCost);
    qDebug().noquote() << text;
	tab++;
	for(auto i : components)
		tab += i.first->print();
	if(vertexType == OUTPUT)
		tab = 0;
	return -1;
}

qint32 CraftingTreeVertex::getProfit() {
	if(vertexType == COMPONENT || vertexType == OUTPUT) {
		return totalMarketValue - (totalCraftCost + Listings::getTotalFees(totalMarketValue));
	}
	return 0;
}

void CraftingTreeVertex::buildQTree(QTreeWidgetItem *parentItem) {
	QTreeWidgetItem* currentVertex = new QTreeWidgetItem(parentItem, 0);
	QStringList cols = getTreeColumns();
	for(qint32 i = 0; i < cols.size(); ++i)
		currentVertex->setText(i, cols[i]);
	for(auto i : components) {
		CraftingTreeVertex* next = static_cast<CraftingTreeVertex*>(i.first.get());
		next->buildQTree(currentVertex);
	}
}

QStringList CraftingTreeVertex::getTreeColumns() {
	QString itemName = Gw2ItemDB::getItemName(outputItemID),
		craftTypeStr = craftType == BUY ? "Buy" : "Craft",
		costStr = craftType == BUY ? Gw2Currency::string(totalMarketValue) : Gw2Currency::string(totalCraftCost);
	return QStringList({itemName, craftTypeStr, costStr});
}

void CraftingTreeVertex::findShoppingList(QHash<qint32, QPair<qint32, qint32> > &materials) {
	for(auto i : components) {
		CraftingTreeVertex* next = static_cast<CraftingTreeVertex*>(i.first.get());
		if(craftType == CRAFT)
			next->findShoppingList(materials);
	}
	if(craftType == BUY) {
		if(materials.contains(outputItemID)) {
			qint32 tempQuantity = materials.value(outputItemID).first,
				tempValue = materials.value(outputItemID).second;
			materials.insert(outputItemID, QPair<qint32, qint32>(quantityReq + tempQuantity, totalMarketValue + tempValue));
		} else
			materials.insert(outputItemID, QPair<qint32, qint32>(quantityReq, totalMarketValue));
	}
}

CraftingTreeRoot::CraftingTreeRoot(qint32 outputItemID)
	: CraftingTreeVertex(outputItemID, customConstructFunc)
{
	Gw2ListingsManager::load();
	setCount(findN());
}

CraftingTreeRoot::CraftingTreeRoot(qint32 outputItemID, qint32 craftCount)
	: CraftingTreeVertex(outputItemID, customConstructFunc)
{
	Gw2ListingsManager::load();
	setCount(craftCount);
}

void CraftingTreeRoot::setCount(qint32 count) {
	overflow.clear();
	CraftingTreeVertex::setCount(count, overflow);
	calculateTree();
}

QList<QPair<qint32, qint32>> CraftingTreeRoot::getOverflow() {
	return overflow;
}

void CraftingTreeRoot::printTree() {
	CraftingTreeVertex::print();
	QString text;
	if(!overflow.isEmpty())
		text += "Overflow:\n";
	for(auto i : overflow)
		text += Gw2ItemDB::getItemName(i.first) + " Count = " + QString::number(i.second) + "\n";
	text += "Shopping List: \n";
	auto shoppingList = getShoppingList();
	qint32 total = 0;
	for(auto iter = shoppingList.begin(); iter != shoppingList.end(); ++iter) {
		total += iter.value().second;
		text += QString::number(iter.value().first) + " " + Gw2ItemDB::getItemName(iter.key()) + " " + Gw2Currency::string(iter.value().second) + "\n";
	}
	text += "\nMarket Value: " + Gw2Currency::string(totalMarketValue) + "\n";
	text += "Listing and Transaction Fee: " + Gw2Currency::string(Listings::getTotalFees(totalMarketValue)) + "\n";
	text += "Crafting Cost Total: " + Gw2Currency::string(total) + "\n";
	text += "Profit: " + Gw2Currency::string(getProfit());
    qDebug().noquote() << text;
}

CraftingTreeVertex* CraftingTreeRoot::getVertex() {
	return this;
}

void CraftingTreeRoot::customConstructFunc(RecipeTreeVertex* recipeTreeVertex){
	for(auto i : recipeTreeVertex->recipe.ingredients) {
		QPair<std::shared_ptr<RecipeTreeVertex>, qint32> component;
		component.first = std::shared_ptr<RecipeTreeVertex>(new CraftingTreeVertex(i.first, customConstructFunc, i.second, recipeTreeVertex));
		component.second = i.second;
		recipeTreeVertex->components.append(component);
	}
}

qint32 CraftingTreeRoot::getCostToCraft() {
	return totalCraftCost;
}

qint32 CraftingTreeRoot::getAdjBS() {
	qint32 unAdjBS = marketListings.getBoundaryPrice(Listings::SELLS) * quantityReq - marketListings.getBoundaryPrice(Listings::BUYS) * quantityReq;
	return unAdjBS - Listings::getTotalFees(unAdjBS);
}

qint32 CraftingTreeRoot::getProfit() {
	qint32 ret = CraftingTreeVertex::getProfit();
	qint32 overflowValue = 0;
	for(auto i : overflow) {
		Listings overflowListings = Gw2ListingsManager::get(i.first);
		overflowValue += overflowListings.getBoundaryPrice(Listings::SELLS) * i.second;
	}
	return ret + (overflowValue - Listings::getTotalFees(overflowValue));
}

std::shared_ptr<QTreeWidgetItem> CraftingTreeRoot::getQTree()
{
	std::shared_ptr<QTreeWidgetItem> ret(new QTreeWidgetItem(0));
	QStringList cols = getTreeColumns();
	ret->setText(0, cols[0]);
	ret->setText(1, cols[1]);
	ret->setText(2, cols[2]);
	for(auto i : components) {
		CraftingTreeVertex* next = static_cast<CraftingTreeVertex*>(i.first.get());
		next->buildQTree(ret.get());
	}
	return ret;
}

QHash<qint32, QPair<qint32, qint32>> CraftingTreeRoot::getShoppingList(){
	QHash<qint32, QPair<qint32, qint32>> ret;
	findShoppingList(ret);
	return ret;
}
