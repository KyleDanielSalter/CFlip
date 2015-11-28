/********************************************************************************
** Form generated from reading UI file 'LoadingSplash.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADINGSPLASH_H
#define UI_LOADINGSPLASH_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QLabel>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadingSplash
{
public:
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *LoadingSplash)
    {
        if (LoadingSplash->objectName().isEmpty())
            LoadingSplash->setObjectName(QString::fromUtf8("LoadingSplash"));
        LoadingSplash->resize(295, 234);
        label = new QLabel(LoadingSplash);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 20, 101, 20));
        label_2 = new QLabel(LoadingSplash);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 110, 91, 20));
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(LoadingSplash);

        QMetaObject::connectSlotsByName(LoadingSplash);
    } // setupUi

    void retranslateUi(QWidget *LoadingSplash)
    {
        LoadingSplash->setWindowTitle(QApplication::translate("LoadingSplash", "Form", 0, 0));
        label->setText(QApplication::translate("LoadingSplash", "CFlip v0.3 Alpha", 0, 0));
        label_2->setText(QApplication::translate("LoadingSplash", "Loading...", 0, 0));
    } // retranslateUi

};

namespace Ui {
    class LoadingSplash: public Ui_LoadingSplash {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADINGSPLASH_H
