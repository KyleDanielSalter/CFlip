#include "AddItemDialog.h"
#include "ui_AddItemDialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include "Gw2ItemDB.h"

AddItemDialog::AddItemDialog(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::AddItemDialog)
	, allItemNames(Gw2ItemDB::getNameIDHashMap().keys())
{
	ui->setupUi(this);
	ui->searchResultsListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

AddItemDialog::~AddItemDialog() {
	allItemNames.clear();
	results.clear();
	delete ui;
}

QList<qint32> AddItemDialog::start(bool &ok) {
	ok = false;
	okPtr = &ok;
	exec();
	QList<qint32> ret = getReturn();
	return ret;
}

AddItemDialog::SearchParameters::SearchParameters()
	: levelRange(QPair<qint32, qint32>(-1, -1))
{}

AddItemDialog::SearchParameters::SearchParameters(
	QString str,
	QHash<QString, QStringList> types,
	QPair<qint32, qint32> levelRange,
	QStringList rarities)
	: str(str)
	, types(types)
	, levelRange(levelRange)
	, rarities(rarities)
{}

void AddItemDialog::search() {
	updateSearchParameters();
	results.clear();
	for(auto i : allItemNames) {
		if(check(i))
			results << i;
	}
	updateSearchResults();
}

bool AddItemDialog::check(QString comp) {
	QJsonDocument jsonDoc = QJsonDocument::fromJson(Gw2ItemDB::getJsonDataString(comp).toUtf8());
	QJsonObject jsonObj = jsonDoc.object();
	if(!checkSearchString(comp))
		return false;
	else if(!checkTypes(jsonObj))
		return false;
	else if(!checkLevelRange(jsonObj))
		return false;
	else if(!checkRarity(jsonObj))
		return false;
	return true;
}

bool AddItemDialog::checkSearchString(QString comp) {
	return params.str.isEmpty() ? true : comp.contains(params.str, Qt::CaseInsensitive);
}

bool AddItemDialog::checkTypes(QJsonObject &jsonObj) {
	QStringList types = params.types.keys();
	//If no types are selected, all types are valid.
	if(!types.isEmpty() && jsonObj.contains("type")) {
		QString itemType = jsonObj.value("type").toString();
		if(types.contains(itemType)) {
			QStringList detailTypes = params.types.value(itemType);
			//If no detailTypes are selected, all detail types are valid
			if(!detailTypes.isEmpty() && jsonObj.contains("details")) {
				QJsonObject detailsJsonObj = jsonObj.value("details").toObject();
				if(detailsJsonObj.contains("type")) {
					QString detailsType = detailsJsonObj.value("type").toString();
					return detailTypes.contains(detailsType);
				}
			} else if(detailTypes.isEmpty())
				return true;
		} else
			return false;
	}
	return true;
}

bool AddItemDialog::checkLevelRange(QJsonObject &jsonObj) {
	if(params.levelRange.first != -1 && params.levelRange.second != -1) {
		if(jsonObj.contains("level")) {
		   qint32 level = jsonObj.value("level").toInt();
		   if(level > params.levelRange.first &&  level < params.levelRange.second)
			   return true;
		   else
			   return false;
		}
	}
	return true;
}

bool AddItemDialog::checkRarity(QJsonObject &jsonObj) {
	if(!params.rarities.isEmpty()) {
		if(jsonObj.contains("rarity")) {
			QString rarity = jsonObj.value("rarity").toString();
			return params.rarities.contains(rarity);
		}
	}
	return true;
}

void AddItemDialog::updateSearchParameters() {
	params.str = ui->searchQueryLineEdit->text();
	params.types = getTypes();
	params.levelRange = getLevelRange();
	params.rarities = getRarities();
}

QHash<QString, QStringList> AddItemDialog::getTypes() {
	QHash<QString, QStringList> types;
	QTreeWidget* typeTree = ui->itemTypeTreeWidget;
	for(qint32 i = 0; i < typeTree->topLevelItemCount(); ++i) {
		QTreeWidgetItem* top = typeTree->topLevelItem(i);
		QString type = top->text(0);
		QStringList detailTypes;
		if(top->childCount() > 0) {
			for(qint32 j = 0; j < top->childCount(); ++j) {
				QTreeWidgetItem *treeChild = top->child(j);
				if(treeChild->childCount() == 0 && treeChild->isSelected())
					detailTypes << treeChild->text(0);
				else if(treeChild->childCount() > 0){
					for(qint32 k = 0; k < treeChild->childCount(); ++k) {
						QTreeWidgetItem *innerType = treeChild->child(k);
						if(innerType->isSelected())
							detailTypes << innerType->text(0);
					}
				}
			}
		}
		if(!detailTypes.isEmpty())
			types.insert(type, detailTypes);
		else if(top->isSelected())
			types.insert(type, detailTypes);
	}
	return types;
}

QPair<qint32, qint32> AddItemDialog::getLevelRange() {
	if(ui->levelGroupBox->isChecked()) {
		qint32 min = ui->minLevelSpinBox->value(),
			max = ui->maxLevelSpinBox->value();
		return QPair<qint32, qint32>(min, max);
	}
	return QPair<qint32, qint32>(-1, -1);
}

QStringList AddItemDialog::getRarities() {
	QStringList ret;
	if(ui->rarityGroupBox->isChecked()) {
		QList<QListWidgetItem*> selectedItems = ui->rarityListWidget->selectedItems();
		for(auto i : selectedItems)
			ret << i->text();
	}
	return ret;
}

void AddItemDialog::updateSearchResults() {
	ui->searchResultsListWidget->clear();
	ui->searchResultsListWidget->addItems(results);
}

QList<qint32> AddItemDialog::getReturn() {
	QList<qint32> ret;
	if(ui->onlyUseSelectedCheckBox->isChecked()) {
		QList<QListWidgetItem*> selectedResults = ui->searchResultsListWidget->selectedItems();
		if(selectedResults.isEmpty())  {
			for(auto i : results)
				ret << Gw2ItemDB::getItemID(i);
		} else {
			for(auto i : selectedResults)
				ret << Gw2ItemDB::getItemID(i->text());
		}
	} else {
		for(auto i : results)
			ret << Gw2ItemDB::getItemID(i);
	}
	return ret;
}

void AddItemDialog::on_searchQueryLineEdit_textEdited(const QString &arg1)
{
	search();
}

void AddItemDialog::on_rarityListWidget_itemSelectionChanged()
{
	search();
}

void AddItemDialog::on_levelGroupBox_toggled(bool arg1)
{
	search();
}

void AddItemDialog::on_minLevelSpinBox_valueChanged(int arg1)
{
	search();
}

void AddItemDialog::on_maxLevelSpinBox_valueChanged(int arg1)
{
	search();
}

void AddItemDialog::on_itemTypeTreeWidget_itemSelectionChanged()
{
	search();
}



void AddItemDialog::on_cancelButton_clicked()
{
	*okPtr = false;
	done(0);
}

void AddItemDialog::on_okButton_clicked()
{
	QList<qint32> ret = getReturn();
	if(!ret.isEmpty()) {
		if(ret.size() > 10) {
			qint32 ret = QMessageBox::warning(this, "Too Many Items", "Loading many items will take a long time. Are you sure?", QMessageBox::No, QMessageBox::Yes);
			if(ret == QMessageBox::Yes) {
				*okPtr = true;
				done(0);
			}
		}
	} else {
		*okPtr = false;
		done(0);
	}
}
