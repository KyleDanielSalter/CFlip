#ifndef GW2RECIPESPARSER_H
#define GW2RECIPESPARSER_H

#include <QString>
#include <QList>
#include <QPair>

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
	//Returns int instead of string, contrary to parser format because an item
	//with no recipe returns -1
	static qint32 getRecipeID(QString itemID);
	//returns default recipe struct if an invalid id
	static Recipe getRecipe(QString recipeID);
	static Recipe getItemRecipe(QString itemID);
private:
	static QString recipesURIStr;
	static QString recipesSearchURIStr;
};

#endif // GW2RECIPESPARSER_H
