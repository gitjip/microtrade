QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addtocartdialog.cpp \
    authorizationmanager.cpp \
    cartwidget.cpp \
    config.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    notificationwidget.cpp \
    orderwidget.cpp \
    passwordhasher.cpp \
    profilewidget.cpp \
    registerdialog.cpp \
    shopwidget.cpp \
    tcpaddtocartclient.cpp \
    tcplocalclient.cpp \
    tcploginclient.cpp \
    tcplogoutclient.cpp \
    tcpproductclient.cpp \
    tcpproductlistclient.cpp \
    tcpregisterclient.cpp \
    welcomewidget.cpp

HEADERS += \
    addtocartdialog.h \
    authorizationmanager.h \
    cartwidget.h \
    config.h \
    logindialog.h \
    mainwindow.h \
    notificationwidget.h \
    orderwidget.h \
    passwordhasher.h \
    profilewidget.h \
    registerdialog.h \
    shopwidget.h \
    tcpaddtocartclient.h \
    tcplocalclient.h \
    tcploginclient.h \
    tcplogoutclient.h \
    tcpproductclient.h \
    tcpproductlistclient.h \
    tcpregisterclient.h \
    welcomewidget.h

FORMS += \
    addtocartdialog.ui \
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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../tcpinteraction/release/ -ltcpinteraction
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../tcpinteraction/debug/ -ltcpinteraction
else:unix: LIBS += -L$$OUT_PWD/../tcpinteraction/ -ltcpinteraction

INCLUDEPATH += $$PWD/../tcpinteraction
DEPENDPATH += $$PWD/../tcpinteraction

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../tcpclient/release/ -ltcpclient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../tcpclient/debug/ -ltcpclient
else:unix: LIBS += -L$$OUT_PWD/../tcpclient/ -ltcpclient

INCLUDEPATH += $$PWD/../tcpclient
DEPENDPATH += $$PWD/../tcpclient

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../entity/release/ -lentity
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../entity/debug/ -lentity
else:unix: LIBS += -L$$OUT_PWD/../entity/ -lentity

INCLUDEPATH += $$PWD/../entity
DEPENDPATH += $$PWD/../entity
