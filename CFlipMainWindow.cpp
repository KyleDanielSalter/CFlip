#include "CFlipMainWindow.h"
#include "ui_CFlipMainWindow.h"
#include <qDebug>
#include <QTime>
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
	QTime t; t.start();
	RecipeTreeRoot rTree(12720);
	qDebug("Time elapsed: %d ms", t.elapsed());
	rTree.print();
	qDebug() << rTree.findN();
}

CFlipMainWindow::~CFlipMainWindow() {
	Gw2ItemDB::clear();
	delete ui;
}
