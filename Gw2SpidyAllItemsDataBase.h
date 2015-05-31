#ifndef GW2SPIDYALLITEMSDATABASE_H
#define GW2SPIDYALLITEMSDATABASE_H

#include <QHash>
#include <QStringList>
#include <QPair>

class Gw2SpidyAllItemsDataBase {
public:
	static void load();
	static QStringList getColumns();
	static QString getName(qint32 id);
	static qint32 getID(QString name);
	static QHash<QString, QString> getData(qint32 id);
	static QHash<QString, QString> getData(QString name);
private:
	static QString fileDir;
	static QStringList cols;
	static QHash<qint32, QString> idToName;
	static QHash<QString, qint32> nameToID;
	static QHash<qint32, QHash<QString, QString> > idToData;
	/*Removes qoutation marks from names, avoids problems with commas in names.
	  0 index is id, second, 1 is name, 2 is the formatted string*/
	static QStringList format(QString line);
};

#endif // GW2SPIDYALLITEMSDATABASE_H
