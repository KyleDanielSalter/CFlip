#include "Gw2RecipeDB.h"
#include <QDebug>
#include <QFileInfo>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

QString Gw2RecipeDB::path = "data/recipes.db";
QString Gw2RecipeDB::recipesTableScheme =
	"CREATE TABLE RECIPES("
	"RECIPE_ID INT PRIMARY KEY NOT NULL,"
	"OUTPUT_ITEM_ID INT NOT NULL,"
	"JSON_DATA_STRING TEXT NOT NULL);";
QSqlDatabase Gw2RecipeDB::db;
QHash<qint32, qint32> Gw2RecipeDB::recipeIDOutputItemIDHash;
QHash<qint32, qint32> Gw2RecipeDB::outputItemIDRecipeIDHash;
QHash<qint32, qint32> Gw2RecipeDB::recipeIDRecipeHash;

void Gw2RecipeDB::init() {
	QFileInfo dbInfo(path);
	db = QSqlDatabase::addDatabase("QSQLITE", "RECIPES");
	db.setDatabaseName(path);
	if(!dbInfo.exists() || !dbInfo.isFile()) {
		if(db.open()) {
			QSqlQuery q(db);
			q.exec(recipesTableScheme);
			close();
		}
	} else
		load();
}

bool Gw2RecipeDB::add(Recipe recipe) {
	if(!jsonString.isEmpty()) {
		qint32 recipeID = recipe.recipeID;
		qint32 outputItemID = recipe.outputID;
		QString jsonString = recipe.jsonString;
		if(!containsRecipeID(recipeID) && open()) {
			recipeIDOutputItemIDHash[recipeID] = outputItemID;
			outputItemIDRecipeIDHash[outputItemID] = recipeID;
			recipeIDRecipeHash[recipeID] = recipe;
			QSqlQuery q(db);
			q.prepare("INSERT INTO RECIPES VALUES(:RECIPE_ID,:OUTPUT_ITEM_ID,:JSON_DATA_STRING);");
			q.bindValue(":RECIPE_ID", recipeID);
			q.bindValue(":OUTPUT_ITEM_ID", outputItemID);
			q.bindValue(":JSON_DATA_STRING", jsonString);
			q.exec();
			db.commit();
			close();
		}
	} else {
		qDebug() << "Warning! Attempting to add a recipe jsonString to recipe DB while string is empty or error opening DB.";
		return false;
	}
	return true;
}

Recipe Gw2RecipeDB::getWithRecipeID(qint32 recipeID) {
	if(open()) {
		QSqlQueryModel model;
		model.setQuery("SELECT JSON_DATA_STRING FROM RECIPES WHERE RECIPE_ID=" + QString::number(recipeID), db);
		while(model.canFetchMore())
			model.fetchMore();
		QString jsonString = model.record(0).value("JSON_DATA_STRING").toString();
		QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
		QJsonObject jsonObj = jsonDoc.object();
		QJsonArray jsonIngredients = jsonObj["ingredients"].toArray();
		QList<QPair<qint32, qint32>> ingredients;
		for(auto i : jsonIngredients) {
			QJsonObject iObj = i.toObject();
			ingredients << QPair<qint32, qint32>(iObj["item_id"].toInt(), iObj["count"].toInt());
		}
		close();
		return Recipe(jsonObj["id"].toInt(), jsonObj["output_item_id"].toInt(), jsonObj["output_item_count"].toInt(), ingredients, jsonString);
	} else {
		qDebug() << "Error opening data to get recipe with recipe id: " + QString::number(recipeID);
	}
	return Recipe();
}

Recipe Gw2RecipeDB::getWithOutputItemID(qint32 outputItemID) {
	if(open()) {
		QSqlQueryModel model;
		model.setQuery("SELECT JSON_DATA_STRING FROM RECIPES WHERE OUTPUT_ITEM_ID=" + QString::number(outputItemID), db);
		while(model.canFetchMore())
			model.fetchMore();
		QString jsonString = model.record(0).value("JSON_DATA_STRING").toString();
		QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
		QJsonObject jsonObj = jsonDoc.object();
		QJsonArray jsonIngredients = jsonObj["ingredients"].toArray();
		QList<QPair<qint32, qint32>> ingredients;
		for(auto i : jsonIngredients) {
			QJsonObject iObj = i.toObject();
			ingredients << QPair<qint32, qint32>(iObj["item_id"].toInt(), iObj["count"].toInt());
		}
		close();
		return Recipe(jsonObj["id"].toInt(), jsonObj["output_item_id"].toInt(), jsonObj["output_item_count"].toInt(), ingredients, jsonString);
	} else {
		qDebug() << "Error opening data to get recipe with output item id: " + QString::number(outputItemID);
	}
	return Recipe();
}

qint32 Gw2RecipeDB::getRecipeID(qint32 outputItemID) {
	if(open()) {
		QSqlQueryModel model;
		model.setQuery("SELECT RECIPE_ID FROM RECIPES WHERE OUTPUT_ITEM_ID=" + QString::number(outputItemID), db);
		while(model.canFetchMore())
			model.fetchMore();
		if(model.rowCount() > 0) {
			close();
			return model.record(0).value("RECIPE_ID").toInt();
		} else {
			close();
			return -1;
		}
	}
	return -1;
}

qint32 Gw2RecipeDB::getOutputItemID(qint32 recipeID) {
	if(open()) {
		QSqlQueryModel model;
		model.setQuery("SELECT OUTPUT_ITEM_ID FROM RECIPES WHERE RECIPE_ID=" + QString::number(recipeID), db);
		while(model.canFetchMore())
			model.fetchMore();
		if(model.rowCount() > 0) {
			close();
			return model.record(0).value("OUTPUT_ITEM_ID").toInt();
		} else {
			close();
			return -1;
		}
	}
	return -1;
}

bool Gw2RecipeDB::containsRecipeID(qint32 recipeID) {
	if(open()) {
		QSqlQueryModel model;
		model.setQuery("SELECT JSON_DATA_STRING FROM RECIPES WHERE RECIPE_ID=" + QString::number(recipeID), db);
		while(model.canFetchMore())
			model.fetchMore();
		if (model.rowCount() > 0) {
			close();
			return true;
		} else
		close();
	}
	return false;
}

bool Gw2RecipeDB::containsRecipeWithOutputItemID(qint32 outputItemID) {
	if(open()) {
		QSqlQueryModel model;
		model.setQuery("SELECT JSON_DATA_STRING FROM RECIPES WHERE RECIPE_ID=" + QString::number(outputItemID), db);
		while(model.canFetchMore())
			model.fetchMore();
		if (model.rowCount() > 0)
			return true;
		close();
	}
	return false;
}

bool Gw2RecipeDB::open() {
	if(!db.isOpen()) {
		db.open();
		if(db.isOpenError()) {
			qDebug() << "Error opening recipe database. Error string: " + db.lastError().text();
			db.close();
			return false;
		}
		return true;
	}
	qDebug() << "Warning! Attempting to open recipe database while it is already opened.";
	return true;
}

bool Gw2RecipeDB::close() {
	if(db.isOpen()) {
		db.close();
		return true;
	}
	qDebug() << "Warning! Attempting to close database while it is already closed.";
	return false;
}

void Gw2RecipeDB::load() {
	if(open()) {
		QSqlQuery q(db);
		QSqlQueryModel model;
		model.setQuery("SELECT * FROM RECIPES", db);
		//Make sure to load the entire db
		while(model.canFetchMore())
			model.fetchMore();
		qint32 rowCount = model.rowCount();
		for(qint32 i = 0; i < rowCount; ++i) {
			QSqlRecord record = model.record(i);
			qint32 recipeID = record.value("RECIPE_ID").toInt();
			qint32 outputItemID = record.value("OUTPUT_ITEM_ID").toInt();
			QString jsonString = record.value("JSON_DATA_STRING").toString();
			recipeIDOutputItemIDHash[recipeID] = outputItemID;
			outputItemIDRecipeIDHash[outputItemID] = recipeID;
			QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
			QJsonObject jsonObj = jsonDoc.object();
			QJsonArray jsonIngredients = jsonObj["ingredients"].toArray();
			QList<QPair<qint32, qint32>> ingredients;
			for(auto i : jsonIngredients) {
				QJsonObject iObj = i.toObject();
				ingredients << QPair<qint32, qint32>(iObj["item_id"].toInt(), iObj["count"].toInt());
			}
			recipeIDRecipeHash[recipeID] = Recipe(jsonObj["id"].toInt(), jsonObj["output_item_id"].toInt(), jsonObj["output_item_count"].toInt(), ingredients, jsonString);
		}
		close();
	}
}
