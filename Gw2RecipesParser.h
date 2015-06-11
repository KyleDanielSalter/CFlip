#ifndef GW2RECIPESPARSER_H
#define GW2RECIPESPARSER_H

#include <QString>
#include <QHash>
#include <QList>
#include <QPair>
#include "Gw2API.h"

class Recipe {
public:
	Recipe();
	Recipe(const Recipe &other);
	Recipe(
		qint32 recipeID,
		qint32 outputID,
		qint32 outputItemCount,
		QList<QPair<qint32, qint32> > ingredients);
	const qint32 recipeID, outputID, outputItemCount;
	//First is itemID, second is quantity
	const QList<QPair<qint32, qint32> > ingredients;
};

class Gw2RecipesParser {
public:
	//-1 if no recipe.
	static qint32 getRecipeID(qint32 itemID);
	static qint32 getRecipeID(QString itemID);
	//returns default recipe struct if an invalid id (which had id=-1)
	static Recipe getRecipe(qint32 recipeID);
	static Recipe getRecipe(QString recipeID);
	static QHash<qint32, Recipe> getRecipeHash(QList<qint32> recipeIDs);
	static QHash<qint32, Recipe> getRecipeHash(QStringList recipeID);
	static Recipe getItemRecipe(qint32 itemID);
	static Recipe getItemRecipe(QString itemID);
	static QHash<qint32, Recipe> getItemRecipeHash(QList<qint32> itemIDs);
	static QHash<qint32, Recipe> getItemRecipeHash(QStringList itemIDs);
private:
	static QString singleRecipesURIStr, multiRecipesURIStr, recipesSearchURIStr;
	static Gw2API singleRecipesAPIEndPoint, multiRecipeAPIEndPoint,
		recipesSearchAPIEndPoint;
};

#endif // GW2RECIPESPARSER_H
