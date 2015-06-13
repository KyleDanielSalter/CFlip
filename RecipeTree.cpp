#include "RecipeTree.h"
#include <QDebug>
#include "Gw2RecipeDB.h"
#include "Gw2ItemDB.h"
#include "Gw2ListingsParser.h"

RecipeTreeVertex::RecipeTreeVertex(
	qint32 outputItemID,
	qint32 outputQuantityRequired,
	RecipeTreeVertex *parent)
	: recipeID(Gw2RecipeDB::getRecipeID(outputItemID))
	, outputItemID(outputItemID)
	, outputQuantityRequired(outputQuantityRequired)
	, parent(parent)
	, vertexType(NO_TYPE)

{
	//Check if the recipe is in the DB
	if(recipeID == -1) {
		//Check if the item has a recipe
		recipeID = Gw2RecipesParser::getRecipeID(outputItemID);
		if(recipeID != -1) {
			//Add the recipe to the DB
			recipe = Gw2RecipesParser::getItemRecipe(outputItemID);
			Gw2RecipeDB::add(recipe.jsonString);
			constructTree();
		} else {
			//No recipe for this item. Either a karma item or a trading post item.
			if(Gw2ListingsParser::getAPIEndPoint()->checkID(outputItemID))
				vertexType = TRADING_POST;
			else
				vertexType = KARMA;
		}
	} else {
		recipe = Gw2RecipeDB::getWithRecipeID(recipeID);
		constructTree();
	}
}

void RecipeTreeVertex::constructTree() {
	for(auto i : recipe.ingredients) {
		QPair<std::shared_ptr<RecipeTreeVertex>, qint32> component;
		component.first = std::shared_ptr<RecipeTreeVertex>(new RecipeTreeVertex(i.first, i.second, this));
		components.append(component);
	}
	vertexType = COMPONENT;
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
	qDebug() << text;
	tab++;
	for(auto i : components)
		tab += i.first->print();
	if(vertexType == OUTPUT)
		tab = 0;
	return -1;
}

RecipeTreeRoot::RecipeTreeRoot(qint32 outputItemID)
	: RecipeTreeVertex(outputItemID, 1)
{
	vertexType = OUTPUT;
}

RecipeTreeRoot::~RecipeTreeRoot() {
	components.clear();
}

void RecipeTreeRoot::print() {
	RecipeTreeVertex::print();
}
