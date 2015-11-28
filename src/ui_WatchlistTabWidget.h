/********************************************************************************
** Form generated from reading UI file 'WatchlistTabWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WATCHLISTTABWIDGET_H
#define UI_WATCHLISTTABWIDGET_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QPushButton>
#include <QTableWidget>
#include <QTreeWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_WatchlistTabWidget
{
public:
    QTableWidget *watchlistTable;
    QPushButton *addNewItemButton;
    QPushButton *startBatchButton;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *WatchlistTabWidget)
    {
        if (WatchlistTabWidget->objectName().isEmpty())
            WatchlistTabWidget->setObjectName(QString::fromUtf8("WatchlistTabWidget"));
        WatchlistTabWidget->resize(878, 443);
        watchlistTable = new QTableWidget(WatchlistTabWidget);
        if (watchlistTable->columnCount() < 4)
            watchlistTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        watchlistTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        watchlistTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        watchlistTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        watchlistTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        watchlistTable->setObjectName(QString::fromUtf8("watchlistTable"));
        watchlistTable->setGeometry(QRect(10, 10, 421, 391));
        watchlistTable->setContextMenuPolicy(Qt::CustomContextMenu);
        watchlistTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        watchlistTable->setDragDropOverwriteMode(false);
        watchlistTable->setAlternatingRowColors(true);
        watchlistTable->verticalHeader()->setMinimumSectionSize(20);
        addNewItemButton = new QPushButton(WatchlistTabWidget);
        addNewItemButton->setObjectName(QString::fromUtf8("addNewItemButton"));
        addNewItemButton->setGeometry(QRect(10, 410, 89, 27));
        startBatchButton = new QPushButton(WatchlistTabWidget);
        startBatchButton->setObjectName(QString::fromUtf8("startBatchButton"));
        startBatchButton->setGeometry(QRect(110, 410, 89, 27));
        treeWidget = new QTreeWidget(WatchlistTabWidget);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(440, 10, 421, 391));

        retranslateUi(WatchlistTabWidget);

        QMetaObject::connectSlotsByName(WatchlistTabWidget);
    } // setupUi

    void retranslateUi(QWidget *WatchlistTabWidget)
    {
        WatchlistTabWidget->setWindowTitle(QApplication::translate("WatchlistTabWidget", "Form", 0, 0));
        QTableWidgetItem *___qtablewidgetitem = watchlistTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("WatchlistTabWidget", "Item Name", 0, 0));
        QTableWidgetItem *___qtablewidgetitem1 = watchlistTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("WatchlistTabWidget", "Craft Cost", 0, 0));
        QTableWidgetItem *___qtablewidgetitem2 = watchlistTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("WatchlistTabWidget", "B/S Spread", 0, 0));
        QTableWidgetItem *___qtablewidgetitem3 = watchlistTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("WatchlistTabWidget", "Craft Profit", 0, 0));
        addNewItemButton->setText(QApplication::translate("WatchlistTabWidget", "Add", 0, 0));
        startBatchButton->setText(QApplication::translate("WatchlistTabWidget", "Start Batch", 0, 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("WatchlistTabWidget", "Cost", 0, 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("WatchlistTabWidget", "Type", 0, 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("WatchlistTabWidget", "Item Name", 0, 0));
    } // retranslateUi

};

namespace Ui {
    class WatchlistTabWidget: public Ui_WatchlistTabWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WATCHLISTTABWIDGET_H
