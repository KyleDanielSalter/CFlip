#ifndef GW2RECIPEDB_H
#define GW2RECIPEDB_H

#include <QSqlDatabase>
#include <QString>
#include <QHash>
#include "Gw2RecipesParser.h"

class Gw2RecipeDB {
public:
	static void init();
	static bool add(QString jsonString);
	static Recipe getWithRecipeID(qint32 recipeID);
	static Recipe getWithOutputItemID(qint32 outputItemID);
	static qint32 getRecipeID(qint32 outputItemID);
	static qint32 getOutputItemID(qint32 recipeID);
	static bool containsRecipeID(qint32 recipeID);
	static bool containsRecipeWithOutputItemID(qint32 outputItemID);
private:
	static QString path;
	static QString recipesTableScheme;
	static QSqlDatabase db;
	static QHash<qint32, qint32> recipeIDOutputItemIDHash;
	static QHash<qint32, qint32> outputItemIDRecipeIDHash;
	static QHash<qint32, Recipe> recipeIDJsonStringHash;
	static bool open();
	static bool close();
	static void load();
};

#endif // GW2RECIPEDB_H
