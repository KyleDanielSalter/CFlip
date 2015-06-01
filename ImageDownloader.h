#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H

#include <memory>
#include <QObject>
#include <QPixmap>
#include <QByteArray>

class QNetworkAccessManager;

class ImageDownloader : public QObject
{
	Q_OBJECT
public:
	explicit ImageDownloader(QObject *parent = 0);
	QPixmap get(QString url);
	QByteArray getImageAsByteArray(QString url);
private:
	std::shared_ptr<QNetworkAccessManager> NAM;
};

#endif // IMAGEDOWNLOADER_H
