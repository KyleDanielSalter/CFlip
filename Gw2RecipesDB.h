#ifndef GW2RECIPEDB_H
#define GW2RECIPEDB_H

#include <QSqlDatabase>
#include <QString>
#include <QHash>
#include "Gw2RecipesParser.h"

class Gw2RecipesDB {
public:
	static void init();
	static bool add(Recipe recipe);
	//Adds a record that there is no recipe for this item, i.e. recipeID = -1
	static bool add(qint32 outputItemID);
	static Recipe getWithRecipeID(qint32 recipeID);
	static Recipe getWithOutputItemID(qint32 outputItemID);
	static qint32 getRecipeID(qint32 outputItemID);
	static qint32 getOutputItemID(qint32 recipeID);
	static bool containsRecipeID(qint32 recipeID);
	static bool containsOutputItemID(qint32 outputItemID);
private:
	static QString path;
	static QString recipesTableScheme;
	static QSqlDatabase db;
	static QHash<qint32, qint32> recipeIDOutputItemIDHash;
	static QHash<qint32, qint32> outputItemIDRecipeIDHash;
	static QHash<qint32, Recipe> recipeIDRecipeHash;
	static bool open();
	static bool close();
	static void load();
	//Should only be called for a new record so the hashes do not repeat.
	static bool write(
		qint32 outputItemID,
		qint32 recipeID = -1,
		QString jsonString = QString());
	static bool write(Recipe recipe);
};

#endif // GW2RECIPEDB_H
