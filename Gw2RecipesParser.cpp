#include "Gw2RecipesParser.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

QString Gw2RecipesParser::singleRecipesURIStr = "recipes/";
QString Gw2RecipesParser::multiRecipesURIStr = "recipes?ids=";
QString Gw2RecipesParser::recipesSearchURIStr = "recipes/search?output=";
Gw2API Gw2RecipesParser::singleRecipesAPIEndPoint(singleRecipesURIStr);
Gw2API Gw2RecipesParser::multiRecipeAPIEndPoint(multiRecipesURIStr);
Gw2API Gw2RecipesParser::recipesSearchAPIEndPoint(recipesSearchURIStr);

Recipe::Recipe()
	: recipeID(-1)
	, outputID(-1)
	, outputItemCount(-1)
{}

Recipe::Recipe(const Recipe &other)
	: recipeID(other.recipeID)
	, outputID(other.outputID)
	, outputItemCount(other.outputItemCount)
	, ingredients(other.ingredients)
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

qint32 Gw2RecipesParser::getRecipeID(qint32 itemID) {
	return getRecipeID(QString::number(itemID));
}

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

Recipe Gw2RecipesParser::getRecipe(qint32 recipeID) {
	return getRecipe(QString::number(recipeID));
}

Recipe Gw2RecipesParser::getRecipe(QString recipeID) {
	Gw2API api(singleRecipesURIStr, recipeID);
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

/*QHash<qint32, Recipe> Gw2RecipesParser::getRecipeList(QList<qint32> recipeIDs) {

}

QHash<qint32, Recipe> Gw2RecipesParser::getRecipeList(QStringList recipeID) {

}*/

Recipe Gw2RecipesParser::getItemRecipe(qint32 itemID){
	return getRecipe(getRecipeID(itemID));
}

Recipe Gw2RecipesParser::getItemRecipe(QString itemID) {
	return getRecipe(QString::number(getRecipeID(itemID)));
}

/*QHash<qint32, Recipe> Gw2RecipesParser::getItemRecipeHash(QList<qint32> itemIDs) {

}

QHash<qint32, Recipe> Gw2RecipesParser::getItemRecipeHash(QStringList itemIDs) {

}
*/
