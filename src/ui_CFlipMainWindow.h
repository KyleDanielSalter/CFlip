/********************************************************************************
** Form generated from reading UI file 'CFlipMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CFLIPMAINWINDOW_H
#define UI_CFLIPMAINWINDOW_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTabWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_CFlipMainWindow
{
public:
    QAction *actionNew_Watchlist;
    QWidget *centralWidget;
    QTabWidget *watchListTab;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CFlipMainWindow)
    {
        if (CFlipMainWindow->objectName().isEmpty())
            CFlipMainWindow->setObjectName(QString::fromUtf8("CFlipMainWindow"));
        CFlipMainWindow->resize(872, 521);
        CFlipMainWindow->setMinimumSize(QSize(872, 521));
        CFlipMainWindow->setMaximumSize(QSize(872, 521));
        actionNew_Watchlist = new QAction(CFlipMainWindow);
        actionNew_Watchlist->setObjectName(QString::fromUtf8("actionNew_Watchlist"));
        centralWidget = new QWidget(CFlipMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        watchListTab = new QTabWidget(centralWidget);
        watchListTab->setObjectName(QString::fromUtf8("watchListTab"));
        watchListTab->setEnabled(true);
        watchListTab->setGeometry(QRect(0, 10, 861, 501));
        watchListTab->setStyleSheet(QString::fromUtf8("QTabWidget::pane { /* The tab widget frame */\n"
"    border-top: 1px  solid #C2C7CB;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"    left: 5px; /* move to the right by 5px */\n"
"}\n"
"\n"
"/* Style the tab using the tab sub-control. Note that\n"
"    it reads QTabBar _not_ QTabWidget */\n"
"QTabBar::tab {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"                                stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n"
"    border: 1px solid #C4C4C3;\n"
"    border-bottom-color: #C2C7CB; /* same as the pane color */\n"
"    border-top-left-radius: 4px;\n"
"    border-top-right-radius: 4px;\n"
"    min-width: 8ex;\n"
"    padding: 2px;\n"
"}\n"
"\n"
"QTabBar::tab:selected, QTabBar::tab:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #fafafa, stop: 0.4 #f4f4f4,\n"
"                                stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);\n"
"}\n"
"\n"
""
                        "QTabBar::tab:selected {\n"
"    border-color: #9B9B9B;\n"
"    border-bottom-color: #C2C7CB; /* same as pane color */\n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"    margin-top: 2px; /* make non-selected tabs look smaller */\n"
"}"));
        watchListTab->setTabsClosable(true);
        watchListTab->setMovable(true);
        watchListTab->setTabBarAutoHide(false);
        CFlipMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CFlipMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 872, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        CFlipMainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(CFlipMainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CFlipMainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew_Watchlist);

        retranslateUi(CFlipMainWindow);

        watchListTab->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(CFlipMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CFlipMainWindow)
    {
        CFlipMainWindow->setWindowTitle(QApplication::translate("CFlipMainWindow", "CFlipMainWindow", 0, 0));
#ifndef QT_NO_STATUSTIP
        CFlipMainWindow->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        actionNew_Watchlist->setText(QApplication::translate("CFlipMainWindow", "New Watchlist...", 0, 0));
        menuFile->setTitle(QApplication::translate("CFlipMainWindow", "File", 0, 0));
    } // retranslateUi

};

namespace Ui {
    class CFlipMainWindow: public Ui_CFlipMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CFLIPMAINWINDOW_H
