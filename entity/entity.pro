QT -= gui

TEMPLATE = lib
DEFINES += ENTITY_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ecart.cpp \
    ecartitem.cpp \
    enotification.cpp \
    entity.cpp \
    eorder.cpp \
    eorderitem.cpp \
    eproduct.cpp \
    euser.cpp

HEADERS += \
    ecart.h \
    ecartitem.h \
    enotification.h \
    entity_global.h \
    entity.h \
    eorder.h \
    eorderitem.h \
    eproduct.h \
    euser.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
