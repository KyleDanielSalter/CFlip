#include "Gw2APIMultiCaller.h"
#include "Gw2API.h"
#include "Gw2APIParser.h"

Gw2APIMultiCaller::Gw2APIMultiCaller(Gw2APIParser *parser) : parser(parser)
{}

void Gw2APIMultiCaller::add(qint32 id, std::shared_ptr<Gw2APIResult> *storageObj) {
	storObjPtrHash.insert(id, storageObj);
}

void Gw2APIMultiCaller::load() {
	QList<qint32> ids = storObjPtrHash.keys();
	QHash<qint32, std::shared_ptr<Gw2APIResult>> result = parser->multiHashParse(ids);
	for(auto iter = result.begin(); iter != result.end(); ++iter) {
		std::shared_ptr<Gw2APIResult> ptr = iter.value();
		*storObjPtrHash[iter.key()] = ptr;
	}
	//clearStorageHash();
}

void Gw2APIMultiCaller::clearStorageHash() {
	storObjPtrHash.clear();
}
