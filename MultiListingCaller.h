#ifndef MULTILISTINGCALLER_H
#define MULTILISTINGCALLER_H

#include <QMultiHash>

class Listings;

class MultiListingCaller {
public:
	static void add(qint32 id, Listings &listings);
	static void load();
	static void clear();
private:
	static QMultiHash<qint32, Listings*> storage;
};

#endif // MULTILISTINGCALLER_H
