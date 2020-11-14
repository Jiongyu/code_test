#-------------------------------------------------
#
# Project created by QtCreator 2020-11-12T17:20:49
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtsqlDemo
TEMPLATE = app


SOURCES += main.cpp\
        qtsqldemo.cpp \
    mysql.cpp

HEADERS  += qtsqldemo.h \
    mysql.h \
    header.h

FORMS    += qtsqldemo.ui

# for c++ 11
QMAKE_CXXFLAGS += -std=c++11

