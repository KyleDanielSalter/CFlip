#ifndef CFLIPMAINWINDOW_H
#define CFLIPMAINWINDOW_H

#include <memory>
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
	void on_watchListTab_tabCloseRequested(int index);
	void on_actionNew_Watchlist_triggered();
	void on_watchListTab_tabBarDoubleClicked(int index);

private:
	Ui::CFlipMainWindow *ui;
};

#endif // CFLIPMAINWINDOW_H
