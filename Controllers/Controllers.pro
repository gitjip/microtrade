QT      += core network sql

TEMPLATE = lib
DEFINES += CONTROLLERS_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller.cpp \
    controllerfactory.cpp \
    controllers.cpp \
    logincontroller.cpp \
    registercontroller.cpp \
    unregistercontroller.cpp \
    usercontroller.cpp

HEADERS += \
    controller.h \
    controllerfactory.h \
    controllers.h \
    controllers_global.h \
    logincontroller.h \
    registercontroller.h \
    unregistercontroller.h \
    usercontroller.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../mylib/release/ -lmylib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../mylib/debug/ -lmylib
else:unix: LIBS += -L$$OUT_PWD/../mylib/ -lmylib

INCLUDEPATH += $$PWD/../mylib
DEPENDPATH += $$PWD/../mylib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../models/release/ -lmodels
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../models/debug/ -lmodels
else:unix: LIBS += -L$$OUT_PWD/../models/ -lmodels

INCLUDEPATH += $$PWD/../models
DEPENDPATH += $$PWD/../models
