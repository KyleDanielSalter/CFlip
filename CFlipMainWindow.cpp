#include "CFlipMainWindow.h"
#include "ui_CFlipMainWindow.h"
#include "WatchlistTabWidget.h"
#include <QDebug>
#include <QTime>
#include <QInputDialog>
#include <QMessageBox>
#include "WatchlistManager.h"
#include "Gw2Currency.h"
#include "Gw2ItemDB.h"
#include "Gw2ListingsParser.h"
#include "Gw2RecipesParser.h"
#include "RecipeTree.h"
#include "CraftingTree.h"
#include "Gw2RecipesDB.h"

CFlipMainWindow::CFlipMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::CFlipMainWindow)
{
	ui->setupUi(this);
	Gw2ItemDB::init();
	Gw2RecipesDB::init();
	WatchlistManager::init();
	QList<WatchlistTabWidget*> prevTabs = WatchlistManager::get();
	for(auto iter : prevTabs)
		ui->watchListTab->insertTab(ui->watchListTab->count() - 1, iter, iter->getName());
	ui->watchListTab->setCurrentIndex(0);
}

CFlipMainWindow::~CFlipMainWindow() {
	Gw2ItemDB::clear();
	Gw2RecipesDB::clear();
	WatchlistManager::clear();
	delete ui;
}

void CFlipMainWindow::on_watchListTab_tabCloseRequested(int index) {
	qint32 ret = QMessageBox::warning(this, "Closing Watchlist", "Closing a watchlist will delete all stored items. Are you sure?", QMessageBox::No, QMessageBox::Yes);
	if(ret == QMessageBox::Yes) {
		WatchlistTabWidget* tab = static_cast<WatchlistTabWidget*>(ui->watchListTab->widget(index));
		ui->watchListTab->removeTab(index);
		WatchlistManager::remove(tab);
	}

}

void CFlipMainWindow::on_actionNew_Watchlist_triggered()
{
	bool ok;
	QString name = QInputDialog::getText(this, tr("Enter New Watchlist Name"), tr("Watchlist Name:"),QLineEdit::Normal, "Untitled Watchlist", &ok);
	if(ok)
		ui->watchListTab->insertTab(ui->watchListTab->count() - 1, WatchlistManager::add(name), name);
}
