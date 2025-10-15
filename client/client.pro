QT       += core gui network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cartwidget.cpp \
    commander.cpp \
    config.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    notificationwidget.cpp \
    orderwidget.cpp \
    passwordhasher.cpp \
    passwordresetdialog.cpp \
    productdialog.cpp \
    profilewidget.cpp \
    promotionwidget.cpp \
    registerdialog.cpp \
    shopwidget.cpp \
    statisticwidget.cpp \
    tcpaddtocartclient.cpp \
    tcpalterusernameclient.cpp \
    tcpcartproductlistclient.cpp \
    tcpcartsyncclient.cpp \
    tcpcancelorderclient.cpp \
    tcpdeleteorderclient.cpp \
    tcplocalclient.cpp \
    tcploginclient.cpp \
    tcplogoutclient.cpp \
    tcpmonthdailycostclient.cpp \
    tcpmonthlycostclient.cpp \
    tcporderclient.cpp \
    tcppaymentclient.cpp \
    tcpproductclient.cpp \
    tcpproductlistclient.cpp \
    tcpproductpromotionlistclient.cpp \
    tcpproductsearchclient.cpp \
    tcppromotionlistclient.cpp \
    tcpregisterclient.cpp \
    tcpremovefromcartclient.cpp \
    tcpresetpasswordclient.cpp \
    tcpuserclient.cpp \
    usernamealterdialog.cpp \
    welcomewidget.cpp

HEADERS += \
    cartwidget.h \
    commander.h \
    config.h \
    logindialog.h \
    mainwindow.h \
    notificationwidget.h \
    orderwidget.h \
    passwordhasher.h \
    passwordresetdialog.h \
    productdialog.h \
    profilewidget.h \
    promotionwidget.h \
    registerdialog.h \
    shopwidget.h \
    statisticwidget.h \
    tcpaddtocartclient.h \
    tcpalterusernameclient.h \
    tcpcartproductlistclient.h \
    tcpcartsyncclient.h \
    tcpcancelorderclient.h \
    tcpdeleteorderclient.h \
    tcplocalclient.h \
    tcploginclient.h \
    tcplogoutclient.h \
    tcpmonthdailycostclient.h \
    tcpmonthlycostclient.h \
    tcporderclient.h \
    tcppaymentclient.h \
    tcpproductclient.h \
    tcpproductlistclient.h \
    tcpproductpromotionlistclient.h \
    tcpproductsearchclient.h \
    tcppromotionlistclient.h \
    tcpregisterclient.h \
    tcpremovefromcartclient.h \
    tcpresetpasswordclient.h \
    tcpuserclient.h \
    usernamealterdialog.h \
    welcomewidget.h

FORMS += \
    cartwidget.ui \
    logindialog.ui \
    mainwindow.ui \
    notificationwidget.ui \
    orderwidget.ui \
    passwordresetdialog.ui \
    productdialog.ui \
    profilewidget.ui \
    promotionwidget.ui \
    registerdialog.ui \
    shopwidget.ui \
    statisticwidget.ui \
    usernamealterdialog.ui \
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

RESOURCES += \
    resrc.qrc
