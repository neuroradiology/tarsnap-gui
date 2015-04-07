#-------------------------------------------------
#
# Project created by QtCreator 2014-12-10T01:25:38
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tarsnappy
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    coreapplication.cpp \
    main.cpp \
    debug.cpp \
    utils.cpp \
    widgets/archivelistitem.cpp \
    widgets/backuplistitem.cpp \
    widgets/backuplistwidget.cpp \
    widgets/browselistwidget.cpp \
    widgets/filepicker.cpp \
    widgets/filepickerdialog.cpp \
    widgets/joblistitem.cpp \
    widgets/joblistwidget.cpp \
    widgets/jobwidget.cpp \
    widgets/mainwindow.cpp \
    widgets/restoredialog.cpp \
    widgets/setupdialog.cpp \
    widgets/textlabel.cpp \
    customfilesystemmodel.cpp \
    job.cpp \
    taskmanager.cpp \
    tarsnapclient.cpp \
    persistentstore.cpp

HEADERS  += \
    coreapplication.h \
    debug.h \
    utils.h \
    widgets/archivelistitem.h \
    widgets/backuplistitem.h \
    widgets/backuplistwidget.h \
    widgets/browselistwidget.h \
    widgets/filepicker.h \
    widgets/filepickerdialog.h \
    widgets/joblistitem.h \
    widgets/joblistwidget.h \
    widgets/jobwidget.h \
    widgets/mainwindow.h \
    widgets/restoredialog.h \
    widgets/setupdialog.h \
    widgets/textlabel.h \
    customfilesystemmodel.h \
    job.h \
    taskmanager.h \
    tarsnapclient.h \
    persistentstore.h

INCLUDEPATH += widgets/

FORMS    += \
    forms/backupitemwidget.ui \
    forms/setupdialog.ui \
    forms/mainwindow.ui \
    forms/archiveitemwidget.ui \
    forms/restoredialog.ui \
    forms/filepicker.ui \
    forms/filepickerdialog.ui \
    forms/jobitemwidget.ui \
    forms/jobwidget.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    COPYING \
    README \
    INSTALL \
    CHANGELOG

osx {
    OBJECTIVE_SOURCES += platform_osx.mm
    LIBS += -framework Foundation
    ICON = resources/icons/tarsnap.icns
}
