#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H

#include <QObject>
#include <QPixmap>
#include <QByteArray>

class ImageDownloader : public QObject
{
	Q_OBJECT
public:
	explicit ImageDownloader(QObject *parent = 0);
	QPixmap get(QString url);
	QByteArray getImageAsByteArray(QString url);
};

#endif // IMAGEDOWNLOADER_H
