#ifndef CFLIPMAINWINDOW_H
#define CFLIPMAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QList>

namespace Ui {
	class CFlipMainWindow;
	class WatchListTabWidget;
}

class CFlipMainWindow : public QMainWindow {
	Q_OBJECT
public:
	explicit CFlipMainWindow(QWidget *parent = 0);
	~CFlipMainWindow();

private slots:
	void on_watchListTab_tabBarClicked(int index);

private:
	Ui::CFlipMainWindow *ui;
	QList<std::shared_ptr<Ui::WatchListTabWidget>> watchListTabWidgetList;
};

#endif // CFLIPMAINWINDOW_H
