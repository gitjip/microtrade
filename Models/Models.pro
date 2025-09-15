QT += core

TEMPLATE = lib
DEFINES += MODELS_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cart.cpp \
    cartitem.cpp \
    goods.cpp \
    models.cpp \
    order.cpp \
    orderitem.cpp \
    user.cpp

HEADERS += \
    cart.h \
    cartitem.h \
    goods.h \
    models.h \
    models_global.h \
    order.h \
    orderitem.h \
    user.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
