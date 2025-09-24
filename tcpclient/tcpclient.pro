QT -= gui

TEMPLATE = lib
DEFINES += TCPCLIENT_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    tcpclient.cpp \
    tcpsender.cpp \
    tcpsenderfactory.cpp

HEADERS += \
    tcpclient_global.h \
    tcpclient.h \
    tcpsender.h \
    tcpsenderfactory.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
