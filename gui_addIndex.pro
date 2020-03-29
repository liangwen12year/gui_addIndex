#-------------------------------------------------
#
# Project created by QtCreator 2020-02-22T11:43:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui_addIndex
TEMPLATE = app
CONFIG += static
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_LFLAGS = -static -static-libgcc
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Decryption/main.cpp \
        Decryption/widget.cpp
#        main.cpp \
#        mainwindow.cpp

HEADERS += \
        Decryption/debug/moc_predefs.h \
        Decryption/ui_widget.h \
        Decryption/widget.h
#        mainwindow.h

FORMS += \
        Decryption/widget.ui
#        mainwindow.ui
DESTDIR = $${PWD}/bin
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    Decryption/Decryption.pro
