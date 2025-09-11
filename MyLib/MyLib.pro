QT += core network sql

TEMPLATE = lib
DEFINES += MYLIB_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    mylib.cpp \
    request.cpp \
    response.cpp \
    responser.cpp \
    sqlquery.cpp \
    tcpclient.cpp \
    tcpserver.cpp

HEADERS += \
    MyLib_global.h \
    constants.h \
    mylib.h \
    request.h \
    response.h \
    responser.h \
    sqlquery.h \
    tcpclient.h \
    tcpserver.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
