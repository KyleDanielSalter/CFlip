#ifndef WATCHLISTMANAGER_H
#define WATCHLISTMANAGER_H

#include <memory>
#include <QList>
#include <QString>
#include "WatchListTabWidget.h"

class WatchListManager {
public:
	static void init();
	static QList<WatchListTabWidget*> get();
private:
	static QString watchlistJsonPath;
	static QList<std::shared_ptr<WatchListTabWidget>> watchlistTabList;
	void read();
	void write();
};

#endif // WATCHLISTMANAGER_H
