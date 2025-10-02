QT       += core gui network concurrent sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    config.cpp \
    logwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    notificationwidget.cpp \
    productwidget.cpp \
    promotionwidget.cpp \
    serverwidget.cpp \
    sqlauthenticator.cpp \
    sqlauthorizer.cpp \
    sqlpayer.cpp \
    sqlproductfinder.cpp \
    sqlproductlistfinder.cpp \
    tcplocaldistributor.cpp \
    tcplocalserver.cpp \
    tcploginhandler.cpp \
    tcppaymenthandler.cpp \
    tcpproducthandler.cpp \
    tcpproductlisthandler.cpp \
    userwidget.cpp \
    welcomewidget.cpp

HEADERS += \
    config.h \
    logwidget.h \
    mainwindow.h \
    notificationwidget.h \
    productwidget.h \
    promotionwidget.h \
    serverwidget.h \
    sqlauthenticator.h \
    sqlauthorizer.h \
    sqlpayer.h \
    sqlproductfinder.h \
    sqlproductlistfinder.h \
    tcplocaldistributor.h \
    tcplocalserver.h \
    tcploginhandler.h \
    tcppaymenthandler.h \
    tcpproducthandler.h \
    tcpproductlisthandler.h \
    userwidget.h \
    welcomewidget.h

FORMS += \
    logwidget.ui \
    mainwindow.ui \
    notificationwidget.ui \
    productwidget.ui \
    promotionwidget.ui \
    serverwidget.ui \
    userwidget.ui \
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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../tcpserver/release/ -ltcpserver
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../tcpserver/debug/ -ltcpserver
else:unix: LIBS += -L$$OUT_PWD/../tcpserver/ -ltcpserver

INCLUDEPATH += $$PWD/../tcpserver
DEPENDPATH += $$PWD/../tcpserver

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../sqlserver/release/ -lsqlserver
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../sqlserver/debug/ -lsqlserver
else:unix: LIBS += -L$$OUT_PWD/../sqlserver/ -lsqlserver

INCLUDEPATH += $$PWD/../sqlserver
DEPENDPATH += $$PWD/../sqlserver

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../entity/release/ -lentity
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../entity/debug/ -lentity
else:unix: LIBS += -L$$OUT_PWD/../entity/ -lentity

INCLUDEPATH += $$PWD/../entity
DEPENDPATH += $$PWD/../entity

DISTFILES +=
