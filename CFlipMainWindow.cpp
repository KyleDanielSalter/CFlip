#include "CFlipMainWindow.h"
#include "ui_CFlipMainWindow.h"
#include <qDebug>
#include "Gw2ItemDB.h"
#include "Gw2ListingsParser.h"
#include "CraftingItem.h"

CFlipMainWindow::CFlipMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::CFlipMainWindow)
{
	ui->setupUi(this);
	Gw2ItemDB::init();
	CraftingItem test(12725, CraftingItem::BUY, CraftingItem::SELL, 3);
	test.print();
}

CFlipMainWindow::~CFlipMainWindow() {
	Gw2ItemDB::clear();
	delete ui;
}
