#ifndef WATCHLISTTABWIDGET_H
#define WATCHLISTTABWIDGET_H

#include <memory>
#include <QWidget>
#include <QString>
#include <QList>
#include "CraftingTree.h"

class BatchWindow;
class QTableWidgetItem;
class QTreeWidgetItem;

namespace Ui {
	class WatchlistTabWidget;
}

struct WatchlistRow {
	WatchlistRow(qint32 itemID);
	qint32 itemID;
	//Order is Item Name, CTC, Adj B/S, Adj C/S
	QList<std::shared_ptr<QTableWidgetItem>> tableItems;
	CraftingTreeRoot craftingTree;
	std::shared_ptr<QTreeWidgetItem> treeItem;
};

class WatchlistTabWidget : public QWidget {
    Q_OBJECT
public:
	explicit WatchlistTabWidget(
		QString name,
		QList<qint32> itemIDs = QList<qint32>(),
		QWidget *parent = 0);
	~WatchlistTabWidget();
	void add(qint32 itemID);
	void remove(qint32 itemID);
	QString getName();
	QList<qint32> getItemIDs();
private slots:
	void on_addNewItemButton_clicked();
	void on_watchlistTable_cellClicked(int row, int column);
	void on_watchlistTable_customContextMenuRequested(const QPoint &pos);
	void on_startBatchButton_clicked();
private:
	Ui::WatchlistTabWidget *ui;
	QString name;
	QList<WatchlistRow> tableRows;
	void init(QList<qint32> itemIDs);
	void addRowToTable(WatchlistRow &row);
	qint32 findIndex(qint32 itemID);
	void setTreeWidgetItem(QTreeWidgetItem *treeItem);
	void expandCraftTreeWidgetItems(QTreeWidgetItem *item);
};

#endif // WATCHLISTTABWIDGET_H
