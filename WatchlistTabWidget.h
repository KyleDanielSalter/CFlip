#ifndef WATCHLISTTABWIDGET_H
#define WATCHLISTTABWIDGET_H

#include <memory>
#include <QWidget>
#include <QString>
#include <QList>
#include "CraftingTree.h"

class QTableWidgetItem;
namespace Ui {
	class WatchListTabWidget;
}

class WatchListTabWidget : public QWidget {
    Q_OBJECT
public:
	explicit WatchListTabWidget(
		QString name,
		QList<qint32> itemIDs,
		QWidget *parent = 0);
    ~WatchListTabWidget();
	void add(qint32 itemID);
	void remove(qint32 itemID);
private:
	struct WatchlistRow {
		WatchlistRow(qint32 itemID);
		qint32 itemID;
		//Order is Icon, Item Name, Adj B/S, Adj C/S
		QList<std::shared_ptr<QTableWidgetItem>> tableItems;
		CraftingTreeRoot craftingTree;
	};
    Ui::WatchListTabWidget *ui;
	QString name;
	QList<qint32> itemIDs;
	QList<WatchlistRow> tableRows;
	void init();
};

#endif // WATCHLISTTABWIDGET_H
