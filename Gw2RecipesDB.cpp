#include "Gw2RecipesDB.h"
#include <QDebug>
#include <QTime>
#include <QFileInfo>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

QString Gw2RecipesDB::path = "data/recipes.db";
QString Gw2RecipesDB::recipesTableScheme =
	"CREATE TABLE RECIPES("
	"OUTPUT_ITEM_ID INT PRIMARY KEY NOT NULL,"
	"RECIPE_ID INT,"
	"JSON_DATA_STRING TEXT);";
QSqlDatabase Gw2RecipesDB::db;
QHash<qint32, qint32> Gw2RecipesDB::recipeIDOutputItemIDHash;
QHash<qint32, qint32> Gw2RecipesDB::outputItemIDRecipeIDHash;
QHash<qint32, Recipe> Gw2RecipesDB::recipeIDRecipeHash;

void Gw2RecipesDB::init() {
	qDebug() << "Initializing Gw2RecipeDB...";
	QTime t; t.start();
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
	qDebug("Time elapsed: %d ms", t.elapsed());
}

bool Gw2RecipesDB::add(Recipe recipe) {
	if(!containsRecipeID(recipe.recipeID))
		return write(recipe);
	return false;
}

bool Gw2RecipesDB::add(qint32 outputItemID) {
	if(!containsOutputItemID(outputItemID))
		return write(outputItemID);
	else
		return false;
}

Recipe Gw2RecipesDB::getWithRecipeID(qint32 recipeID) {
	if(recipeIDRecipeHash.contains(recipeID))
		return recipeIDRecipeHash.value(recipeID);
	else
		qDebug() << "Could not find recipe with id " + QString::number(recipeID);
	return Recipe();
}

Recipe Gw2RecipesDB::getWithOutputItemID(qint32 outputItemID) {
	return getWithRecipeID(getRecipeID(outputItemID));
}

qint32 Gw2RecipesDB::getRecipeID(qint32 outputItemID) {
	if(outputItemIDRecipeIDHash.contains(outputItemID))
		return outputItemIDRecipeIDHash.value(outputItemID);
	else
		qDebug() << "Could not find recipe id with output id " + QString::number(outputItemID);
	return -1;
}

qint32 Gw2RecipesDB::getOutputItemID(qint32 recipeID) {
	if(recipeIDOutputItemIDHash.contains(recipeID))
		return recipeIDOutputItemIDHash.value(recipeID);
	else
		qDebug() << "Could not find recipe id with output id " + QString::number(recipeID);
	return -1;
}

bool Gw2RecipesDB::containsRecipeID(qint32 recipeID) {
	return recipeIDRecipeHash.contains(recipeID);
}

bool Gw2RecipesDB::containsOutputItemID(qint32 outputItemID) {
	return outputItemIDRecipeIDHash.contains(outputItemID);
}

void Gw2RecipesDB::clear() {
	close();
	recipeIDOutputItemIDHash.clear();
	outputItemIDRecipeIDHash.clear();
	recipeIDRecipeHash.clear();
}

bool Gw2RecipesDB::open() {
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

bool Gw2RecipesDB::close() {
	if(db.isOpen()) {
		db.close();
	} else
		qDebug() << "Warning! Attempting to close database while it is already closed.";
	return true;
}

void Gw2RecipesDB::load() {
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
			qint32 outputItemID = record.value("OUTPUT_ITEM_ID").toInt();
			qint32 recipeID = record.value("RECIPE_ID").toInt();
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

bool Gw2RecipesDB::write(
		qint32 outputItemID,
		qint32 recipeID,
		QString jsonString)
{
	if(open()) {
		recipeIDOutputItemIDHash[recipeID] = outputItemID;
		outputItemIDRecipeIDHash[outputItemID] = recipeID;
		QSqlQuery q(db);
		q.prepare("INSERT INTO RECIPES VALUES(:OUTPUT_ITEM_ID,:RECIPE_ID,:JSON_DATA_STRING);");
		q.bindValue(":OUTPUT_ITEM_ID", outputItemID);
		q.bindValue(":RECIPE_ID", recipeID);
		q.bindValue(":JSON_DATA_STRING", jsonString);
		q.exec();
		QSqlError er = q.lastError();
		if(er.type() != QSqlError::NoError)
			qDebug() << "Error writing to recipe DB: " + er.text();
		else
			db.commit();
		close();
		return true;
	} else
		qDebug() << "Warning! Skipped write to recipe DB for outputItemID: " + QString::number(outputItemID) + "because it was not opened correctly";
	return false;
}

bool Gw2RecipesDB::write(Recipe recipe) {
	if(write(recipe.outputID, recipe.recipeID, recipe.jsonString)) {
		recipeIDRecipeHash[recipe.recipeID] = recipe;
		return true;
	}
	return false;
}
