#include "Gw2API.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonArray>

QString Gw2API::gw2APIURLStr = "https://api.guildwars2.com/v2/";

Gw2API::Gw2API(QString URI, QString params, QObject *parent)
	: QObject(parent)
	, URI(URI)
	, params(params)
{}

QString Gw2API::get() {
	openNAM();
	QNetworkReply* reply = NAM->get(QNetworkRequest(getURL()));
	QEventLoop eventLoop;
	connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
	eventLoop.exec();
	if(reply->error() == QNetworkReply::NoError)
		return (QString)reply->readAll();
	else
		qDebug() << "Error querying the Gw2 API. Error string: " + reply->errorString();
	closeNAM();
	return QString();
}

QUrl Gw2API::getURL() {
	return QUrl(gw2APIURLStr + URI + params);
}

void Gw2API::setParams(QString newParams) {
	params = newParams;
}

void Gw2API::loadEndPointIDList() {
	//Querying onlt the endpoint (no params) returns list of all IDs
	//For some logical reason I could not figure out, leaving the backslash
	//returned an empty string.
	QString uriNoSlash = URI;
	uriNoSlash.remove("/", Qt::CaseInsensitive);
	Gw2API endPoint(uriNoSlash);
	QString dataString = endPoint.get();
	if(!dataString.isEmpty()) {
		QJsonDocument jsonDoc = QJsonDocument::fromJson(dataString.toUtf8());
		QJsonArray jsonArray = jsonDoc.array();
		for(auto i : jsonArray)
			endPointIDList << i.toInt();
	} else
		qDebug() << "Error loading End Point IDs for URI: " + URI;
}

bool Gw2API::checkID(qint32 id) {
	if(endPointIDList.isEmpty())
		loadEndPointIDList();
	return endPointIDList.contains(id);
}

QList<qint32> Gw2API::getEndPointIDList() {
	if(endPointIDList.isEmpty())
		loadEndPointIDList();
	return endPointIDList;
}

QStringList Gw2API::intIDListToStringList(QList<qint32> idList) {
	QStringList ret;
	for(auto i : idList)
		ret << QString::number(i);
	return ret;
}

void Gw2API::openNAM() {
	NAM = std::shared_ptr<QNetworkAccessManager>(new QNetworkAccessManager(this));
}

void Gw2API::closeNAM() {
	NAM.reset();
}
