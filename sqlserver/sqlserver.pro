QT -= gui

TEMPLATE = lib
DEFINES += SQLSERVER_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sqlserver.cpp \
    sqlserverdistributor.cpp \
    sqlserverhandler.cpp \
    sqlserverparser.cpp

HEADERS += \
    sqlserver_global.h \
    sqlserver.h \
    sqlserverdistributor.h \
    sqlserverhandler.h \
    sqlserverparser.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
