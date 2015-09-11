/********************************************************************************
** Form generated from reading UI file 'LoadingSplash.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADINGSPLASH_H
#define UI_LOADINGSPLASH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadingSplash
{
public:
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *LoadingSplash)
    {
        if (LoadingSplash->objectName().isEmpty())
            LoadingSplash->setObjectName(QStringLiteral("LoadingSplash"));
        LoadingSplash->resize(295, 234);
        label = new QLabel(LoadingSplash);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 20, 101, 20));
        label_2 = new QLabel(LoadingSplash);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(100, 110, 91, 20));
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(LoadingSplash);

        QMetaObject::connectSlotsByName(LoadingSplash);
    } // setupUi

    void retranslateUi(QWidget *LoadingSplash)
    {
        LoadingSplash->setWindowTitle(QApplication::translate("LoadingSplash", "Form", 0));
        label->setText(QApplication::translate("LoadingSplash", "CFlip v0.1 Alpha", 0));
        label_2->setText(QApplication::translate("LoadingSplash", "Loading...", 0));
    } // retranslateUi

};

namespace Ui {
    class LoadingSplash: public Ui_LoadingSplash {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADINGSPLASH_H
