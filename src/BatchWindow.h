#ifndef BATCHWINDOW_H
#define BATCHWINDOW_H

#include <QWidget>
#include <WatchlistTabWidget.h>

namespace Ui {
	class BatchWindow;
}


class BatchWindow : public QWidget {
	Q_OBJECT
public:
	explicit BatchWindow(
		QList<WatchlistRow> rows,
		QWidget *parent = 0);
	~BatchWindow();
public slots:
	void watchlistRowQuantityChanged();
private slots:
	void on_preventOverflowCheckBox_toggled(bool checked);
private:
	Ui::BatchWindow *ui;
	QList<WatchlistRow> rows;
	void init();
	void initWatchlistTable();
	void update();
	bool updateWatchlistRow(qint32 row, WatchlistRow &rowItem);
	void updateShoppingListTable();
	void updateOverflowTable();
	void updateOutputTextFields();
	qint32 getSpinnerRow(QObject *spinnerObj);
	qint32 findIndex(qint32 itemID);
};

#endif // BATCHWINDOW_H
