#ifndef GW2ITEMPARSER_H
#define GW2ITEMPARSER_H

#include <QStringList>

class Gw2ItemIDListParser
{
public:
	static QStringList get();
private:
	static QString itemIDListURI;
};

#endif // GW2ITEMPARSER_H
