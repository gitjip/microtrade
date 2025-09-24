QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cartwidget.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    notificationwidget.cpp \
    orderwidget.cpp \
    profilewidget.cpp \
    registerdialog.cpp \
    shopwidget.cpp \
    welcomewidget.cpp

HEADERS += \
    cartwidget.h \
    logindialog.h \
    mainwindow.h \
    notificationwidget.h \
    orderwidget.h \
    profilewidget.h \
    registerdialog.h \
    shopwidget.h \
    welcomewidget.h

FORMS += \
    cartwidget.ui \
    logindialog.ui \
    mainwindow.ui \
    notificationwidget.ui \
    orderwidget.ui \
    profilewidget.ui \
    registerdialog.ui \
    shopwidget.ui \
    welcomewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
