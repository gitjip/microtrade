QT = core network sql

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        config.cpp \
        costcalculator.cpp \
        costcalculatorwithpromotion.cpp \
        logmanager.cpp \
        main.cpp \
        sqlauthenticator.cpp \
        sqlauthorizer.cpp \
        sqlcartcreator.cpp \
        sqlcartfinder.cpp \
        sqlcartitemcreator.cpp \
        sqlcartitemlistfinder.cpp \
        sqlcartitemremover.cpp \
        sqlcartsyncer.cpp \
        sqllocalserver.cpp \
        sqlloginchecker.cpp \
        sqllogwriter.cpp \
        sqlordercreator.cpp \
        sqlorderitemcreator.cpp \
        sqlorderitemlistcreator.cpp \
        sqlorderitemlistfinder.cpp \
        sqlorderlistfinder.cpp \
        sqlpasswordupdater.cpp \
        sqlproductfinder.cpp \
        sqlproductlistfinder.cpp \
        sqlproductreducer.cpp \
        sqlproductsearcher.cpp \
        sqlpromotionfinder.cpp \
        sqlpromotionidlistfinder.cpp \
        sqlpromotionlistfinder.cpp \
        sqlunauthorizer.cpp \
        sqlusercreator.cpp \
        sqluserfinder.cpp \
        sqlusernameupdater.cpp \
        tcpaddtocarthandler.cpp \
        tcpalterusernamehandler.cpp \
        tcpcartproductlisthandler.cpp \
        tcpcartsynchandler.cpp \
        tcplocaldistributor.cpp \
        tcplocalresponse.cpp \
        tcplocalserver.cpp \
        tcploginhandler.cpp \
        tcplogouthandler.cpp \
        tcporderhandler.cpp \
        tcppaymenthandler.cpp \
        tcpproducthandler.cpp \
        tcpproductlisthandler.cpp \
        tcpproductpromotionlisthandler.cpp \
        tcpproductsearchhandler.cpp \
        tcppromotionlisthandler.cpp \
        tcpregisterhandler.cpp \
        tcpremovefromcarthandler.cpp \
        tcpresetpasswordhandler.cpp \
        tcpuserhandler.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    config.h \
    costcalculator.h \
    costcalculatorwithpromotion.h \
    logmanager.h \
    sqlauthenticator.h \
    sqlauthorizer.h \
    sqlcartcreator.h \
    sqlcartfinder.h \
    sqlcartitemcreator.h \
    sqlcartitemlistfinder.h \
    sqlcartitemremover.h \
    sqlcartsyncer.h \
    sqllocalserver.h \
    sqlloginchecker.h \
    sqllogwriter.h \
    sqlordercreator.h \
    sqlorderitemcreator.h \
    sqlorderitemlistcreator.h \
    sqlorderitemlistfinder.h \
    sqlorderlistfinder.h \
    sqlpasswordupdater.h \
    sqlproductfinder.h \
    sqlproductlistfinder.h \
    sqlproductreducer.h \
    sqlproductsearcher.h \
    sqlpromotionfinder.h \
    sqlpromotionidlistfinder.h \
    sqlpromotionlistfinder.h \
    sqlunauthorizer.h \
    sqlusercreator.h \
    sqluserfinder.h \
    sqlusernameupdater.h \
    tcpaddtocarthandler.h \
    tcpalterusernamehandler.h \
    tcpcartproductlisthandler.h \
    tcpcartsynchandler.h \
    tcplocaldistributor.h \
    tcplocalresponse.h \
    tcplocalserver.h \
    tcploginhandler.h \
    tcplogouthandler.h \
    tcporderhandler.h \
    tcppaymenthandler.h \
    tcpproducthandler.h \
    tcpproductlisthandler.h \
    tcpproductpromotionlisthandler.h \
    tcpproductsearchhandler.h \
    tcppromotionlisthandler.h \
    tcpregisterhandler.h \
    tcpremovefromcarthandler.h \
    tcpresetpasswordhandler.h \
    tcpuserhandler.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../entity/release/ -lentity
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../entity/debug/ -lentity
else:unix: LIBS += -L$$OUT_PWD/../entity/ -lentity

INCLUDEPATH += $$PWD/../entity
DEPENDPATH += $$PWD/../entity

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../sqlserver/release/ -lsqlserver
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../sqlserver/debug/ -lsqlserver
else:unix: LIBS += -L$$OUT_PWD/../sqlserver/ -lsqlserver

INCLUDEPATH += $$PWD/../sqlserver
DEPENDPATH += $$PWD/../sqlserver

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
