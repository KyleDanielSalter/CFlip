#ifndef RECIPETREE_H
#define RECIPETREE_H

#include <memory>
#include <QList>
#include <QPair>
#include "Gw2RecipesParser.h"

struct RecipeTreeVertex {
	enum VertexType {
		NO_TYPE,
		OUTPUT,
		COMPONENT,
		KARMA,
		TRADING_POST,
	};
	RecipeTreeVertex(
		qint32 outputItemID,
		qint32 outputQuantityRequired,
		RecipeTreeVertex *parent = nullptr);
	qint32 recipeID, outputItemID, outputQuantityRequired;
	RecipeTreeVertex *parent;
	VertexType vertexType;
	Recipe recipe;
	//Second value of pair is quantity required
	QList<QPair<std::shared_ptr<RecipeTreeVertex>, qint32>> components;
	void constructTree();
	qint32 print();
};

class RecipeTreeRoot : private RecipeTreeVertex {
public:
	RecipeTreeRoot(qint32 outputItemID);
	~RecipeTreeRoot();
	void print();
};

#endif // RECIPETREE_H
