#ifndef GW2CURRENCY_H
#define GW2CURRENCY_H

#include <QString>

class Gw2Currency {
public:
	Gw2Currency();
	Gw2Currency(const Gw2Currency &currency);
	Gw2Currency(const QString priceString);
	Gw2Currency(const qint32 valueNum);
	static qint32 convert(QString priceString);
	static QString convert(qint32 valueNum);
	static void getGSC(
		qint32 valueNum,
		bool *isNegative,
		qint32 *goldOut,
		qint32 *silverOut,
		qint32 *copperOut);
	qint32 getNum()const;
	QString getString()const;
	Gw2Currency& operator=(const Gw2Currency &other);
	Gw2Currency& operator=(const qint32 &num);
	Gw2Currency& operator=(const QString &string);
	friend bool operator<(const Gw2Currency &lhs, const Gw2Currency &rhs);
	friend bool operator>(const Gw2Currency &lhs, const Gw2Currency &rhs);
	friend bool operator<=(const Gw2Currency &lhs, const Gw2Currency &rhs);
	friend bool operator>=(const Gw2Currency &lhs, const Gw2Currency &rhs);
	friend bool operator==(const Gw2Currency &lhs, const Gw2Currency &rhs);
	friend bool operator!=(const Gw2Currency &lhs, const Gw2Currency &rhs);
	Gw2Currency& operator+=(const Gw2Currency &rhs);
	Gw2Currency& operator-=(const Gw2Currency &rhs);
	Gw2Currency& operator*=(const Gw2Currency &rhs);
	Gw2Currency& operator/=(const Gw2Currency &rhs);
	friend Gw2Currency operator+(const Gw2Currency &lhs, const Gw2Currency &rhs);
	friend Gw2Currency operator-(const Gw2Currency &lhs, const Gw2Currency &rhs);
	friend Gw2Currency operator*(const Gw2Currency &lhs, const Gw2Currency &rhs);
	friend Gw2Currency operator/(const Gw2Currency &lhs, const Gw2Currency &rhs);
private:
	qint32 valueNum;
};

inline bool Gw2Currency::operator<(
	const Gw2Currency &lhs,
	const Gw2Currency &rhs)
{

}

inline bool Gw2Currency::operator>(
	const Gw2Currency &lhs,
	const Gw2Currency &rhs)
{

}

inline bool Gw2Currency::operator<=(
	const Gw2Currency &lhs,
	const Gw2Currency &rhs)
{

}

inline bool Gw2Currency::operator>=(
	const Gw2Currency &lhs,
	const Gw2Currency &rhs)
{

}

inline bool Gw2Currency::operator==(
	const Gw2Currency &lhs,
	const Gw2Currency &rhs)
{

}

inline bool Gw2Currency::operator!=(
	const Gw2Currency &lhs,
	const Gw2Currency &rhs)
{

}

inline Gw2Currency Gw2Currency::operator+(
	const Gw2Currency &lhs,
	const Gw2Currency &rhs)
{

}

inline Gw2Currency Gw2Currency::operator-(
	const Gw2Currency &lhs,
	const Gw2Currency &rhs)
{

}

inline Gw2Currency Gw2Currency::operator*(
	const Gw2Currency &lhs,
	const Gw2Currency &rhs)
{

}

inline Gw2Currency Gw2Currency::operator/(
	const Gw2Currency &lhs,
	const Gw2Currency &rhs)
{

}

#endif // GW2CURRENCY_H
