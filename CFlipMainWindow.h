#ifndef CFLIPMAINWINDOW_H
#define CFLIPMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
	class CFlipMainWindow;
}

class CFlipMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit CFlipMainWindow(QWidget *parent = 0);
	~CFlipMainWindow();

private:
	Ui::CFlipMainWindow *ui;
};

#endif // CFLIPMAINWINDOW_H
