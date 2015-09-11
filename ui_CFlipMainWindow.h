/********************************************************************************
** Form generated from reading UI file 'CFlipMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CFLIPMAINWINDOW_H
#define UI_CFLIPMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

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
            CFlipMainWindow->setObjectName(QStringLiteral("CFlipMainWindow"));
        CFlipMainWindow->resize(872, 521);
        actionNew_Watchlist = new QAction(CFlipMainWindow);
        actionNew_Watchlist->setObjectName(QStringLiteral("actionNew_Watchlist"));
        centralWidget = new QWidget(CFlipMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        watchListTab = new QTabWidget(centralWidget);
        watchListTab->setObjectName(QStringLiteral("watchListTab"));
        watchListTab->setEnabled(true);
        watchListTab->setGeometry(QRect(0, 10, 861, 501));
        watchListTab->setStyleSheet(QLatin1String("QTabWidget::pane { /* The tab widget frame */\n"
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
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 872, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        CFlipMainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(CFlipMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CFlipMainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew_Watchlist);

        retranslateUi(CFlipMainWindow);

        watchListTab->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(CFlipMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CFlipMainWindow)
    {
        CFlipMainWindow->setWindowTitle(QApplication::translate("CFlipMainWindow", "CFlipMainWindow", 0));
#ifndef QT_NO_STATUSTIP
        CFlipMainWindow->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        actionNew_Watchlist->setText(QApplication::translate("CFlipMainWindow", "New Watchlist...", 0));
        menuFile->setTitle(QApplication::translate("CFlipMainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class CFlipMainWindow: public Ui_CFlipMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CFLIPMAINWINDOW_H
