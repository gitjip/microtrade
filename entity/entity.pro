QT += core

TEMPLATE = lib
DEFINES += ENTITY_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authorization.cpp \
    cart.cpp \
    cartitem.cpp \
    entity.cpp \
    log.cpp \
    notification.cpp \
    order.cpp \
    orderitem.cpp \
    product.cpp \
    productpromotionrelation.cpp \
    promotion.cpp \
    user.cpp

HEADERS += \
    authorization.h \
    cart.h \
    cartitem.h \
    entity_global.h \
    entity.h \
    log.h \
    notification.h \
    order.h \
    orderitem.h \
    product.h \
    productpromotionrelation.h \
    promotion.h \
    user.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
