#ifndef GW2CURRENCY_H
#define GW2CURRENCY_H

#include <QString>
#include <QTableWidgetItem>

class Gw2CurrencyTableWidgetItem : public QObject, public QTableWidgetItem {
	Q_OBJECT
public:
	Gw2CurrencyTableWidgetItem(qint32 value);
	Gw2CurrencyTableWidgetItem(QString valueStr);
	bool operator<(const QTableWidgetItem & other) const;
};

class Gw2Currency {
public:
	static QString string(qint32 number);
	static qint32 number(QString string);
	static void GSC(
		qint32 number,
		qint32 *goldOut,
		qint32 *silverOut,
		qint32 *copperOut);
	static void GSC(
		QString string,
		qint32 *goldOut,
		qint32 *silverOut,
		qint32 *copperOut);
};

#endif // GW2CURRENCY_H
