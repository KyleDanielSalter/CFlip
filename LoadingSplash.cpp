#include "LoadingSplash.h"
#include "ui_LoadingSplash.h"

LoadingSplash::LoadingSplash(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LoadingSplash)
{
	ui->setupUi(this);
	setWindowTitle("Loading CFlip...");
	setWindowFlags(Qt::FramelessWindowHint);
}

LoadingSplash::~LoadingSplash()
{
	delete ui;
}
