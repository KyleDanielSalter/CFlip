#include "WatchlistManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include "WatchlistTabWidget.h"

QString WatchlistManager::watchlistJsonPath = "data/watchlist.json";
QList<std::shared_ptr<WatchlistTabWidget>> WatchlistManager::watchlistTabList;

QList<WatchlistTabWidget *> WatchlistManager::init() {
	read();
	return get();
}

void WatchlistManager::clear() {
	write();
	watchlistTabList.clear();
}

QList<WatchlistTabWidget*> WatchlistManager::get() {
	QList<WatchlistTabWidget*> ret;
	for(auto i : watchlistTabList)
		ret << i.get();
	return ret;
}

WatchlistTabWidget* WatchlistManager::add(QString name) {
	std::shared_ptr<WatchlistTabWidget> newTab(new WatchlistTabWidget(name));
	watchlistTabList.append(newTab);
	write();
	return watchlistTabList.back().get();
}

void WatchlistManager::remove(WatchlistTabWidget* tab) {
	for(auto iter = watchlistTabList.begin(); iter != watchlistTabList.end(); ++iter) {
		if(tab == iter->get())
			watchlistTabList.erase(iter);
	}
	write();
}

void WatchlistManager::read() {
	QFile file(watchlistJsonPath);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QJsonDocument jsonDoc(QJsonDocument::fromJson(file.readAll()));
	file.close();
	QJsonObject jsonObj = jsonDoc.object();
	QJsonArray jsonWatchlistsArray = jsonObj["Watchlists"].toArray();
	for(auto iter : jsonWatchlistsArray) {
		QJsonObject jsonWatchlistObject = iter.toObject();
		QString watchlistName = jsonWatchlistObject["name"].toString();
		QJsonArray jsonItemIDArray = jsonWatchlistObject["itemIDs"].toArray();
		QList<qint32> itemIDs;
		for(auto innerIter : jsonItemIDArray)
			itemIDs << innerIter.toInt();
		std::shared_ptr<WatchlistTabWidget> newTab(new WatchlistTabWidget(watchlistName, itemIDs));
		watchlistTabList.append(newTab);
	}
}

void WatchlistManager::write() {
	QFile file(watchlistJsonPath);
	QHash<QString, QList<qint32>> watchlistHash;
	QJsonDocument jsonDoc;
	QJsonObject jsonObj;
	QJsonArray jsonWatchlistArray;
	file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
	//Get relevant data to write
	for(auto i :watchlistTabList)
		watchlistHash[i->getName()] = i->getItemIDs();
	for(auto iter = watchlistHash.begin(); iter != watchlistHash.end(); ++iter) {
		QJsonObject jsonWatchlistObject;
		QJsonArray jsonItemIDArray;
		jsonWatchlistObject.insert("name", QJsonValue(iter.key()));

		for(auto innerIter : iter.value())
			jsonItemIDArray.append(QJsonValue(innerIter));
		jsonWatchlistObject.insert("itemIDs", QJsonValue(jsonItemIDArray));
		jsonWatchlistArray.append(jsonWatchlistObject);
	}
	jsonObj.insert("Watchlists", QJsonValue(jsonWatchlistArray));
	jsonDoc.setObject(jsonObj);
	file.write(jsonDoc.toJson());
	file.close();
}
