#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T14:57:25
#
#-------------------------------------------------

QT       += core gui quickwidgets location qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Exifator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qmetadata.cpp \
    qexifimageheader.cpp \
    gpsinformationwidget.cpp

HEADERS  += mainwindow.h \
    qmetadata.h \
    qexifimageheader.h \
    gpsinformationwidget.h

FORMS    += mainwindow.ui \
    gpsinformationwidget.ui

DISTFILES += \
    MapView.qml

RESOURCES += \
    qmlfiles.qrc
