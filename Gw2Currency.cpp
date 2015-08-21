#include "Gw2Currency.h"
#include <QDebug>
#include <QChar>

QString Gw2Currency::string(qint32 number) {
	QString ret;
	qint32 gold(0), silver(0), copper(0);
	GSC(number, &gold, &silver, &copper);
	ret += gold == 0 ? "" : QString::number(gold) + "g ";
	ret += silver == 0 ? "" : QString::number(silver) + "s ";
	ret += copper == 0 ? "" : QString::number(copper) + "c";
	if(gold == 0 && silver == 0 && copper == 0)
		ret += "0c";
	return ret;
}

qint32 Gw2Currency::number(QString string) {
	bool isNegative(false);
	qint32 gold(0), silver(0), copper(0);
	if(!string.isEmpty()) {
		//If the string contains a '-', it is a negative value, remove any dashes
		isNegative = string.contains('-');
		if(isNegative)
			string.remove("-", Qt::CaseInsensitive);
		//Separate by spaces into a list
		QStringList strList = string.split(" ");
		for(auto i = strList.begin(); i != strList.end(); ++i) {
			QString str = *i;
			if(str.contains("g", Qt::CaseInsensitive)) {
				str.remove("g", Qt::CaseInsensitive);
				gold = str.toInt();
			}
			else if (str.contains("s", Qt::CaseInsensitive)) {
				str.remove("s", Qt::CaseInsensitive);
				silver = str.toInt();
			}
			else if(str.contains("c", Qt::CaseInsensitive)) {
				str.remove("c", Qt::CaseInsensitive);
				copper = str.toInt();
			} else
				qDebug() << "Error converting Gw2Currency string " + str + " to a number";
		}
		qint32 num = gold * 10000 + silver * 100 + copper;
		return isNegative ? num * -1 : num;
	} else
		qDebug() << "Error converting price string '" + string + "' to Gw2Currency: String is empty.";
	return 0;
}

void Gw2Currency::GSC(qint32 number,
	qint32 *goldOut,
	qint32 *silverOut,
	qint32 *copperOut)
{
	QString raw(QString::number(number));
	//Check for negativity, if true, remove the dash
	if(number < 0)
		raw.remove(0, 1);
	//Last two characters will always be the copper quantity, remove
	*copperOut = number < 0 ? raw.right(2).toInt() * -1 : raw.right(2).toInt();
	raw.chop(2);
	//Now the last two will be the silver quantity, but only if the
	//string is not empty at this point.
	if(!raw.isEmpty()) {
		*silverOut = number < 0 ? raw.right(2).toInt() * -1 : raw.right(2).toInt();
		raw.chop(2);
		//use the rest string for the gold quantity if its not empty.
		if(!raw.isEmpty())
			*goldOut = number < 0 ? raw.toInt() * -1 : raw.toInt();
	}
}

void Gw2Currency::GSC(
	QString string,
	qint32 *goldOut,
	qint32 *silverOut,
	qint32 *copperOut)
{
	GSC(number(string), goldOut, silverOut, copperOut);
}
