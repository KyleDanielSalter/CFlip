#include "BatchWindow.h"
#include "ui_BatchWindow.h"
#include <QDebug>
#include <QTableWidgetItem>
#include <QSpinBox>
#include <QHash>
#include <QPair>
#include "Gw2ItemDB.h"
#include "CraftingTree.h"
#include "Gw2Currency.h"

BatchWindow::BatchWindow(QList<WatchlistRow> rows, QWidget *parent) :
	QWidget(parent, Qt::Window),
	ui(new Ui::BatchWindow),
	rows(rows)
{
	ui->setupUi(this);
	init();
}

BatchWindow::~BatchWindow() {
	delete ui;
}

void BatchWindow::watchlistRowQuantityChanged() {
	ui->watchlistItemsTable->setSortingEnabled(false);
	qint32 row = getSpinnerRow(sender());
	if(row != -1) {
		QString itemName = ui->watchlistItemsTable->item(row, 1)->text();
		qint32 index = findIndex(Gw2ItemDB::getItemID(itemName));
		if(index != -1) {
			if(updateWatchlistRow(row, rows[index]))
				update();
		}
	}
	ui->watchlistItemsTable->setSortingEnabled(true);
}

void BatchWindow::init() {
	setWindowTitle("New Batch");
	//ui->watchlistItemsTable->setColumnCount(5);
	ui->watchlistItemsTable->setSortingEnabled(true);
	ui->shoppingListTable->setSortingEnabled(true);
	ui->overflowTable->setSortingEnabled(true);
	//Set row height to 22 for all tables to save space
	QHeaderView *watchlistTableVerticalHeader = ui->watchlistItemsTable->verticalHeader(),
		*shoppingListTableVerticalHeader = ui->shoppingListTable->verticalHeader(),
		*overflowTableVerticalHeader = ui->overflowTable->verticalHeader();
	watchlistTableVerticalHeader->setDefaultSectionSize(22);
	shoppingListTableVerticalHeader->setDefaultSectionSize(22);
	overflowTableVerticalHeader->setDefaultSectionSize(22);
	//Init data in tables
	initWatchlistTable();
	updateShoppingListTable();
	updateOverflowTable();
	updateOutputTextFields();
}

void BatchWindow::initWatchlistTable() {
	ui->watchlistItemsTable->setRowCount(0);
	ui->watchlistItemsTable->setRowCount(rows.size());
	for(qint32 i = 0; i < rows.size(); ++i) {
		CraftingTreeRoot *cTree = &rows[i].craftingTree;
		QString itemName = Gw2ItemDB::getItemName(rows[i].itemID);
		QSpinBox *spinner = new QSpinBox();
		spinner->setRange(0, INT_MAX);
		if(ui->preventOverflowCheckBox->isChecked()) {
			qint32 interval = cTree->getVertex()->findN();
			spinner->setSingleStep(interval);
			spinner->setValue(interval);
		} else
			spinner->setValue(1);
		connect(spinner, SIGNAL(valueChanged(int)), this, SLOT(watchlistRowQuantityChanged()));
		//Spinner
		ui->watchlistItemsTable->setCellWidget(i, 0, spinner);
		//Item Name
		ui->watchlistItemsTable->setItem(i, 1, new QTableWidgetItem(itemName, 0));
		//Cost
		ui->watchlistItemsTable->setItem(i, 2, new Gw2CurrencyTableWidgetItem(0));
		//Profit
		ui->watchlistItemsTable->setItem(i, 3, new Gw2CurrencyTableWidgetItem(0));
		//# Crafts
		ui->watchlistItemsTable->setItem(i, 4, new QTableWidgetItem(0));
		updateWatchlistRow(i, rows[i]);
	}
}

void BatchWindow::update() {
	updateShoppingListTable();
	updateOverflowTable();
	updateOutputTextFields();
}

bool BatchWindow::updateWatchlistRow(qint32 row, WatchlistRow &rowItem) {
	CraftingTreeRoot *cTree = &rowItem.craftingTree;
	CraftingTreeVertex* cTreeVertex = cTree->getVertex();
	QSpinBox *spinner = static_cast<QSpinBox*>(ui->watchlistItemsTable->cellWidget(row, 0));
	//Adjust value if the prevent overflow box is checked
	if(ui->preventOverflowCheckBox->isChecked()) {
		qint32 quantity = spinner->value();
		qint32 interval = cTreeVertex->findN();
		qint32 quantityModInterval = quantity % interval;
		if(quantityModInterval != 0) {
			spinner->setValue(quantity + quantityModInterval);
			//To prevent recursive signal calling.
			return false;
		}
	}
	cTree->setCount(spinner->value());
	ui->watchlistItemsTable->item(row, 2)->setText(Gw2Currency::string(cTreeVertex->totalCraftCost));
	ui->watchlistItemsTable->item(row, 3)->setText(Gw2Currency::string(cTree->getProfit()));
	ui->watchlistItemsTable->item(row, 4)->setText(QString::number(cTreeVertex->getCraftCount()));
	return true;
}

void BatchWindow::updateShoppingListTable() {
	QHash<qint32, QPair<qint32, qint32>> totalShoppingList;
	//make the total shopping list by combining all other shopping lists.
	for(qint32 row = 0; row < ui->watchlistItemsTable->rowCount(); ++row) {
		QString itemName = ui->watchlistItemsTable->item(row, 1)->text();
		qint32 index = findIndex(Gw2ItemDB::getItemID(itemName));
		CraftingTreeRoot *cTree = &rows[index].craftingTree;
		CraftingTreeVertex* cTreeVertex = cTree->getVertex();
		if(cTreeVertex->craftCount != 0) {
			QHash<qint32, QPair<qint32, qint32>> currentRowShoppingList = cTree->getShoppingList();
			for(auto iter = currentRowShoppingList.begin(); iter != currentRowShoppingList.end(); ++iter) {
				//Non-unique items get added to existing values
				if(totalShoppingList.contains(iter.key())) {
					qint32 totalQuantity = totalShoppingList.value(iter.key()).first,
						totalCost = totalShoppingList.value(iter.key()).second;
					totalQuantity += iter.value().first;
					totalCost += iter.value().second;
					totalShoppingList.insert(iter.key(), QPair<qint32, qint32>(totalQuantity, totalCost));
				} else
					totalShoppingList.insert(iter.key(), iter.value());
			}
		}
	}
	//Update the table
	ui->shoppingListTable->setRowCount(0);
	ui->shoppingListTable->setRowCount(totalShoppingList.keys().size());
	{
		qint32 row = 0; auto iter = totalShoppingList.begin();
		for(; row < ui->shoppingListTable->rowCount() && iter != totalShoppingList.end(); ++row, ++iter) {
			ui->shoppingListTable->setItem(row, 0, new QTableWidgetItem(Gw2ItemDB::getItemName(iter.key()), 0));
			ui->shoppingListTable->setItem(row, 1, new QTableWidgetItem(QString::number(iter.value().first), 0));
			ui->shoppingListTable->setItem(row, 2, new Gw2CurrencyTableWidgetItem(iter.value().second));
		}
	}
}

void BatchWindow::updateOverflowTable() {
	//Key is itemID second is ParentItemID, quantity
	QList<QPair<qint32, qint32>> totalOverflow;
	for(qint32 row = 0; row < ui->watchlistItemsTable->rowCount(); ++row) {
		CraftingTreeRoot *cTree = &rows[row].craftingTree;
		QList<QPair<qint32, qint32>> currentRowOverflow = cTree->getOverflow();
		//Non-unique items have their quantities added together.
		for(auto i : currentRowOverflow) {
			bool contains = false;
			for(auto j : totalOverflow) {
				if(j.first == i.first) {
					j.second += j.second;
					contains = true;
				}
			}
			if(!contains)
				totalOverflow << i;
		}
	}
	//Update the table
	ui->overflowTable->setRowCount(0);
	ui->overflowTable->setRowCount(totalOverflow.size());
	for(qint32 row = 0; row < ui->overflowTable->rowCount(); ++row) {
		ui->overflowTable->setItem(row, 0, new QTableWidgetItem(Gw2ItemDB::getItemName(totalOverflow[row].first), 0));
		ui->overflowTable->setItem(row, 1, new QTableWidgetItem(QString::number(totalOverflow[row].second), 0));
	}
}

void BatchWindow::updateOutputTextFields() {
	qint32 totalCost = 0, totalProfit = 0, totalCrafts = 0;
	for(qint32 row = 0; row < ui->watchlistItemsTable->rowCount(); ++row) {
		CraftingTreeRoot *cTree = &rows[row].craftingTree;
		CraftingTreeVertex* cTreeVertex = cTree->getVertex();
		totalCost += cTreeVertex->totalCraftCost;
		totalProfit += cTree->getProfit();
		totalCrafts += cTreeVertex->getCraftCount();
	}
	ui->estTotalInvestmentLineEdit->setText(Gw2Currency::string(totalCost));
	ui->estTotalProfitLineEdit->setText(Gw2Currency::string(totalProfit));
	ui->totalCraftsLineEdit->setText(QString::number(totalCrafts));
}


qint32 BatchWindow::getSpinnerRow(QObject *spinnerObj) {
	for(qint32 row = 0; row < ui->watchlistItemsTable->rowCount(); ++row) {
		if(spinnerObj == ui->watchlistItemsTable->cellWidget(row, 0))
			return row;
	}
	return -1;
}

void BatchWindow::on_preventOverflowCheckBox_toggled(bool checked)
{
	for(qint32 row = 0; row < ui->watchlistItemsTable->rowCount(); ++row) {
		CraftingTreeRoot *cTree = &rows[row].craftingTree;
		CraftingTreeVertex* cTreeVertex = cTree->getVertex();
		qint32 step = checked ? cTreeVertex->findN() : 1;
		QSpinBox *spinner = static_cast<QSpinBox*>(ui->watchlistItemsTable->cellWidget(row, 0));
		spinner->setSingleStep(step);
	}
}

qint32 BatchWindow::findIndex(qint32 itemID) {
	for(qint32 i = 0; i < rows.size(); ++i) {
		if(rows[i].itemID == itemID)
			return i;
	}
	return -1;
}
