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
	qint32 outputItemID, outputQuantityRequired;
	RecipeTreeVertex *parent;
	VertexType vertexType;
	Recipe recipe;
	//Second value of pair is quantity required
	QList<QPair<std::shared_ptr<RecipeTreeVertex>, qint32>> components;
	void constructTree();
	qint32 print();
	qint32 findN();
};

class RecipeTreeRoot : public RecipeTreeVertex {
public:
	RecipeTreeRoot(qint32 outputItemID);
	~RecipeTreeRoot();
	void print();
};

qint32 gcd(qint32 a, qint32 b);
qint32 lcm(qint32 a, qint32 b);

#endif // RECIPETREE_H
