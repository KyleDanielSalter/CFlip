#include "Gw2TradingPost.h"
#include <QDebug>
#include <QStringList>
#include <QTime>

QHash<qint32, Listings> Gw2TradingPost::listingsHash;

void Gw2TradingPost::init() {
	qDebug() << "Initializing Gw2TradingPost...";
	QTime t; t.start();
	QList<qint32> itemIDList = Gw2ListingsParser::getPossibleIDs();
	QStringList partition;
	QList<QStringList> partitionedIDLists;
	QList<Listings> allListings;
	qint32 partitionIndex = 0;
	qint32 numMaxIndices = 199;
	for(auto i : itemIDList) {
		if(partitionIndex > numMaxIndices) {
			partitionIndex = 0;
			partitionedIDLists << partition;
			partition.clear();
		}
		partition << QString::number(i);
		partitionIndex++;
	}
	//If there are leftover IDs in the partition, add it to the list
	if(!partition.empty())
		partitionedIDLists << partition;
	for(auto i : partitionedIDLists) {
		QTime t1; t1.start();
		QHash<qint32, Listings> partitionedListingHash = Gw2ListingsParser::get(i);
		allListings.append(partitionedListingHash.values());
		qDebug() << t1.elapsed();
	}
	for(auto i : allListings)
		listingsHash[i.getItemID()] = i;
	qDebug("Time elapsed: %d ms", t.elapsed());
}

Listings Gw2TradingPost::get(qint32 itemID) {
	if(listingsHash.isEmpty())
		init();
	return listingsHash[itemID];
}
