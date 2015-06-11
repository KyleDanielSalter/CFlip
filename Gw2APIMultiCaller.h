#ifndef GW2APIMULTICALLER_H
#define GW2APIMULTICALLER_H

#include <memory>
#include <QHash>

class Gw2APIParser;
class Gw2APIResult;

class Gw2APIMultiCaller {
public:
	Gw2APIMultiCaller(Gw2APIParser *parser);
	void add(qint32 id, std::shared_ptr<Gw2APIResult> *storageObjPtr);
	void load();
	void clearStorageHash();
private:
	std::shared_ptr<Gw2APIParser> parser;
	QHash<qint32, std::shared_ptr<Gw2APIResult>*> storObjPtrHash;
};

#endif // GW2APIMULTICALLER_H
