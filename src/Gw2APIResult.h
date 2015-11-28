#ifndef GW2APIRESULT_H
#define GW2APIRESULT_H

#include <QtGlobal>

class Gw2APIResult {
public:
	Gw2APIResult();
	Gw2APIResult(qint32 id);
protected:
	qint32 id;
};

#endif // GW2APIRESULT_H
