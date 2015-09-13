/********************************************************************************
** Form generated from reading UI file 'AddItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDITEMDIALOG_H
#define UI_ADDITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_AddItemDialog
{
public:
    QGroupBox *rarityGroupBox;
    QListWidget *rarityListWidget;
    QLineEdit *searchQueryLineEdit;
    QGroupBox *searchResultsGroupBox;
    QListWidget *searchResultsListWidget;
    QTreeWidget *itemTypeTreeWidget;
    QGroupBox *levelGroupBox;
    QSpinBox *minLevelSpinBox;
    QLabel *toLevelLabel;
    QSpinBox *maxLevelSpinBox;
    QLabel *searchQueryLabel;
    QCheckBox *onlyUseSelectedCheckBox;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *AddItemDialog)
    {
        if (AddItemDialog->objectName().isEmpty())
            AddItemDialog->setObjectName(QStringLiteral("AddItemDialog"));
        AddItemDialog->resize(572, 340);
        AddItemDialog->setMinimumSize(QSize(522, 308));
        rarityGroupBox = new QGroupBox(AddItemDialog);
        rarityGroupBox->setObjectName(QStringLiteral("rarityGroupBox"));
        rarityGroupBox->setGeometry(QRect(10, 10, 120, 191));
        rarityGroupBox->setCheckable(true);
        rarityGroupBox->setChecked(false);
        rarityListWidget = new QListWidget(rarityGroupBox);
        new QListWidgetItem(rarityListWidget);
        new QListWidgetItem(rarityListWidget);
        new QListWidgetItem(rarityListWidget);
        new QListWidgetItem(rarityListWidget);
        new QListWidgetItem(rarityListWidget);
        new QListWidgetItem(rarityListWidget);
        new QListWidgetItem(rarityListWidget);
        new QListWidgetItem(rarityListWidget);
        rarityListWidget->setObjectName(QStringLiteral("rarityListWidget"));
        rarityListWidget->setGeometry(QRect(0, 20, 111, 161));
        rarityListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        rarityListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        searchQueryLineEdit = new QLineEdit(AddItemDialog);
        searchQueryLineEdit->setObjectName(QStringLiteral("searchQueryLineEdit"));
        searchQueryLineEdit->setGeometry(QRect(100, 290, 201, 29));
        searchResultsGroupBox = new QGroupBox(AddItemDialog);
        searchResultsGroupBox->setObjectName(QStringLiteral("searchResultsGroupBox"));
        searchResultsGroupBox->setGeometry(QRect(340, 10, 231, 261));
        searchResultsListWidget = new QListWidget(searchResultsGroupBox);
        searchResultsListWidget->setObjectName(QStringLiteral("searchResultsListWidget"));
        searchResultsListWidget->setGeometry(QRect(0, 20, 221, 231));
        searchResultsListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        itemTypeTreeWidget = new QTreeWidget(AddItemDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(itemTypeTreeWidget);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(itemTypeTreeWidget);
        new QTreeWidgetItem(itemTypeTreeWidget);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(itemTypeTreeWidget);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(itemTypeTreeWidget);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(itemTypeTreeWidget);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(itemTypeTreeWidget);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(itemTypeTreeWidget);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(itemTypeTreeWidget);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(itemTypeTreeWidget);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(itemTypeTreeWidget);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(itemTypeTreeWidget);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(itemTypeTreeWidget);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem(itemTypeTreeWidget);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        QTreeWidgetItem *__qtreewidgetitem8 = new QTreeWidgetItem(itemTypeTreeWidget);
        QTreeWidgetItem *__qtreewidgetitem9 = new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem9);
        new QTreeWidgetItem(__qtreewidgetitem9);
        new QTreeWidgetItem(__qtreewidgetitem9);
        new QTreeWidgetItem(__qtreewidgetitem9);
        new QTreeWidgetItem(__qtreewidgetitem9);
        new QTreeWidgetItem(__qtreewidgetitem9);
        QTreeWidgetItem *__qtreewidgetitem10 = new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem10);
        new QTreeWidgetItem(__qtreewidgetitem10);
        new QTreeWidgetItem(__qtreewidgetitem10);
        new QTreeWidgetItem(__qtreewidgetitem10);
        QTreeWidgetItem *__qtreewidgetitem11 = new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem11);
        new QTreeWidgetItem(__qtreewidgetitem11);
        QTreeWidgetItem *__qtreewidgetitem12 = new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem12);
        new QTreeWidgetItem(__qtreewidgetitem12);
        new QTreeWidgetItem(__qtreewidgetitem12);
        QTreeWidgetItem *__qtreewidgetitem13 = new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem13);
        new QTreeWidgetItem(__qtreewidgetitem13);
        new QTreeWidgetItem(__qtreewidgetitem13);
        new QTreeWidgetItem(__qtreewidgetitem13);
        itemTypeTreeWidget->setObjectName(QStringLiteral("itemTypeTreeWidget"));
        itemTypeTreeWidget->setGeometry(QRect(130, 10, 201, 251));
        itemTypeTreeWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        itemTypeTreeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        itemTypeTreeWidget->setAlternatingRowColors(false);
        itemTypeTreeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        itemTypeTreeWidget->setIndentation(17);
        itemTypeTreeWidget->setRootIsDecorated(true);
        levelGroupBox = new QGroupBox(AddItemDialog);
        levelGroupBox->setObjectName(QStringLiteral("levelGroupBox"));
        levelGroupBox->setGeometry(QRect(10, 200, 121, 81));
        levelGroupBox->setCheckable(true);
        levelGroupBox->setChecked(false);
        minLevelSpinBox = new QSpinBox(levelGroupBox);
        minLevelSpinBox->setObjectName(QStringLiteral("minLevelSpinBox"));
        minLevelSpinBox->setGeometry(QRect(0, 30, 44, 27));
        minLevelSpinBox->setMinimum(1);
        minLevelSpinBox->setMaximum(80);
        toLevelLabel = new QLabel(levelGroupBox);
        toLevelLabel->setObjectName(QStringLiteral("toLevelLabel"));
        toLevelLabel->setGeometry(QRect(50, 30, 21, 31));
        maxLevelSpinBox = new QSpinBox(levelGroupBox);
        maxLevelSpinBox->setObjectName(QStringLiteral("maxLevelSpinBox"));
        maxLevelSpinBox->setGeometry(QRect(70, 30, 44, 27));
        maxLevelSpinBox->setMinimum(1);
        maxLevelSpinBox->setMaximum(80);
        maxLevelSpinBox->setValue(80);
        searchQueryLabel = new QLabel(AddItemDialog);
        searchQueryLabel->setObjectName(QStringLiteral("searchQueryLabel"));
        searchQueryLabel->setGeometry(QRect(10, 290, 91, 31));
        onlyUseSelectedCheckBox = new QCheckBox(AddItemDialog);
        onlyUseSelectedCheckBox->setObjectName(QStringLiteral("onlyUseSelectedCheckBox"));
        onlyUseSelectedCheckBox->setGeometry(QRect(370, 270, 141, 31));
        okButton = new QPushButton(AddItemDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(470, 300, 89, 27));
        cancelButton = new QPushButton(AddItemDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(370, 300, 89, 27));

        retranslateUi(AddItemDialog);

        QMetaObject::connectSlotsByName(AddItemDialog);
    } // setupUi

    void retranslateUi(QDialog *AddItemDialog)
    {
        AddItemDialog->setWindowTitle(QApplication::translate("AddItemDialog", "Item Search", 0));
        rarityGroupBox->setTitle(QApplication::translate("AddItemDialog", "Rarity", 0));

        const bool __sortingEnabled = rarityListWidget->isSortingEnabled();
        rarityListWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = rarityListWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("AddItemDialog", "Junk", 0));
        QListWidgetItem *___qlistwidgetitem1 = rarityListWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("AddItemDialog", "Basic", 0));
        QListWidgetItem *___qlistwidgetitem2 = rarityListWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("AddItemDialog", "Fine", 0));
        QListWidgetItem *___qlistwidgetitem3 = rarityListWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("AddItemDialog", "Masterwork", 0));
        QListWidgetItem *___qlistwidgetitem4 = rarityListWidget->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("AddItemDialog", "Rare", 0));
        QListWidgetItem *___qlistwidgetitem5 = rarityListWidget->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("AddItemDialog", "Exotic", 0));
        QListWidgetItem *___qlistwidgetitem6 = rarityListWidget->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("AddItemDialog", "Ascended", 0));
        QListWidgetItem *___qlistwidgetitem7 = rarityListWidget->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("AddItemDialog", "Legendary", 0));
        rarityListWidget->setSortingEnabled(__sortingEnabled);

        searchQueryLineEdit->setText(QString());
        searchResultsGroupBox->setTitle(QApplication::translate("AddItemDialog", "Search Results", 0));
        QTreeWidgetItem *___qtreewidgetitem = itemTypeTreeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("AddItemDialog", "Type", 0));

        const bool __sortingEnabled1 = itemTypeTreeWidget->isSortingEnabled();
        itemTypeTreeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = itemTypeTreeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("AddItemDialog", "Armor", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("AddItemDialog", "Boots", 0));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("AddItemDialog", "Coat", 0));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem4->setText(0, QApplication::translate("AddItemDialog", "Gloves", 0));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem1->child(3);
        ___qtreewidgetitem5->setText(0, QApplication::translate("AddItemDialog", "Helm", 0));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem1->child(4);
        ___qtreewidgetitem6->setText(0, QApplication::translate("AddItemDialog", "HelmAquatic", 0));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem1->child(5);
        ___qtreewidgetitem7->setText(0, QApplication::translate("AddItemDialog", "Leggings", 0));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem1->child(6);
        ___qtreewidgetitem8->setText(0, QApplication::translate("AddItemDialog", "Shoulders", 0));
        QTreeWidgetItem *___qtreewidgetitem9 = itemTypeTreeWidget->topLevelItem(1);
        ___qtreewidgetitem9->setText(0, QApplication::translate("AddItemDialog", "Back", 0));
        QTreeWidgetItem *___qtreewidgetitem10 = itemTypeTreeWidget->topLevelItem(2);
        ___qtreewidgetitem10->setText(0, QApplication::translate("AddItemDialog", "Bag", 0));
        QTreeWidgetItem *___qtreewidgetitem11 = itemTypeTreeWidget->topLevelItem(3);
        ___qtreewidgetitem11->setText(0, QApplication::translate("AddItemDialog", "Consumable", 0));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem11->child(0);
        ___qtreewidgetitem12->setText(0, QApplication::translate("AddItemDialog", "AppearanceChange", 0));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem11->child(1);
        ___qtreewidgetitem13->setText(0, QApplication::translate("AddItemDialog", "Booze", 0));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem11->child(2);
        ___qtreewidgetitem14->setText(0, QApplication::translate("AddItemDialog", "ContractNpc", 0));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem11->child(3);
        ___qtreewidgetitem15->setText(0, QApplication::translate("AddItemDialog", "Food", 0));
        QTreeWidgetItem *___qtreewidgetitem16 = ___qtreewidgetitem11->child(4);
        ___qtreewidgetitem16->setText(0, QApplication::translate("AddItemDialog", "Generic", 0));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem11->child(5);
        ___qtreewidgetitem17->setText(0, QApplication::translate("AddItemDialog", "Halloween", 0));
        QTreeWidgetItem *___qtreewidgetitem18 = ___qtreewidgetitem11->child(6);
        ___qtreewidgetitem18->setText(0, QApplication::translate("AddItemDialog", "Immediate", 0));
        QTreeWidgetItem *___qtreewidgetitem19 = ___qtreewidgetitem11->child(7);
        ___qtreewidgetitem19->setText(0, QApplication::translate("AddItemDialog", "Transmutation", 0));
        QTreeWidgetItem *___qtreewidgetitem20 = ___qtreewidgetitem11->child(8);
        ___qtreewidgetitem20->setText(0, QApplication::translate("AddItemDialog", "Unlock", 0));
        QTreeWidgetItem *___qtreewidgetitem21 = ___qtreewidgetitem11->child(9);
        ___qtreewidgetitem21->setText(0, QApplication::translate("AddItemDialog", "UpgradeRemoval", 0));
        QTreeWidgetItem *___qtreewidgetitem22 = ___qtreewidgetitem11->child(10);
        ___qtreewidgetitem22->setText(0, QApplication::translate("AddItemDialog", "Utility", 0));
        QTreeWidgetItem *___qtreewidgetitem23 = itemTypeTreeWidget->topLevelItem(4);
        ___qtreewidgetitem23->setText(0, QApplication::translate("AddItemDialog", "Container", 0));
        QTreeWidgetItem *___qtreewidgetitem24 = ___qtreewidgetitem23->child(0);
        ___qtreewidgetitem24->setText(0, QApplication::translate("AddItemDialog", "Default", 0));
        QTreeWidgetItem *___qtreewidgetitem25 = ___qtreewidgetitem23->child(1);
        ___qtreewidgetitem25->setText(0, QApplication::translate("AddItemDialog", "GiftBox", 0));
        QTreeWidgetItem *___qtreewidgetitem26 = ___qtreewidgetitem23->child(2);
        ___qtreewidgetitem26->setText(0, QApplication::translate("AddItemDialog", "OpenUI", 0));
        QTreeWidgetItem *___qtreewidgetitem27 = itemTypeTreeWidget->topLevelItem(5);
        ___qtreewidgetitem27->setText(0, QApplication::translate("AddItemDialog", "CraftingMaterial", 0));
        QTreeWidgetItem *___qtreewidgetitem28 = itemTypeTreeWidget->topLevelItem(6);
        ___qtreewidgetitem28->setText(0, QApplication::translate("AddItemDialog", "Gathering", 0));
        QTreeWidgetItem *___qtreewidgetitem29 = ___qtreewidgetitem28->child(0);
        ___qtreewidgetitem29->setText(0, QApplication::translate("AddItemDialog", "Foraging", 0));
        QTreeWidgetItem *___qtreewidgetitem30 = ___qtreewidgetitem28->child(1);
        ___qtreewidgetitem30->setText(0, QApplication::translate("AddItemDialog", "Logging", 0));
        QTreeWidgetItem *___qtreewidgetitem31 = ___qtreewidgetitem28->child(2);
        ___qtreewidgetitem31->setText(0, QApplication::translate("AddItemDialog", "Mining", 0));
        QTreeWidgetItem *___qtreewidgetitem32 = itemTypeTreeWidget->topLevelItem(7);
        ___qtreewidgetitem32->setText(0, QApplication::translate("AddItemDialog", "Gizmo", 0));
        QTreeWidgetItem *___qtreewidgetitem33 = ___qtreewidgetitem32->child(0);
        ___qtreewidgetitem33->setText(0, QApplication::translate("AddItemDialog", "Default", 0));
        QTreeWidgetItem *___qtreewidgetitem34 = ___qtreewidgetitem32->child(1);
        ___qtreewidgetitem34->setText(0, QApplication::translate("AddItemDialog", "ContainerKey", 0));
        QTreeWidgetItem *___qtreewidgetitem35 = ___qtreewidgetitem32->child(2);
        ___qtreewidgetitem35->setText(0, QApplication::translate("AddItemDialog", "ContainerKey", 0));
        QTreeWidgetItem *___qtreewidgetitem36 = ___qtreewidgetitem32->child(3);
        ___qtreewidgetitem36->setText(0, QApplication::translate("AddItemDialog", "UnlimitedConsumable", 0));
        QTreeWidgetItem *___qtreewidgetitem37 = itemTypeTreeWidget->topLevelItem(8);
        ___qtreewidgetitem37->setText(0, QApplication::translate("AddItemDialog", "MiniPet", 0));
        QTreeWidgetItem *___qtreewidgetitem38 = itemTypeTreeWidget->topLevelItem(9);
        ___qtreewidgetitem38->setText(0, QApplication::translate("AddItemDialog", "Tool", 0));
        QTreeWidgetItem *___qtreewidgetitem39 = ___qtreewidgetitem38->child(0);
        ___qtreewidgetitem39->setText(0, QApplication::translate("AddItemDialog", "Salvage", 0));
        QTreeWidgetItem *___qtreewidgetitem40 = itemTypeTreeWidget->topLevelItem(10);
        ___qtreewidgetitem40->setText(0, QApplication::translate("AddItemDialog", "Trait", 0));
        QTreeWidgetItem *___qtreewidgetitem41 = itemTypeTreeWidget->topLevelItem(11);
        ___qtreewidgetitem41->setText(0, QApplication::translate("AddItemDialog", "Trinket", 0));
        QTreeWidgetItem *___qtreewidgetitem42 = ___qtreewidgetitem41->child(0);
        ___qtreewidgetitem42->setText(0, QApplication::translate("AddItemDialog", "Accessory", 0));
        QTreeWidgetItem *___qtreewidgetitem43 = ___qtreewidgetitem41->child(1);
        ___qtreewidgetitem43->setText(0, QApplication::translate("AddItemDialog", "Amulet", 0));
        QTreeWidgetItem *___qtreewidgetitem44 = ___qtreewidgetitem41->child(2);
        ___qtreewidgetitem44->setText(0, QApplication::translate("AddItemDialog", "Ring", 0));
        QTreeWidgetItem *___qtreewidgetitem45 = itemTypeTreeWidget->topLevelItem(12);
        ___qtreewidgetitem45->setText(0, QApplication::translate("AddItemDialog", "Trophy", 0));
        QTreeWidgetItem *___qtreewidgetitem46 = itemTypeTreeWidget->topLevelItem(13);
        ___qtreewidgetitem46->setText(0, QApplication::translate("AddItemDialog", "UpgradeComponent", 0));
        QTreeWidgetItem *___qtreewidgetitem47 = ___qtreewidgetitem46->child(0);
        ___qtreewidgetitem47->setText(0, QApplication::translate("AddItemDialog", "Default", 0));
        QTreeWidgetItem *___qtreewidgetitem48 = ___qtreewidgetitem46->child(1);
        ___qtreewidgetitem48->setText(0, QApplication::translate("AddItemDialog", "Gem", 0));
        QTreeWidgetItem *___qtreewidgetitem49 = ___qtreewidgetitem46->child(2);
        ___qtreewidgetitem49->setText(0, QApplication::translate("AddItemDialog", "Gem", 0));
        QTreeWidgetItem *___qtreewidgetitem50 = ___qtreewidgetitem46->child(3);
        ___qtreewidgetitem50->setText(0, QApplication::translate("AddItemDialog", "Sigil", 0));
        QTreeWidgetItem *___qtreewidgetitem51 = itemTypeTreeWidget->topLevelItem(14);
        ___qtreewidgetitem51->setText(0, QApplication::translate("AddItemDialog", "Weapon", 0));
        QTreeWidgetItem *___qtreewidgetitem52 = ___qtreewidgetitem51->child(0);
        ___qtreewidgetitem52->setText(0, QApplication::translate("AddItemDialog", "One-handed main hand", 0));
        QTreeWidgetItem *___qtreewidgetitem53 = ___qtreewidgetitem52->child(0);
        ___qtreewidgetitem53->setText(0, QApplication::translate("AddItemDialog", "Axe", 0));
        QTreeWidgetItem *___qtreewidgetitem54 = ___qtreewidgetitem52->child(1);
        ___qtreewidgetitem54->setText(0, QApplication::translate("AddItemDialog", "Dagger", 0));
        QTreeWidgetItem *___qtreewidgetitem55 = ___qtreewidgetitem52->child(2);
        ___qtreewidgetitem55->setText(0, QApplication::translate("AddItemDialog", "Mace", 0));
        QTreeWidgetItem *___qtreewidgetitem56 = ___qtreewidgetitem52->child(3);
        ___qtreewidgetitem56->setText(0, QApplication::translate("AddItemDialog", "Pistol", 0));
        QTreeWidgetItem *___qtreewidgetitem57 = ___qtreewidgetitem52->child(4);
        ___qtreewidgetitem57->setText(0, QApplication::translate("AddItemDialog", "Scepter", 0));
        QTreeWidgetItem *___qtreewidgetitem58 = ___qtreewidgetitem52->child(5);
        ___qtreewidgetitem58->setText(0, QApplication::translate("AddItemDialog", "Sword", 0));
        QTreeWidgetItem *___qtreewidgetitem59 = ___qtreewidgetitem51->child(1);
        ___qtreewidgetitem59->setText(0, QApplication::translate("AddItemDialog", "One-handed off hand", 0));
        QTreeWidgetItem *___qtreewidgetitem60 = ___qtreewidgetitem59->child(0);
        ___qtreewidgetitem60->setText(0, QApplication::translate("AddItemDialog", "Focus", 0));
        QTreeWidgetItem *___qtreewidgetitem61 = ___qtreewidgetitem59->child(1);
        ___qtreewidgetitem61->setText(0, QApplication::translate("AddItemDialog", "Shield", 0));
        QTreeWidgetItem *___qtreewidgetitem62 = ___qtreewidgetitem59->child(2);
        ___qtreewidgetitem62->setText(0, QApplication::translate("AddItemDialog", "Torch", 0));
        QTreeWidgetItem *___qtreewidgetitem63 = ___qtreewidgetitem59->child(3);
        ___qtreewidgetitem63->setText(0, QApplication::translate("AddItemDialog", "Warhorn", 0));
        QTreeWidgetItem *___qtreewidgetitem64 = ___qtreewidgetitem51->child(2);
        ___qtreewidgetitem64->setText(0, QApplication::translate("AddItemDialog", "Two-handed", 0));
        QTreeWidgetItem *___qtreewidgetitem65 = ___qtreewidgetitem64->child(0);
        ___qtreewidgetitem65->setText(0, QApplication::translate("AddItemDialog", "Greatsword", 0));
        QTreeWidgetItem *___qtreewidgetitem66 = ___qtreewidgetitem64->child(1);
        ___qtreewidgetitem66->setText(0, QApplication::translate("AddItemDialog", "Hammer", 0));
        QTreeWidgetItem *___qtreewidgetitem67 = ___qtreewidgetitem64->child(2);
        ___qtreewidgetitem67->setText(0, QApplication::translate("AddItemDialog", "LongBow", 0));
        QTreeWidgetItem *___qtreewidgetitem68 = ___qtreewidgetitem64->child(3);
        ___qtreewidgetitem68->setText(0, QApplication::translate("AddItemDialog", "Rifle", 0));
        QTreeWidgetItem *___qtreewidgetitem69 = ___qtreewidgetitem64->child(4);
        ___qtreewidgetitem69->setText(0, QApplication::translate("AddItemDialog", "ShortBow", 0));
        QTreeWidgetItem *___qtreewidgetitem70 = ___qtreewidgetitem64->child(5);
        ___qtreewidgetitem70->setText(0, QApplication::translate("AddItemDialog", "Staff", 0));
        QTreeWidgetItem *___qtreewidgetitem71 = ___qtreewidgetitem51->child(3);
        ___qtreewidgetitem71->setText(0, QApplication::translate("AddItemDialog", "Aquatic", 0));
        QTreeWidgetItem *___qtreewidgetitem72 = ___qtreewidgetitem71->child(0);
        ___qtreewidgetitem72->setText(0, QApplication::translate("AddItemDialog", "Harpoon", 0));
        QTreeWidgetItem *___qtreewidgetitem73 = ___qtreewidgetitem71->child(1);
        ___qtreewidgetitem73->setText(0, QApplication::translate("AddItemDialog", "Speargun", 0));
        QTreeWidgetItem *___qtreewidgetitem74 = ___qtreewidgetitem71->child(2);
        ___qtreewidgetitem74->setText(0, QApplication::translate("AddItemDialog", "Trident", 0));
        QTreeWidgetItem *___qtreewidgetitem75 = ___qtreewidgetitem51->child(4);
        ___qtreewidgetitem75->setText(0, QApplication::translate("AddItemDialog", "Other", 0));
        QTreeWidgetItem *___qtreewidgetitem76 = ___qtreewidgetitem75->child(0);
        ___qtreewidgetitem76->setText(0, QApplication::translate("AddItemDialog", "LargeBundle", 0));
        QTreeWidgetItem *___qtreewidgetitem77 = ___qtreewidgetitem75->child(1);
        ___qtreewidgetitem77->setText(0, QApplication::translate("AddItemDialog", "SmallBundle", 0));
        QTreeWidgetItem *___qtreewidgetitem78 = ___qtreewidgetitem75->child(2);
        ___qtreewidgetitem78->setText(0, QApplication::translate("AddItemDialog", "Toy", 0));
        QTreeWidgetItem *___qtreewidgetitem79 = ___qtreewidgetitem75->child(3);
        ___qtreewidgetitem79->setText(0, QApplication::translate("AddItemDialog", "TwoHandedToy", 0));
        itemTypeTreeWidget->setSortingEnabled(__sortingEnabled1);

        levelGroupBox->setTitle(QApplication::translate("AddItemDialog", "Level", 0));
        toLevelLabel->setText(QApplication::translate("AddItemDialog", "to", 0));
        searchQueryLabel->setText(QApplication::translate("AddItemDialog", "Search Query:", 0));
        onlyUseSelectedCheckBox->setText(QApplication::translate("AddItemDialog", "Only Use Selected", 0));
        okButton->setText(QApplication::translate("AddItemDialog", "OK", 0));
        cancelButton->setText(QApplication::translate("AddItemDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class AddItemDialog: public Ui_AddItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDITEMDIALOG_H
