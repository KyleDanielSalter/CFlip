#ifndef GW2API_H
#define GW2API_H

#include <QObject>
#include <QStringList>
#include <QUrl>
#include <memory>

class QNetworkAccessManager;

class Gw2API : public QObject {
	Q_OBJECT
public:
	Gw2API();
	Gw2API(QString URI, QString params = QString(), QObject *parent = nullptr);
	QString get();
	QUrl getURL();
	void setParams(QString newParams);
	void loadEndPointIDList();
	bool checkID(qint32 id);
	QList<qint32> getEndPointIDList();
	static QStringList intIDListToStringList(QList<qint32> idList);
private:
	static QString gw2APIURLStr;
	const QString URI;
	QString params;
	QList<qint32> endPointIDList;
	std::shared_ptr<QNetworkAccessManager> NAM;
	void openNAM();
	void closeNAM();
};

#endif // GW2API_H
