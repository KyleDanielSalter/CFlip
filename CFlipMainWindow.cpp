#include "CFlipMainWindow.h"
#include "ui_CFlipMainWindow.h"
#include <qDebug>
#include "Gw2ItemDB.h"
#include "Gw2ListingsParser.h"
#include "Gw2RecipesParser.h"
#include "RecipeTree.h"
#include "Gw2RecipesDB.h"

CFlipMainWindow::CFlipMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::CFlipMainWindow)
{
	ui->setupUi(this);
	Gw2ItemDB::init();
	Gw2RecipesDB::init();
	RecipeTreeRoot rTree(12725);
	rTree.print();
}

CFlipMainWindow::~CFlipMainWindow() {
	Gw2ItemDB::clear();
	delete ui;
}
