QT += core
QT -= gui

CONFIG += c++11

TARGET = openpcap
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    run.cpp \
    read.cpp

INCLUDEPATH += "tmp/libpcap/include"

LIBS += -L"/tmp/libpcap/lib" -lpcap

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    data.h \
    head.h \
    twse01.h \
    trans.h \
    twse21.h \
    twse22.h \
    twse06.h \
    twse23.h \
    tpex01.h \
    tpex06.h \
    tpex21.h \
    tpex22.h \
    tpex23.h
