#include "CFlipMainWindow.h"
#include "ui_CFlipMainWindow.h"
#include <qDebug>
#include "Gw2ItemDB.h"

CFlipMainWindow::CFlipMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::CFlipMainWindow)
{
	ui->setupUi(this);
	Gw2ItemDB::init();
	auto testhash = Gw2ItemDB::getIDIconUrlHashMap();
	QString test = testhash[1];
}

CFlipMainWindow::~CFlipMainWindow() {
	delete ui;
}
