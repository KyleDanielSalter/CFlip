#include "CFlipMainWindow.h"
#include "ui_CFlipMainWindow.h"
#include "Gw2SpidyAllItemsDataBase.h"
#include <qDebug>

CFlipMainWindow::CFlipMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::CFlipMainWindow)
{
	ui->setupUi(this);
	Gw2SpidyAllItemsDataBase::load();
	auto test = Gw2SpidyAllItemsDataBase::getData(0);
}

CFlipMainWindow::~CFlipMainWindow() {
	delete ui;
}
