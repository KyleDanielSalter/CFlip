#include "CFlipMainWindow.h"
#include "ui_CFlipMainWindow.h"

CFlipMainWindow::CFlipMainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::CFlipMainWindow)
{
	ui->setupUi(this);
}

CFlipMainWindow::~CFlipMainWindow()
{
	delete ui;
}
