#include "Gw2Currency.h"
#include <QDebug>

Gw2Currency::Gw2Currency() : valueNum(0)
{}

Gw2Currency::Gw2Currency(const Gw2Currency &currency)
	: valueNum(currency.getNum())
{}

Gw2Currency::Gw2Currency(const QString priceString)
	: valueNum(convert(priceString))
{}

Gw2Currency::Gw2Currency(const qint32 valueNum) : valueNum(valueNum)
{}

qint32 Gw2Currency::convert(QString priceString) {
	/* Currency is XX...g YYs ZZc, X being #gold, Y being #silver, Z being #copper.
	 * All spaces and alphabetical characters are removed
	 * Last two characters is the copper quantity, 0-99
	 * The next two to the left is the silver quantity, 0-99
	 * The first character to the character right before the last 4 is the
	 * gold quantity.
	 * Note that there are no trailing digits. 1 == 1 copper, not 1 gold
	 * 119 == 1 silver, 19 gold, 1119 == 11 silver, 19 gold
	 * 1111119 == 119 gold, 11 silver, 19 copper
	 * 001, 00001, are valid inputs but are improper form.
	 * If the price is a negative value, the first character is a '-';
	*/
	qint32 gold(0), silver(0), copper(0), ret(0); bool isNumber(false), isNegative(false);
	if(!priceString.isEmpty()) {
		//Format the string into all integers.
		priceString.remove(' ',Qt::CaseInsensitive);
		priceString.remove('g',Qt::CaseInsensitive);
		priceString.remove('s',Qt::CaseInsensitive);
		priceString.remove('c',Qt::CaseInsensitive);
		//Now check for proper format
		priceString.toInt(&isNumber);
		if(isNumber && !priceString.isEmpty()) {

		} else {
			qDebug() << "Error converting price string '" + priceString + "' to Gw2Currency: String is not in an integer format.";
			return 0;
		}
	} else
		qDebug << "Error converting price string '" + priceString + "' to Gw2Currency: String is empty.";
	return 0;
}

QString Gw2Currency::convert(qint32 valueNum) {
	QString ret;
	bool isNegative; qint32 gold, silver, copper;
	getGSC(valueNum, &isNegative, &gold, &silver, &copper);
	if(isNegative)
		ret += "-";
	if(gold != 0)
		ret += QString::number(gold) + "g ";
	if(silver != 0)
		ret += QString::number(silver) + "s ";
	ret += QString::number(copper) + "c";
	return ret;
}

void Gw2Currency::getGSC(
	qint32 valueNum,
	bool *isNegative = false,
	qint32 *goldOut = 0,
	qint32 *silverOut = 0,
	qint32 *copperOut = 0)
{
	QString raw(QString::number(valueNum));
	//Check for negativity, if true, remove the dash
	if(valueNum < 0) {
		*isNegative = true;
		raw.remove[0];
	}
	//Last two characters will always be the copper quantity, remove
	*copperOut = raw.right(2).toInt();
	raw.chop(2);
	//Now the last two will be the silver quantity, but only if the
	//string is not empty at this point.
	if(!raw.isEmpty()) {
		*silverOut = raw.right(2).toInt();
		//use the rest string for the gold quantity if its not empty.
		if(!raw.isEmpty())
			*goldOut = raw.toInt();
	}
}

qint32 Gw2Currency::getNum() const {

}

QString Gw2Currency::getString() const {

}

Gw2Currency& Gw2Currency::operator=(const Gw2Currency &other) {

}

Gw2Currency& Gw2Currency::operator=(const qint32 &num) {

}

Gw2Currency& Gw2Currency::operator=(const QString &string) {

}

Gw2Currency& Gw2Currency::operator+=(const Gw2Currency &rhs) {

}

Gw2Currency& Gw2Currency::operator-=(const Gw2Currency &rhs) {

}

Gw2Currency& Gw2Currency::operator*=(const Gw2Currency &rhs) {

}

Gw2Currency& Gw2Currency::operator/=(const Gw2Currency &rhs) {

}
