#-------------------------------------------------
#
# Project created by QtCreator 2018-04-12T23:57:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Turing
TEMPLATE = app
CONFIG += c++14

INCLUDEPATH += /usr/local/include/
LIBS += -L/usr/local/include/boost/ -lboost_system -lboost_regex
LIBS += -L/usr/local/lib/ -lboost_system -lboost_regex

SOURCES += main.cpp\
        mainwindow.cpp \
    TM.cpp \
    Lang.cpp

HEADERS  += mainwindow.h \
    Lang.hpp \
    TM.hpp \
    settings.hpp

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
