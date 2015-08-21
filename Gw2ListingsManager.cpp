#include "Gw2ListingsManager.h"
#include <QDebug>

QHash<qint32, Listings> Gw2ListingsManager::itemIDListingsHash;
QList<qint32> Gw2ListingsManager::idList;

void Gw2ListingsManager::add(qint32 itemID){
	if(!idList.contains(itemID) && Gw2ListingsParser::getAPIEndPoint()->checkID(itemID))
		idList << itemID;
}

Listings Gw2ListingsManager::get(qint32 itemID) {
	if(itemIDListingsHash.contains(itemID))
		return itemIDListingsHash.value(itemID);
	return Listings();
}

Listings Gw2ListingsManager::forceGet(qint32 itemID) {
	if(Gw2ListingsParser::getAPIEndPoint()->checkID(itemID))
		itemIDListingsHash.insert(itemID, Gw2ListingsParser::get(itemID));
	return itemIDListingsHash.value(itemID);
}

void Gw2ListingsManager::load() {
	QHash<qint32, Listings> result = Gw2ListingsParser::get(idList);
	//Purposefully overwite previous entries
	for(auto iter = result.begin(); iter != result.end(); ++iter)
		itemIDListingsHash.insert(iter.key(), iter.value());
	idList.clear();
}

void Gw2ListingsManager::clear() {
	clearIDList();
	clearHash();
}

void Gw2ListingsManager::clearIDList() {
	idList.clear();
}

void Gw2ListingsManager::clearHash() {
	itemIDListingsHash.clear();
}

void Gw2ListingsManager::refresh() {
	clearIDList();
	idList = itemIDListingsHash.keys();
	clearHash();
	load();
}
