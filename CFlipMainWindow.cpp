#include "CFlipMainWindow.h"
#include "ui_CFlipMainWindow.h"
#include <qDebug>
#include "Gw2ItemDB.h"
#include "Gw2ListingsParser.h"
#include "Gw2RecipesParser.h"
#include "RecipeTree.h"
#include "Gw2RecipeDB.h"

CFlipMainWindow::CFlipMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::CFlipMainWindow)
{
	ui->setupUi(this);
	Gw2ItemDB::init();
	Gw2RecipeDB::init();
	RecipeTreeRoot rTree(12725);
	rTree.print();
	//CraftingItem test(12725, CraftingItem::BUY, CraftingItem::SELL, 3);
	//test.print();
}

CFlipMainWindow::~CFlipMainWindow() {
	Gw2ItemDB::clear();
	delete ui;
}
