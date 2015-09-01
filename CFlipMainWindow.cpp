#include "CFlipMainWindow.h"
#include "ui_CFlipMainWindow.h"
#include "WatchListTabWidget.h"
#include <QDebug>
#include <QTime>
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
	CraftingTreeRoot cTree(12725);
	cTree.printTree();
}

CFlipMainWindow::~CFlipMainWindow() {
	Gw2ItemDB::clear();
	Gw2RecipesDB::clear();
	delete ui;
}

void CFlipMainWindow::on_watchListTab_tabBarClicked(int index)
{
	if(index == ui->watchListTab->count() - 1) {
		ui->watchListTab->insertTab(index, new WatchListTabWidget("TEST", {1,2,3,4}), "TEST");
		ui->watchListTab->setCurrentIndex(index - 1);
	}
}
