#ifndef GW2APIPARSER_H
#define GW2APIPARSER_H

#include <QString>
#include <QHash>
#include <QList>
#include <memory>

class Gw2API;
class Gw2APIResult;

class Gw2APIParser {
public:
	virtual Gw2API* getAPIEndPoint();
	virtual Gw2API* getMultiAPIEndPoint();
	virtual std::shared_ptr<Gw2APIResult> parse(qint32 id);
	virtual QHash<qint32, std::shared_ptr<Gw2APIResult>> multiHashParse(QList<qint32> id);
	virtual QList<std::shared_ptr<Gw2APIResult>> multiListParse(QList<qint32> id);
};

#endif // GW2APIPARSER_H
