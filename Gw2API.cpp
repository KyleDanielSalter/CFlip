#include "Gw2API.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

QString Gw2API::gw2APIURLStr = "https://api.guildwars2.com/v2/";

Gw2API::Gw2API(QString URI, QString params, QObject *parent)
	: QObject(parent)
	, NAM(new QNetworkAccessManager(this))
	, URI(URI)
	, params(params)
{}

QString Gw2API::get() {
	QNetworkReply* reply = NAM->get(QNetworkRequest(getURL()));
	QEventLoop eventLoop;
	connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
	eventLoop.exec();
	if(reply->error() == QNetworkReply::NoError) {
		data = (QString)reply->readAll();
	} else
		qDebug() << "Error querying the Gw2 API. Error string: " + reply->errorString();
	return data;
}

QUrl Gw2API::getURL() {
	return QUrl(gw2APIURLStr + URI + params);
}

void Gw2API::setURI(QString newURI) {
	URI = newURI;
}

void Gw2API::setParams(QString newParams) {
	params = newParams;
}
