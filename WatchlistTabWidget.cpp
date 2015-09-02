#include "WatchListTabWidget.h"
#include "ui_WatchListTabWidget.h"
#include <QHash>
#include "Gw2ItemDB.h"
#include "ImageDownloader.h"
#include "Gw2Currency.h"

WatchListTabWidget::WatchListTabWidget(
	QString name,
	QList<qint32> itemIDs,
	QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::WatchListTabWidget)
	, name(name)
	, itemIDs(itemIDs)
{
    ui->setupUi(this);
	init();
}

WatchListTabWidget::~WatchListTabWidget() {
    delete ui;
}

WatchListTabWidget::WatchlistRow::WatchlistRow(qint32 itemID)
	: itemID(itemID)
	, craftingTree(itemID)
{
	QString itemName(Gw2ItemDB::getItemName(itemID)),
		iconUrl(Gw2ItemDB::getIconUrl(itemID)),
		adjBS(Gw2Currency::string(craftingTree.getAdjBS())),
		adjCS(Gw2Currency::string(craftingTree.getProfit()));
	std::shared_ptr<QTableWidgetItem> itemNameTableItem(new QTableWidgetItem(itemName, 0));
	std::shared_ptr<QTableWidgetItem> iconTableItem(new QTableWidgetItem(QIcon(ImageDownloader::get(iconUrl)), 0));
	std::shared_ptr<QTableWidgetItem> adjBSTableItem(new QTableWidgetItem(adjBS, 0));
	std::shared_ptr<QTableWidgetItem> adjCSTableItem(new QTableWidgetItem(adjCS, 0));
	tableItems << iconTableItem;
	tableItems << itemNameTableItem;
	tableItems << adjBSTableItem;
	tableItems << adjCSTableItem;
}

void WatchListTabWidget::init() {
	//fill out table
	ui->tableWidget->setRowCount(itemIDs.size());
	for(qint32 row = 0; row < itemIDs.size(); ++row) {
		tableRows.append(WatchlistRow(itemIDs[row]));
		WatchlistRow *watchlistRow = &tableRows.back();
		for(qint32 col = 0; col < watchlistRow->tableItems.size(); ++col) {
			ui->tableWidget->setItem(row, col, watchlistRow->tableItems[col].get());
		}
	}
}
