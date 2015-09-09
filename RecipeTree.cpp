#include "RecipeTree.h"
#include <QDebug>
#include <QTreeWidgetItem>
#include "Gw2RecipesDB.h"
#include "Gw2ItemDB.h"
#include "Gw2ListingsParser.h"

RecipeTreeVertex::RecipeTreeVertex(
	qint32 outputItemID,
	qint32 outputQuantityRequired,
	RecipeTreeVertex *parent)
	: outputItemID(outputItemID)
	, outputQuantityRequired(outputQuantityRequired)
	, parent(parent)
	, vertexType(parent == nullptr ? OUTPUT : COMPONENT)
{
	init();
	defaultConstruct();
}

RecipeTreeVertex::RecipeTreeVertex(
	qint32 outputItemID,
	std::function<void (RecipeTreeVertex*)> constructFunc,
	qint32 outputQuantityRequired,
	RecipeTreeVertex *parent)
	: outputItemID(outputItemID)
	, outputQuantityRequired(outputQuantityRequired)
	, parent(parent)
	, vertexType(parent == nullptr ? OUTPUT : COMPONENT)
{
	init();
	constructFunc(this);
}

void RecipeTreeVertex::init() {
	//Items that have not been recorded need doing so.
	//Temp recipeID storage variable.
	qint32 recipeID = -1;
	if(!Gw2RecipesDB::containsOutputItemID(outputItemID)) {
		recipeID = Gw2RecipesParser::getRecipeID(outputItemID);
		//If there is a recipe, query the API for it and record it to the DB.
		//If not, then add the record of the item
		if(recipeID != -1) {
			recipe = Gw2RecipesParser::getRecipe(recipeID);
			Gw2RecipesDB::add(recipe);
		} else
			Gw2RecipesDB::add(outputItemID);
	} else {
		//An item can be in the db but not have a recipe, therefore need to check
		recipeID = Gw2RecipesDB::getRecipeID(outputItemID);
		if(recipeID != -1)
			recipe = Gw2RecipesDB::getWithRecipeID(recipeID);
	}
	//Continue building the tree if this vertex has a recipe
	//If this item is a leaf, decide its type
	if(recipeID ==  -1) {
		if(Gw2ListingsParser::getAPIEndPoint()->checkID(outputItemID))
			vertexType = TRADING_POST;
		else
			vertexType = KARMA;
	}
}

void RecipeTreeVertex::defaultConstruct() {
	for(auto i : recipe.ingredients) {
		QPair<std::shared_ptr<RecipeTreeVertex>, qint32> component;
		component.first = std::shared_ptr<RecipeTreeVertex>(new RecipeTreeVertex(i.first, i.second, this));
		component.second = i.second;
		components.append(component);
	}
}

qint32 RecipeTreeVertex::print() {
	static qint32 tab = 0;
	QString text;
	for(qint32 i = 0; i < tab; ++i)
		text += "\t";
	text += Gw2ItemDB::getItemName(outputItemID);
	if(vertexType != OUTPUT)
		text += " #req: " + QString::number(outputQuantityRequired);
	if(recipe.recipeID != -1)
		text += " #output: " + QString::number(recipe.outputItemCount);
	switch(vertexType) {
		case OUTPUT:
			text += " OUTPUT"; break;
		case COMPONENT:
			text += " COMPONENT"; break;
		case KARMA:
			text += " KARMA"; break;
		case TRADING_POST:
			text += " TRADING_POST"; break;
	}
    qDebug().nospace() << text;
	tab++;
	for(auto i : components)
		tab += i.first->print();
	if(vertexType == OUTPUT)
		tab = 0;
	return -1;
}

qint32 RecipeTreeVertex::findN() {
	if(vertexType == OUTPUT) {
		for(auto i : components)
			return i.first->findN();
	} else if(vertexType == COMPONENT) {
		qint32 ret = 1;
		if(outputQuantityRequired % recipe.outputItemCount != 0)
			ret = lcm(outputQuantityRequired, recipe.outputItemCount) / outputQuantityRequired;
		for(auto i : components)
			ret *= i.first->findN();
		return ret;
	}
	return 1;
}

RecipeTreeRoot::RecipeTreeRoot(qint32 outputItemID)
	: RecipeTreeVertex(outputItemID)
{}

RecipeTreeRoot::~RecipeTreeRoot() {
	components.clear();
}

qint32 gcd(qint32 a, qint32 b) {
	for (;;) {
		if (a == 0)
			return b;
		b %= a;
		if (b == 0)
			return a;
		a %= b;
	}
}

qint32 lcm(qint32 a, qint32 b) {
	int temp = gcd(a, b);
	return temp ? (a / temp * b) : 0;
}
