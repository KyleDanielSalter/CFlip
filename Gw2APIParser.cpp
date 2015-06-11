#include "Gw2APIParser.h"
#include "Gw2APIResult.h"

Gw2API* Gw2APIParser::getAPIEndPoint() {
	return nullptr;
}
Gw2API* Gw2APIParser::getMultiAPIEndPoint() {
	return nullptr;
}

std::shared_ptr<Gw2APIResult> Gw2APIParser::parse(qint32 id) {
	return std::shared_ptr<Gw2APIResult>(new Gw2APIResult(id));
}

QHash<qint32, std::shared_ptr<Gw2APIResult>> Gw2APIParser::multiHashParse(
	QList<qint32> id)
{
	id.clear();
	return QHash<qint32, std::shared_ptr<Gw2APIResult>>();
}

QList<std::shared_ptr<Gw2APIResult>> Gw2APIParser::multiListParse(
	QList<qint32> id)
{
	id.clear();
	return QList<std::shared_ptr<Gw2APIResult>>();
}
