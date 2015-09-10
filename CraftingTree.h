#ifndef CRAFTINGTREE_H
#define CRAFTINGTREE_H

#include <functional>
#include <QList>
#include <QHash>
#include "RecipeTree.h"
#include "Gw2ListingsParser.h"

class QTreeWidgetItem;

struct CraftingTreeVertex : public RecipeTreeVertex {
	enum CraftType {
		BUY,	//Optimal to buy this item
		CRAFT,	//Optimal to craft this item
	};
	CraftingTreeVertex(
		qint32 outputItemID,
		std::function<void (RecipeTreeVertex*)> constructFunc,
		qint32 outputQuantityRequired = 1,
		RecipeTreeVertex* parent = nullptr);
	CraftType craftType;
	/*
	 * craftCount is the number of crafts required.
	 * If this item is not a component, craftCount will be 0
	 * quantityReq is the total number of this item required.
	 */
	qint32 craftCount, quantityReq,
	/*
	 * marketUnitValue is the ppu, totalMarketValue is the ppu * quantityReq
	 * totalCraftCost is the sum of the value of its children, dependent
	 * on whether it is more profitable to buy or craft the child.
	 */
	marketUnitValue, totalMarketValue, totalCraftCost;
	Listings marketListings;
	/*
	 * Adjusts the quantity values of the tree based on the quantity required.
	 * overflow is the list of items that are not used in the crafting process.
	 * overflow.first = outputItemID, overflow.second = quantity.
	 */
	void setCount(qint32 count, QList<QPair<qint32, qint32>> &overflow);
	qint32 getCraftCount();
	qint32 getCraftCount(QList<QPair<qint32, qint32>> &countList);
	void calculateTree();
	virtual qint32 print();
	virtual qint32 getProfit();
	void buildQTree(QTreeWidgetItem *parentItem);
	QStringList getTreeColumns();
	//materials.first = itemID, materials.second.first = quantity, materials.second.second = total cost
	void findShoppingList(QHash<qint32, QPair<qint32, qint32>> &materials);
};

class CraftingTreeRoot : private CraftingTreeVertex {
public:
	CraftingTreeRoot(qint32 outputItemID);
	CraftingTreeRoot(qint32 outputItemID, qint32 craftCount);
	void setCount(qint32 count);
	QList<QPair<qint32, qint32>> getOverflow();
	void printTree();
	CraftingTreeVertex* getVertex();
	qint32 getAdjBS();
	//AKA get AdjC/S
	qint32 getProfit();
	std::shared_ptr<QTreeWidgetItem> getQTree();
	QHash<qint32, QPair<qint32, qint32> > getShoppingList();
private:
	QList<QPair<qint32, qint32>> overflow;
	static void customConstructFunc(RecipeTreeVertex* recipeTreeVertex);
};

#endif // CRAFTINGTREE_H
