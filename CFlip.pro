#-------------------------------------------------
#
# Project created by QtCreator 2015-05-23T18:39:58
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CFlip
TEMPLATE = app


SOURCES += main.cpp\
        CFlipMainWindow.cpp \
    Gw2SpidyAllItemsDataBase.cpp

HEADERS  += CFlipMainWindow.h \
    Gw2SpidyAllItemsDataBase.h

FORMS    += CFlipMainWindow.ui
