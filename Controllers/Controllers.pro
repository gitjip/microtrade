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
    usercontroller.cpp

HEADERS += \
    Controllers_global.h \
    controller.h \
    controllerfactory.h \
    controllers.h \
    usercontroller.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../MyLib/release/ -lMyLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../MyLib/debug/ -lMyLib
else:unix: LIBS += -L$$OUT_PWD/../MyLib/ -lMyLib

INCLUDEPATH += $$PWD/../MyLib
DEPENDPATH += $$PWD/../MyLib
