#include "MultiListingCaller.h"
#include <QDebug>
#include "Gw2ListingsParser.h"

QMultiHash<qint32, Listings*> MultiListingCaller::storage;

void MultiListingCaller::add(qint32 id, Listings &listings) {
	storage.insert(id, &listings);
}

void MultiListingCaller::load() {
	QHash<qint32, Listings> result = Gw2ListingsParser::get(storage.keys());
	auto test = storage;
	for(auto iter = result.begin(); iter != result.end(); ++iter) {
		auto storageIter = storage.find(iter.key());
		while(storageIter != storage.end() && storageIter.key() == iter.key()) {
			*storageIter.value() = iter.value();
			++storageIter;
		}
	}
	clear();
}

void MultiListingCaller::clear() {
	storage.clear();
}
