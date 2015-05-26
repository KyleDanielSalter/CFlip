#include "CFlipMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CFlipMainWindow w;
	w.show();

	return a.exec();
}
