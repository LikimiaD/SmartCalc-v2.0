QT += core gui
QT += charts
QT += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

LIBS += -L$$PWD/.. -lmodel
LIBS += -L$$PWD/.. -lcontroller

INCLUDEPATH += $$PWD/../model
INCLUDEPATH += $$PWD/../controller

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../main.cpp \
    creditui.cpp \
    depositui.cpp \
    graphwidget.cpp \
    mainwindow.cpp
    graphwidget.cpp

HEADERS += \
    creditui.h \
    depositui.h \
    graphwidget.h \
    mainwindow.h
    graphwidget.h

FORMS += \
    creditui.ui \
    depositui.ui \
    graphwidget.ui \
    mainwindow.ui

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target