/********************************************************************************
** Form generated from reading UI file 'BatchWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATCHWINDOW_H
#define UI_BATCHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BatchWindow
{
public:
    QTableWidget *watchlistItemsTable;
    QLabel *watchlistItemsLabel;
    QTableWidget *shoppingListTable;
    QLabel *shoppingListLabel;
    QLineEdit *estTotalInvestmentLineEdit;
    QLabel *estTotalInvestmentLabel;
    QLabel *estTotalProfitLabel;
    QLineEdit *estTotalProfitLineEdit;
    QLabel *totalCraftsLabel;
    QLineEdit *totalCraftsLineEdit;
    QPushButton *saveButton;
    QCheckBox *preventOverflowCheckBox;
    QTableWidget *overflowTable;
    QLabel *overflowLabel;

    void setupUi(QWidget *BatchWindow)
    {
        if (BatchWindow->objectName().isEmpty())
            BatchWindow->setObjectName(QStringLiteral("BatchWindow"));
        BatchWindow->resize(1100, 409);
        watchlistItemsTable = new QTableWidget(BatchWindow);
        if (watchlistItemsTable->columnCount() < 5)
            watchlistItemsTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        watchlistItemsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        watchlistItemsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        watchlistItemsTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        watchlistItemsTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        watchlistItemsTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        watchlistItemsTable->setObjectName(QStringLiteral("watchlistItemsTable"));
        watchlistItemsTable->setGeometry(QRect(10, 40, 521, 361));
        watchlistItemsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        watchlistItemsLabel = new QLabel(BatchWindow);
        watchlistItemsLabel->setObjectName(QStringLiteral("watchlistItemsLabel"));
        watchlistItemsLabel->setGeometry(QRect(10, 10, 101, 17));
        shoppingListTable = new QTableWidget(BatchWindow);
        if (shoppingListTable->columnCount() < 3)
            shoppingListTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        shoppingListTable->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        shoppingListTable->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        shoppingListTable->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        shoppingListTable->setObjectName(QStringLiteral("shoppingListTable"));
        shoppingListTable->setGeometry(QRect(540, 40, 321, 301));
        shoppingListTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        shoppingListTable->setDragDropOverwriteMode(true);
        shoppingListTable->setSortingEnabled(true);
        shoppingListTable->setCornerButtonEnabled(true);
        shoppingListTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        shoppingListTable->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        shoppingListLabel = new QLabel(BatchWindow);
        shoppingListLabel->setObjectName(QStringLiteral("shoppingListLabel"));
        shoppingListLabel->setGeometry(QRect(540, 10, 91, 17));
        estTotalInvestmentLineEdit = new QLineEdit(BatchWindow);
        estTotalInvestmentLineEdit->setObjectName(QStringLiteral("estTotalInvestmentLineEdit"));
        estTotalInvestmentLineEdit->setGeometry(QRect(540, 370, 161, 29));
        estTotalInvestmentLabel = new QLabel(BatchWindow);
        estTotalInvestmentLabel->setObjectName(QStringLiteral("estTotalInvestmentLabel"));
        estTotalInvestmentLabel->setGeometry(QRect(540, 350, 171, 17));
        estTotalProfitLabel = new QLabel(BatchWindow);
        estTotalProfitLabel->setObjectName(QStringLiteral("estTotalProfitLabel"));
        estTotalProfitLabel->setGeometry(QRect(710, 350, 131, 17));
        estTotalProfitLineEdit = new QLineEdit(BatchWindow);
        estTotalProfitLineEdit->setObjectName(QStringLiteral("estTotalProfitLineEdit"));
        estTotalProfitLineEdit->setGeometry(QRect(710, 370, 131, 29));
        totalCraftsLabel = new QLabel(BatchWindow);
        totalCraftsLabel->setObjectName(QStringLiteral("totalCraftsLabel"));
        totalCraftsLabel->setGeometry(QRect(850, 350, 71, 17));
        totalCraftsLineEdit = new QLineEdit(BatchWindow);
        totalCraftsLineEdit->setObjectName(QStringLiteral("totalCraftsLineEdit"));
        totalCraftsLineEdit->setGeometry(QRect(850, 370, 71, 29));
        saveButton = new QPushButton(BatchWindow);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setEnabled(false);
        saveButton->setGeometry(QRect(1000, 370, 89, 27));
        preventOverflowCheckBox = new QCheckBox(BatchWindow);
        preventOverflowCheckBox->setObjectName(QStringLiteral("preventOverflowCheckBox"));
        preventOverflowCheckBox->setGeometry(QRect(110, 10, 131, 21));
        preventOverflowCheckBox->setChecked(true);
        overflowTable = new QTableWidget(BatchWindow);
        if (overflowTable->columnCount() < 2)
            overflowTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        overflowTable->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        overflowTable->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        overflowTable->setObjectName(QStringLiteral("overflowTable"));
        overflowTable->setGeometry(QRect(870, 40, 221, 301));
        overflowTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        overflowTable->setSortingEnabled(true);
        overflowLabel = new QLabel(BatchWindow);
        overflowLabel->setObjectName(QStringLiteral("overflowLabel"));
        overflowLabel->setGeometry(QRect(870, 10, 59, 17));

        retranslateUi(BatchWindow);

        QMetaObject::connectSlotsByName(BatchWindow);
    } // setupUi

    void retranslateUi(QWidget *BatchWindow)
    {
        BatchWindow->setWindowTitle(QApplication::translate("BatchWindow", "Form", 0));
        QTableWidgetItem *___qtablewidgetitem = watchlistItemsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("BatchWindow", "Quantity", 0));
        QTableWidgetItem *___qtablewidgetitem1 = watchlistItemsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("BatchWindow", "Item Name", 0));
        QTableWidgetItem *___qtablewidgetitem2 = watchlistItemsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("BatchWindow", "Cost", 0));
        QTableWidgetItem *___qtablewidgetitem3 = watchlistItemsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("BatchWindow", "Profit", 0));
        QTableWidgetItem *___qtablewidgetitem4 = watchlistItemsTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("BatchWindow", "# Crafts", 0));
        watchlistItemsLabel->setText(QApplication::translate("BatchWindow", "Watchlist Items", 0));
        QTableWidgetItem *___qtablewidgetitem5 = shoppingListTable->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("BatchWindow", "Item Name", 0));
        QTableWidgetItem *___qtablewidgetitem6 = shoppingListTable->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("BatchWindow", "Quantity", 0));
        QTableWidgetItem *___qtablewidgetitem7 = shoppingListTable->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QApplication::translate("BatchWindow", "Price", 0));
        shoppingListLabel->setText(QApplication::translate("BatchWindow", "Shopping List", 0));
        estTotalInvestmentLabel->setText(QApplication::translate("BatchWindow", "Estimated Total Investment", 0));
        estTotalProfitLabel->setText(QApplication::translate("BatchWindow", "Estimated Total Profit", 0));
        totalCraftsLabel->setText(QApplication::translate("BatchWindow", "Total Crafts", 0));
        saveButton->setText(QApplication::translate("BatchWindow", "Save", 0));
#ifndef QT_NO_TOOLTIP
        preventOverflowCheckBox->setToolTip(QApplication::translate("BatchWindow", "Adjusts item quantities so there is no leftover materials.", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        preventOverflowCheckBox->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        preventOverflowCheckBox->setText(QApplication::translate("BatchWindow", "Prevent Overflow", 0));
        QTableWidgetItem *___qtablewidgetitem8 = overflowTable->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("BatchWindow", "Item Name", 0));
        QTableWidgetItem *___qtablewidgetitem9 = overflowTable->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QApplication::translate("BatchWindow", "Quantity", 0));
        overflowLabel->setText(QApplication::translate("BatchWindow", "Overflow", 0));
    } // retranslateUi

};

namespace Ui {
    class BatchWindow: public Ui_BatchWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATCHWINDOW_H
