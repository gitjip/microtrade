QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

VERSION = 1.0.0
QMAKE_TARGET_PRODUCT = "Microtrade"
QMAKE_TARGET_COMPANY = "JLU"
QMAKE_TARGET_DESCRIPTION = "Microtrade" "Client"
QMAKE_TARGET_COPYRIGHT = "Copyright(C)" "2025" "JLU." "All" "rights" "reserved."
# RC_ICONS = .ico

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
    registerdialog.cpp \
    shopwidget.cpp \
    usercenterwidget.cpp \
    welcomewidget.cpp

HEADERS += \
    cartwidget.h \
    logindialog.h \
    mainwindow.h \
    notificationwidget.h \
    orderwidget.h \
    registerdialog.h \
    shopwidget.h \
    usercenterwidget.h \
    welcomewidget.h

FORMS += \
    cartwidget.ui \
    logindialog.ui \
    mainwindow.ui \
    notificationwidget.ui \
    orderwidget.ui \
    registerdialog.ui \
    shopwidget.ui \
    usercenterwidget.ui \
    welcomewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../mylib/release/ -lmylib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../mylib/debug/ -lmylib
else:unix: LIBS += -L$$OUT_PWD/../mylib/ -lmylib

INCLUDEPATH += $$PWD/../mylib
DEPENDPATH += $$PWD/../mylib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../models/release/ -lmodels
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../models/debug/ -lmodels
else:unix: LIBS += -L$$OUT_PWD/../models/ -lmodels

INCLUDEPATH += $$PWD/../models
DEPENDPATH += $$PWD/../models
