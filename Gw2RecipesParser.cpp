#include "Gw2RecipesParser.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "Gw2API.h"

QString Gw2RecipesParser::recipesURIStr = "recipes/";
QString Gw2RecipesParser::recipesSearchURIStr = "recipes/search?input=";

Recipe::Recipe()
	: recipeID(-1)
	, outputID(-1)
	, outputItemCount(-1)
{}

Recipe::Recipe(qint32 recipeID,
	qint32 outputID,
	qint32 outputItemCount,
	QList<QPair<qint32, qint32> > ingredients)
	: recipeID(recipeID)
	, outputID(outputID)
	, outputItemCount(outputItemCount)
	, ingredients(ingredients)
{}

qint32 Gw2RecipesParser::getRecipeID(QString itemID) {
	Gw2API api(recipesSearchURIStr, itemID);
	QString dataString = api.get();
	if(!dataString.isEmpty()) {
		QJsonDocument jsonDoc = QJsonDocument::fromJson(dataString.toUtf8());
		QJsonArray jsonArray = jsonDoc.array();
		return jsonArray.isEmpty() ? -1 : jsonArray[0].toInt();
	} else
		qDebug() << "Warning! Error getting gw2 recipe search for itemIDs: " + itemID;
	return -1;
}

Recipe Gw2RecipesParser::getRecipe(QString recipeID) {
	Gw2API api(recipesURIStr, recipeID);
	QString dataString = api.get();
	if(!dataString.isEmpty()) {
		QJsonDocument jsonDoc = QJsonDocument::fromJson(dataString.toUtf8());
		QJsonObject jsonObj = jsonDoc.object();
		QJsonArray jsonIngredients = jsonObj["ingredients"].toArray();
		QList<QPair<qint32, qint32>> ingredients;
		for(auto i : jsonIngredients) {
			QJsonObject iObj = i.toObject();
			ingredients << QPair<qint32, qint32>(iObj["item_id"].toInt(), iObj["count"].toInt());
		}
		return Recipe(jsonObj["id"].toInt(), jsonObj["output_item_id"].toInt(), jsonObj["output_item_count"].toInt(), ingredients);
	} else
		qDebug() << "Warning! Error getting gw2 recipe for itemIDs: " + recipeID;
	return Recipe();
}

Recipe Gw2RecipesParser::getItemRecipe(QString itemID) {
	return getRecipe(QString::number(getRecipeID(itemID)));
}
