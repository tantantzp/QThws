#-------------------------------------------------
#
# Project created by QtCreator 2012-08-24T15:13:44
#
#-------------------------------------------------

QT       += core gui

TARGET = project1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    SPPackingStrategy.cpp \
    SPPackingCommand.cpp \
    Rect.cpp \
    PackingCommand.cpp \
    mainwindow.cpp \
    main.cpp \
    Layout.cpp \
    GraphPacking.cpp \
    dialog.cpp \
    dialog_2.cpp

HEADERS  += mainwindow.h \
    SPPackingStrategy.h \
    SPPackingCommand.h \
    PackingStrategy.h \
    PackingCommand.h \
    Layout.h \
    GraphPacking.h \
    Point.h \
    Rect.h \
    dialog.h \
    dialog_2.h

FORMS    += mainwindow.ui \
    dialog.ui \
    dialog_2.ui

RESOURCES += \
    Icon.qrc
