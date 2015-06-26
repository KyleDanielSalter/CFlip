#include "CraftingTree.h"
#include <QtMath>
#include "MultiListingCaller.h"
#include "Gw2Currency.h"

CraftingTreeVertex::CraftingTreeVertex(
	qint32 outputItemID,
	std::function<void (RecipeTreeVertex *)> constructFunc,
	qint32 outputQuantityRequired,
	RecipeTreeVertex *parent)
	: RecipeTreeVertex(outputItemID, constructFunc, outputQuantityRequired, parent)
	, craftType(BUY)
	, marketUnitValue(0.0)
	, craftCost(0.0)
{
	if(Gw2ListingsParser::getAPIEndPoint()->checkID(outputItemID)) {
		marketListings = Listings(outputItemID);
		MultiListingCaller::add(outputItemID, marketListings);
	}
}

void CraftingTreeVertex::calculateTree(
	qint32 craftCount,
	QList<QPair<qint32, qint32>> &overflow)
{
	for(auto i : components) {
		qint32 quantityReq, numOverflow;
		CraftingTreeVertex* next = static_cast<CraftingTreeVertex*>(i.first.get());
		quantityReq = craftCount * i.second;
		numOverflow = quantityReq % next->recipe.outputItemCount;
		if(!numOverflow) {
			overflow.append(QPair<qint32, qint32>(next->outputItemID, numOverflow));
			quantityReq += numOverflow;
		}
		next->calculateTree(quantityReq / next->recipe.outputItemCount, overflow);
	}
	if(marketListings.getItemID() != -1)
		marketUnitValue = marketListings.getAveragePrice(Listings::BUYS, craftCount * recipe.outputItemCount);
	totalMarketValue = marketUnitValue * craftCount * recipe.outputItemCount;
	if(vertexType == COMPONENT) {
		bool allChildrenAreLeaves = true;
		for(auto i : components) {
			if(i.first->vertexType != KARMA && i.first->vertexType != TRADING_POST)
				allChildrenAreLeaves = false;
		}
		if(allChildrenAreLeaves) {
			for(auto i : components) {
				CraftingTreeVertex* next = static_cast<CraftingTreeVertex*>(i.first.get());
				if(next->vertexType == TRADING_POST)
					craftCost += next->marketUnitValue * craftCount * i.second;
			}

		} else {
			for(auto i : components) {
				CraftingTreeVertex* next = static_cast<CraftingTreeVertex*>(i.first.get());
				if(next->craftType == BUY)
					craftCost += next->marketUnitValue * craftCount * i.second;
				else {
					qint32 componentCraftCount = qCeil((craftCount * i.second) / next->recipe.outputItemCount);
					craftCost += next->craftCost * componentCraftCount;
				}
			}
		}
		craftType = marketUnitValue * craftCount * outputQuantityRequired < craftCost ? BUY : CRAFT;
	}

}

qint32 CraftingTreeVertex::print() {
	static qint32 tab = 0;
	QString text;
	for(qint32 i = 0; i < tab; ++i)
		text += "\t";
	text += Gw2ItemDB::getItemName(outputItemID);
	if(craftType == BUY) {
		text += " BUY";
		text += " " + Gw2Currency::string()
	}
	tab++;
	for(auto i : components)
		tab += i.first->print();
	if(vertexType == OUTPUT)
		tab = 0;
	return -1;
}

CraftingTreeRoot::CraftingTreeRoot(qint32 outputItemID, qint32 craftCount)
	: CraftingTreeVertex(outputItemID, customConstructFunc)
	, craftCount(craftCount)
{
	MultiListingCaller::load();
	calculateTree(craftCount, overflow);
}

void CraftingTreeRoot::customConstructFunc(RecipeTreeVertex* recipeTreeVertex){
	for(auto i : recipeTreeVertex->recipe.ingredients) {
		QPair<std::shared_ptr<RecipeTreeVertex>, qint32> component;
		component.first = std::shared_ptr<RecipeTreeVertex>(new CraftingTreeVertex(i.first, customConstructFunc, i.second, recipeTreeVertex));
		recipeTreeVertex->components.append(component);
	}
}
