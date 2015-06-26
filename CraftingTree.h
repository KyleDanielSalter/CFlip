#ifndef CRAFTINGTREE_H
#define CRAFTINGTREE_H

#include <functional>
#include <QList>
#include "RecipeTree.h"
#include "Gw2ListingsParser.h"

struct CraftingTreeVertex : public RecipeTreeVertex {
	enum CraftType {
		BUY,
		CRAFT,
	};
	CraftingTreeVertex(
		qint32 outputItemID,
		std::function<void (RecipeTreeVertex*)> constructFunc,
		qint32 outputQuantityRequired = 1,
		RecipeTreeVertex* parent = nullptr);
	float marketUnitValue, craftCost;
	CraftType craftType;
	Listings marketListings;
	//overflow.first = outputItemID, overflow.second = quantity
	void calculateTree(qint32 craftCount, QList<QPair<qint32, qint32>> &overflow);
	QList<CraftingTreeVertex*> getOverflow();
	virtual qint32 print();
};

class CraftingTreeRoot : private CraftingTreeVertex {
public:
	CraftingTreeRoot(qint32 outputItemID, qint32 craftCount = 1);
private:
	qint32 craftCount;
	QList<QPair<qint32, qint32>> overflow;
	static void customConstructFunc(RecipeTreeVertex* recipeTreeVertex);
};

#endif // CRAFTINGTREE_H
