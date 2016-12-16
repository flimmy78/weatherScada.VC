#-------------------------------------------------
#
# Project created by QtCreator 2016-12-03T22:07:48
#
#-------------------------------------------------

QT       += core gui sql serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console debug warn_on

TARGET = weatherScada
TEMPLATE = app

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/protocol.cpp \
    src/func.cpp \
    src/sysconfig.cpp \
    src/db.cpp \
    src/readdata.cpp \
    src/com.cpp \
    src/logic.cpp

HEADERS  += inc/mainwindow.h \
    inc/protocol.h \
    inc/basedef.h \
    inc/func.h \
    inc/sysconfig.h \
    inc/db.h \
    inc/readdata.h \
    inc/com.h \
    inc/logic.h

INCLUDEPATH += 	inc/

FORMS    += ui/mainwindow.ui \
    ui/sysconfig.ui \
    ui/readdata.ui

RESOURCES += weatherScada.qrc
RC_FILE = weatherScada.rc
DESTDIR  = obj/
OBJECTS_DIR = obj/
UI_DIR = inc/
TRANSLATIONS += ./language/weatherScada_en.ts ./language/weatherScada_zh.ts