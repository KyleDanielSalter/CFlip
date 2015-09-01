#-------------------------------------------------
#
# Project created by QtCreator 2015-05-23T18:39:58
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CFlip
TEMPLATE = app


SOURCES += main.cpp\
        CFlipMainWindow.cpp \
    Gw2ItemDB.cpp \
    Gw2API.cpp \
    Gw2ItemsParser.cpp \
    ImageDownloader.cpp \
    Gw2ListingsParser.cpp \
    Gw2Currency.cpp \
    Gw2RecipesParser.cpp \
    CraftingItem.cpp \
    Gw2APIParser.cpp \
    Gw2APIMultiCaller.cpp \
    Gw2APIResult.cpp \
    MultiListingCaller.cpp \
    RecipeTree.cpp \
    Gw2RecipesDB.cpp \
    CraftingTree.cpp \
    Gw2ListingsManager.cpp \
    WatchListTabWidget.cpp \
    WatchListManager.cpp

HEADERS  += CFlipMainWindow.h \
    Gw2ItemDB.h \
    Gw2API.h \
    Gw2ItemsParser.h \
    ImageDownloader.h \
    Gw2ListingsParser.h \
    Gw2Currency.h \
    Gw2RecipesParser.h \
    CraftingItem.h \
    Gw2APIParser.h \
    Gw2APIMultiCaller.h \
    Gw2APIResult.h \
    MultiListingCaller.h \
    RecipeTree.h \
    Gw2RecipesDB.h \
    CraftingTree.h \
    Gw2ListingsManager.h \
    WatchListTabWidget.h \
    WatchListManager.h

FORMS    += CFlipMainWindow.ui \
    WatchListTabWidget.ui
