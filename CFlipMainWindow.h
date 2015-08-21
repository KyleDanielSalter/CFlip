#ifndef CFLIPMAINWINDOW_H
#define CFLIPMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
	class CFlipMainWindow;
}

class CFlipMainWindow : public QMainWindow {
	Q_OBJECT
public:
	explicit CFlipMainWindow(QWidget *parent = 0);
	~CFlipMainWindow();

private slots:
	void on_watchListTab_tabBarClicked(int index);

	void on_pushButton_clicked();

private:
	Ui::CFlipMainWindow *ui;
};

#endif // CFLIPMAINWINDOW_H
