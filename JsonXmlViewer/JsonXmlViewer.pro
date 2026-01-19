QT       += core gui xml

CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JsonXmlViewer
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += c++11

SOURCES += \
        jsontreebuilder.cpp \
        main.cpp \
        mainwindow.cpp \
        searchproxymodel.cpp \
        thememanager.cpp \
        treebuilder.cpp \
        xmltreebuilder.cpp

HEADERS += \
        jsontreebuilder.h \
        mainwindow.h \
        searchproxymodel.h \
        thememanager.h \
        treebuilder.h \
        xmltreebuilder.h

FORMS += \
        mainwindow.ui


win32 {
        RC_FILE += file.rc
        OTHER_FILES += file.rc
}
