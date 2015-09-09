#ifndef WATCHLISTMANAGER_H
#define WATCHLISTMANAGER_H

#include <memory>
#include <QList>
#include <QString>

class WatchlistTabWidget;

class WatchlistManager {
public:
	static QList<WatchlistTabWidget*> init();
	static void clear();
	static QList<WatchlistTabWidget*> get();
	static WatchlistTabWidget* add(QString name);
	static void remove(WatchlistTabWidget* tab);
private:
	static QString watchlistJsonPath;
	static QList<std::shared_ptr<WatchlistTabWidget>> watchlistTabList;
	static void read();
	static void write();
};

#endif // WATCHLISTMANAGER_H
