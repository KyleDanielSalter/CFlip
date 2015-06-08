#include "CFlipMainWindow.h"
#include "ui_CFlipMainWindow.h"
#include <qDebug>
#include "Gw2ItemDB.h"
#include "Gw2Currency.h"
#include "Gw2ListingsParser.h"
#include "Gw2RecipesParser.h"

CFlipMainWindow::CFlipMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::CFlipMainWindow)
{
	ui->setupUi(this);
	//Gw2ItemDB::init();
	auto test = Gw2RecipesParser::getItemRecipe("46731");
}

CFlipMainWindow::~CFlipMainWindow() {
	Gw2ItemDB::clear();
	delete ui;
}
