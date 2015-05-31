#include "Gw2SpidyAllItemsDataBase.h"
#include <QDebug>
#include <QFile>

QString Gw2SpidyAllItemsDataBase::fileDir = "data/all.txt";
QStringList Gw2SpidyAllItemsDataBase::cols;
QHash<qint32, QString> Gw2SpidyAllItemsDataBase::idToName;
QHash<QString, qint32> Gw2SpidyAllItemsDataBase::nameToID;
QHash<qint32, QHash<QString, QString> > Gw2SpidyAllItemsDataBase::idToData;

void Gw2SpidyAllItemsDataBase::load() {
	QFile itemDB(fileDir);
	if(itemDB.open(QIODevice::ReadOnly)) {
		//First line is the column, if not proper format, no data will be loaded
		QString firstLine = itemDB.readLine(); firstLine.chop(2); //removes \r\n
		cols = firstLine.split(',', QString::SkipEmptyParts);
		while(!itemDB.atEnd()) {
			QString line = itemDB.readLine(); line.chop(2);
			//0 is id, 1 is name, 2 is the formatted data
			QStringList idNameDataList = format(line);
			QStringList values = idNameDataList[2].split(",", QString::SkipEmptyParts);
			QHash<QString, QString> row;
			row[cols[0]] = idNameDataList[0]; row[cols[1]] = idNameDataList[1];
			//Key = name of column, Value = matching index from column in values
			//Skips id and name, format removed them.
			for(int i = 0; i < values.size(); ++i) {
				row[cols[i + 2]] = values[i];
			}

			idToName[idNameDataList[0].toInt()] = idNameDataList[1];
			nameToID[idNameDataList[1]] = idNameDataList[0].toInt();
			idToData[idNameDataList[0].toInt()] = row;
		}
	} else
		qDebug() << "Error opening " + fileDir + " '" + itemDB.errorString() + "'";
}

QStringList Gw2SpidyAllItemsDataBase::getColumns() {
	return cols;
}

QString Gw2SpidyAllItemsDataBase::getName(qint32 id) {
	return idToName[id];
}

qint32 Gw2SpidyAllItemsDataBase::getID(QString name) {
	return nameToID[name];
}

QHash<QString, QString> Gw2SpidyAllItemsDataBase::getData(qint32 id) {
	return idToData[id];
}

QHash<QString, QString> Gw2SpidyAllItemsDataBase::getData(QString name) {
	return idToData[nameToID[name]];
}

QStringList Gw2SpidyAllItemsDataBase::format(QString line) {
	QStringList ret; int namePos, i;
	for(i = 0; line[i] != ','; ++i) {
		if(line[i + 1] == ',') {
			//Stop at the end of the ID string
			ret.append(line.left(i + 1));
		}
	}
	//Name pos is After the first quote mark, 2 after the end of the id
	i += 2;
	namePos = i;
	while(true) {
		if(line[i + 1] == '"' && line[i + 2] == ',') {
			/*Stop at the end of the name string, between the quotation marks.
			  123,"abc"
			  namepos is at the comma, i is at the 'c'
			  Grab everything between the quotes */
			ret.append(line.mid(namePos, i - (namePos - 1))); break;
		}
		++i;
	}
	//Remove the id and name columns from the original string, i+2 to remove the next comma
	i += 2;
	ret.append(line.remove(0, i));
	return ret;
}
