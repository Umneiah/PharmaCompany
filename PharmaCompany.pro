#-------------------------------------------------
#
# Project created by QtCreator 2016-12-16T15:18:22
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PharmaCompany
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    employee.cpp \
    client.cpp \
    product.cpp \
    department.cpp

HEADERS  += mainwindow.h \
    employee.h \
    client.h \
    product.h \
    department.h

FORMS    += mainwindow.ui \
    employee.ui \
    client.ui \
    product.ui \
    department.ui

INCLUDEPATH += $$PWD/../../../Users/mosta/Desktop
DEPENDPATH += $$PWD/../../../Users/mosta/Desktop

INCLUDEPATH += $$PWD/../../../Users/mosta/Desktop
DEPENDPATH += $$PWD/../../../Users/mosta/Desktop
