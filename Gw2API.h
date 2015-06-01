#ifndef GW2API_H
#define GW2API_H

#include <QObject>
#include <QString>
#include <QURL>
#include <memory>

class QNetworkAccessManager;

class Gw2API : public QObject {
	Q_OBJECT;
public:
	Gw2API(QString URI, QString params = QString(), QObject *parent = nullptr);
	QString get();
	QUrl getURL();
	void setURI(QString newURI);
	void setParams(QString newParams);
private:
	static QString gw2APIURLStr;
	QString URI;
	QString params;
	QString data;
	std::shared_ptr<QNetworkAccessManager> NAM;
};

#endif // GW2API_H
