#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H

#include <QObject>
#include <QPixmap>
#include <QByteArray>

class ImageDownloader : public QObject {
	Q_OBJECT
public:
	static QPixmap get(QString url);
	static QByteArray getImageAsByteArray(QString url);
};

#endif // IMAGEDOWNLOADER_H
