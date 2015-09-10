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
	, treeItem(craftingTree.getQTree())
{
	QString itemName(Gw2ItemDB::getItemName(itemID)),
		costToCraft(Gw2Currency::string(craftingTree.getVertex()->totalCraftCost)),
		adjBS(Gw2Currency::string(craftingTree.getAdjBS())),
		adjCS(Gw2Currency::string(craftingTree.getProfit()));
	std::shared_ptr<QTableWidgetItem> itemNameTableItem(new QTableWidgetItem(itemName, 0)),
		costToCraftTableItem(new QTableWidgetItem(costToCraft, 0)),
		adjBSTableItem(new QTableWidgetItem(adjBS, 0)),
		adjCSTableItem(new QTableWidgetItem(adjCS, 0));
	tableItems << itemNameTableItem;
	tableItems << costToCraftTableItem;
	tableItems << adjBSTableItem;
	tableItems << adjCSTableItem;
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
	ui->treeWidget->setColumnWidth(0, 200);
	init(itemIDs);
}

WatchlistTabWidget::~WatchlistTabWidget() {
    delete ui;
}

void WatchlistTabWidget::add(qint32 itemID) {
	tableRows.append(WatchlistRow(itemID));
	//must be unique
	if(findIndex(itemID == -1))
	   addRowToTable(tableRows.back());
}

void WatchlistTabWidget::remove(qint32 itemID) {
	qint32 index = findIndex(itemID);
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
	for(qint32 row = 0; row < itemIDs.size(); ++row) {
		tableRows.append(WatchlistRow(itemIDs[row]));
		addRowToTable(tableRows.back());
	}
}

void WatchlistTabWidget::addRowToTable(WatchlistRow &row) {
	qint32 rowInsert = ui->watchlistTable->rowCount();
	ui->watchlistTable->setRowCount(rowInsert + 1);
	for(qint32 col = 0; col < row.tableItems.size(); ++col)
		ui->watchlistTable->setItem(rowInsert, col, row.tableItems[col].get());
	setTreeWidgetItem(row.treeItem.get());
}

qint32 WatchlistTabWidget::findIndex(qint32 itemID) {
	for(qint32 i = 0; i < tableRows.size(); ++i) {
		if(tableRows[i].itemID == itemID)
			return i;
	}
	return -1;
}

void WatchlistTabWidget::setTreeWidgetItem(QTreeWidgetItem *treeItem) {
	if(ui->treeWidget->topLevelItem(0) != treeItem) {
		while(ui->treeWidget->topLevelItemCount() > 0)
			ui->treeWidget->takeTopLevelItem(0);
		ui->treeWidget->insertTopLevelItem(0, treeItem);
		expandCraftTreeWidgetItems(ui->treeWidget->topLevelItem(0));
	}
}

void WatchlistTabWidget::expandCraftTreeWidgetItems(QTreeWidgetItem* item) {
	if(item->text(1) == "Craft")
		item->setExpanded(true);
	for(qint32 i = 0; i < item->childCount(); ++i)
		expandCraftTreeWidgetItems(item->child(i));
}

void WatchlistTabWidget::on_watchlistTable_cellClicked(int row, int column) {
	setTreeWidgetItem(tableRows[row].treeItem.get());
}

void WatchlistTabWidget::on_watchlistTable_customContextMenuRequested(const QPoint &pos)
{
	if(ui->watchlistTable->itemAt(pos) != 0) {
		QMenu rightClickMenu(ui->watchlistTable);
		rightClickMenu.addAction("Remove Item");
		QPoint globalPos = ui->watchlistTable->viewport()->mapToGlobal(pos);
		QAction *removeAction = rightClickMenu.exec(globalPos);
		if(removeAction) {
			QTableWidgetItem *clickedItem = ui->watchlistTable->itemAt(pos);
			qint32 row = ui->watchlistTable->row(clickedItem);;
			remove(tableRows[row].itemID);
		}
	}
}

void WatchlistTabWidget::on_startBatchButton_clicked()
{
	BatchWindow *newBatch = new BatchWindow(tableRows, parentWidget());
	newBatch->show();
}
