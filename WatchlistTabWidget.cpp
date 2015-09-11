#include "WatchlistTabWidget.h"
#include "ui_WatchlistTabWidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QHash>
#include <QTreeWidgetItem>
#include <QAction>
#include <QMenu>
#include "BatchWindow.h"
#include "Gw2ItemDB.h"
#include "ImageDownloader.h"
#include "Gw2Currency.h"

WatchlistRow::WatchlistRow(qint32 itemID)
	: itemID(itemID)
	, craftingTree(itemID)
{
	QString itemName(Gw2ItemDB::getItemName(itemID)),
		costToCraft(Gw2Currency::string(craftingTree.getVertex()->totalCraftCost)),
		adjBS(Gw2Currency::string(craftingTree.getAdjBS())),
		adjCS(Gw2Currency::string(craftingTree.getProfit()));
	tableItems << itemName;
	tableItems << costToCraft;
	tableItems << adjBS;
	tableItems << adjCS;
}

WatchlistTabWidget::WatchlistTabWidget(
	QString name,
	QList<qint32> itemIDs,
	QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::WatchlistTabWidget)
	, name(name)
{
    ui->setupUi(this);
	init(itemIDs);
}

WatchlistTabWidget::~WatchlistTabWidget() {
	//Unparent the current QTreeWidgetItem from the QTreeWidget for safe deletion.
	ui->treeWidget->takeTopLevelItem(0);
    delete ui;
}

void WatchlistTabWidget::add(qint32 itemID) {
	//must be unique
	if(findIndex(itemID) == -1) {
		//Disable add button until complete
		ui->addNewItemButton->setText("Loading...");
		ui->addNewItemButton->setEnabled(false);
		tableRows.append(WatchlistRow(itemID));
		addRowToTable(tableRows.back());
		ui->addNewItemButton->setText("Add New Item");
		ui->addNewItemButton->setEnabled(true);
	} else
		QMessageBox::warning(this, "Can Not Add New Item", "Item must be unique.");
}

void WatchlistTabWidget::remove(WatchlistRow &row) {
	qint32 index = findIndex(row.itemID);
	if(index != -1) {
		tableRows.removeAt(index);
		ui->watchlistTable->removeRow(index);
		while(ui->treeWidget->topLevelItemCount() > 0)
			ui->treeWidget->takeTopLevelItem(0);
	}
}

QString WatchlistTabWidget::getName() {
	return name;
}

void WatchlistTabWidget::setName(QString newName) {
	name = newName;
}

QList<qint32> WatchlistTabWidget::getItemIDs() {
	QList<qint32> ret;
	for(auto iter : tableRows)
		ret << iter.itemID;
	return ret;
}

void WatchlistTabWidget::on_addNewItemButton_clicked() {
	bool ok;
	QString itemName = QInputDialog::getText(this, tr("Enter Valid Item Name"), tr("Item Name:"),QLineEdit::Normal, "", &ok);
	if(ok) {
		qint32 itemID = Gw2ItemDB::getItemID(itemName);
		if(itemID)
			add(Gw2ItemDB::getItemID(itemName));
		else
			QMessageBox::warning(this, "Invalid Item Name", "The entered item name does not exist.");
	}
}

void WatchlistTabWidget::init(QList<qint32> itemIDs) {
	//Format adjusting
	ui->watchlistTable->setSortingEnabled(true);
	ui->treeWidget->setColumnWidth(0, 200);
	QHeaderView *watchlistTableVerticalHeader = ui->watchlistTable->verticalHeader();
	//Aesthetically pleasing value found experimentally
	watchlistTableVerticalHeader->setDefaultSectionSize(22);
	//Init data in the table.
	for(qint32 row = 0; row < itemIDs.size(); ++row) {
		tableRows.append(WatchlistRow(itemIDs[row]));
		addRowToTable(tableRows.back());
	}
}

void WatchlistTabWidget::addRowToTable(WatchlistRow &row) {
	qint32 rowInsert = ui->watchlistTable->rowCount();
	ui->watchlistTable->setRowCount(rowInsert + 1);
	//Item Name
	ui->watchlistTable->setItem(rowInsert, 0, new QTableWidgetItem(row.tableItems[0], 0));
	//CTC, Adj B/S, Adj C/S
	for(qint32 col = 1; col < row.tableItems.size(); ++col)
		ui->watchlistTable->setItem(rowInsert, col, new Gw2CurrencyTableWidgetItem(row.tableItems[col]));
	setTreeWidgetItem(row);
}

qint32 WatchlistTabWidget::findIndex(qint32 itemID) {
	for(qint32 i = 0; i < tableRows.size(); ++i) {
		if(tableRows[i].itemID == itemID)
			return i;
	}
	return -1;
}

QTreeWidgetItem* WatchlistTabWidget::buildQTree(CraftingTreeVertex *vertex, QTreeWidgetItem *parent) {
	QTreeWidgetItem* ret = new QTreeWidgetItem(parent, 0);
	QStringList cols = getTreeColumns(vertex);
	for(qint32 i = 0; i < cols.size(); ++i)
		ret->setText(i, cols[i]);
	for(auto i : vertex->components) {
		CraftingTreeVertex* next = static_cast<CraftingTreeVertex*>(i.first.get());
		buildQTree(next, ret);
	}
	return ret;
}

QStringList WatchlistTabWidget::getTreeColumns(CraftingTreeVertex* vertex) {
	QString itemName = Gw2ItemDB::getItemName(vertex->outputItemID),
		craftTypeStr = vertex->craftType == CraftingTreeVertex::BUY ? "Buy" : "Craft",
		costStr = vertex->craftType == CraftingTreeVertex::BUY ? Gw2Currency::string(vertex->totalMarketValue) : Gw2Currency::string(vertex->totalCraftCost);
	return QStringList({itemName, craftTypeStr, costStr});
}

void WatchlistTabWidget::setTreeWidgetItem(WatchlistRow &row) {
	QTreeWidgetItem* currentTreeItem = ui->treeWidget->topLevelItem(0);
	if(currentTreeItem != nullptr) {
		//Remove the tree if the current tree is not the same as the new one.
		if(currentTreeItem->text(0) == Gw2ItemDB::getItemName(row.itemID))
			return;
		else {
			while(ui->treeWidget->topLevelItemCount() > 0)
				delete ui->treeWidget->takeTopLevelItem(0);
		}
	}
	QTreeWidgetItem *treeItem = buildQTree(row.craftingTree.getVertex());
	ui->treeWidget->insertTopLevelItem(0, treeItem);
	expandCraftTreeWidgetItems(ui->treeWidget->topLevelItem(0));
}

void WatchlistTabWidget::expandCraftTreeWidgetItems(QTreeWidgetItem *item) {
	if(item->text(1) == "Craft")
		item->setExpanded(true);
	for(qint32 i = 0; i < item->childCount(); ++i)
		expandCraftTreeWidgetItems(item->child(i));
}

void WatchlistTabWidget::on_watchlistTable_cellClicked(int row, int column) {
	QTableWidgetItem* rowWidgetItem = ui->watchlistTable->item(row, 0);
	qint32 itemID = Gw2ItemDB::getItemID(rowWidgetItem->text());
	if(itemID > 0)
		setTreeWidgetItem(tableRows[findIndex(itemID)]);
}

void WatchlistTabWidget::on_watchlistTable_customContextMenuRequested(const QPoint &pos)
{
	if(ui->watchlistTable->itemAt(pos) != 0) {
		QMenu rightClickMenu(ui->watchlistTable);
		rightClickMenu.addAction("Remove Item");
		QPoint globalPos = ui->watchlistTable->viewport()->mapToGlobal(pos);
		QAction *removeAction = rightClickMenu.exec(globalPos);
		if(removeAction) {
			//Find the rows of the selected items
			QList<qint32> selectedRows;
			QList<QTableWidgetItem*> selectedItems = ui->watchlistTable->selectedItems();
			for(auto i : selectedItems) {
				qint32 row = ui->watchlistTable->row(i);
				if(!selectedRows.contains(row))
					selectedRows << row;
			}
			//Remove selected rows
			for(auto i : selectedRows)
				remove(tableRows[i]);
		}
	}
}

void WatchlistTabWidget::on_startBatchButton_clicked()
{
	if(!tableRows.empty()) {
		QList<WatchlistRow> rowsInCurrentOrder;
		for(qint32 row = 0; row < ui->watchlistTable->rowCount(); ++row) {
			QTableWidgetItem* rowWidgetItem = ui->watchlistTable->item(row, 0);
			qint32 itemID = Gw2ItemDB::getItemID(rowWidgetItem->text());
			if(itemID > 0)
				rowsInCurrentOrder << tableRows[findIndex(itemID)];
		}
		BatchWindow *newBatch = new BatchWindow(rowsInCurrentOrder, parentWidget());
		newBatch->show();
	} else
		QMessageBox::warning(this, "Can Not Start Empty Batch", "Enter at least one item into the watchlist before starting a new batch.");
}
