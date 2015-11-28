#include "ImageDownloader.h"
#include <QDebug>
#include <QByteArray>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>


QPixmap ImageDownloader::get(QString url) {
	return QPixmap(getImageAsByteArray(url));
}

QByteArray ImageDownloader::getImageAsByteArray(QString url) {
	QByteArray ret;
	QNetworkAccessManager NAM;
	QNetworkReply* reply = NAM.get(QNetworkRequest(QUrl(url)));
	QEventLoop eventLoop;
	connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
	eventLoop.exec();
	if(reply->error() == QNetworkReply::NoError) {
		ret = reply->readAll();
	} else
		qDebug() << "Error querying downloading image from url:" + url + "Error string: " + reply->errorString();
	return ret;
}
