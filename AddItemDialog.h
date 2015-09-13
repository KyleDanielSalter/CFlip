#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QHash>
#include <QPair>

namespace Ui {
	class AddItemDialog;
}

class AddItemDialog : public QDialog {
	Q_OBJECT

public:
	explicit AddItemDialog(QWidget *parent = 0);
	~AddItemDialog();
	QList<qint32> start(bool &ok);
private slots:
	void on_searchQueryLineEdit_textEdited(const QString &arg1);

	void on_rarityListWidget_itemSelectionChanged();

	void on_levelGroupBox_toggled(bool arg1);

	void on_minLevelSpinBox_valueChanged(int arg1);

	void on_maxLevelSpinBox_valueChanged(int arg1);

	void on_itemTypeTreeWidget_itemSelectionChanged();


	void on_cancelButton_clicked();

	void on_okButton_clicked();

private:
	struct SearchParameters {
		SearchParameters();
		SearchParameters(
			QString str,
			QHash<QString, QStringList> types,
			QPair<qint32, qint32> levelRange,
			QStringList rarities);
		QString str;
		QHash<QString, QStringList> types;
		QPair<qint32, qint32> levelRange;
		QStringList rarities;
	};

	Ui::AddItemDialog *ui;
	bool *okPtr;
	SearchParameters params;
	QStringList allItemNames;
	QStringList results;
	void search();
	bool check(QString comp);
	bool checkSearchString(QString comp);
	bool checkTypes(QJsonObject &jsonObj);
	bool checkLevelRange(QJsonObject &jsonObj);
	bool checkRarity(QJsonObject &jsonObj);
	void updateSearchParameters();
	QHash<QString, QStringList> getTypes();
	QPair<qint32, qint32> getLevelRange();
	QStringList getRarities();
	void updateSearchResults();
	QList<qint32> getReturn();
};

#endif // ADDITEMDIALOG_H
