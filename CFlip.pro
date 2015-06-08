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
    Gw2ItemDB.cpp \
    Gw2API.cpp \
    Gw2ItemIDListParser.cpp \
    Gw2ItemsParser.cpp \
    ImageDownloader.cpp \
    Gw2ListingsParser.cpp \
    Gw2Currency.cpp \
    Gw2RecipesParser.cpp

HEADERS  += CFlipMainWindow.h \
    Gw2ItemDB.h \
    Gw2API.h \
    Gw2ItemIDListParser.h \
    Gw2ItemsParser.h \
    ImageDownloader.h \
    Gw2ListingsParser.h \
    Gw2Currency.h \
    Gw2RecipesParser.h

FORMS    += CFlipMainWindow.ui
