#include "CFlipMainWindow.h"
#include "ui_CFlipMainWindow.h"
#include <qDebug>
#include <QTime>
#include "Gw2ItemDB.h"
#include "Gw2ListingsParser.h"
#include "Gw2APIResult.h"
#include "Gw2APIMultiCaller.h"

CFlipMainWindow::CFlipMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::CFlipMainWindow)
{
	ui->setupUi(this);
	//Gw2ItemDB::init();
	//QTime t; t.start();
	//CraftingItem testItem(12725, CraftingItem::BUY, CraftingItem::SELL, 1);
	//qDebug("Time elapsed: %d ms", t.elapsed());
}

CFlipMainWindow::~CFlipMainWindow() {
	Gw2ItemDB::clear();
	delete ui;
}
