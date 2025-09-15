QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controlwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    welcomewidget.cpp

HEADERS += \
    controlwidget.h \
    mainwindow.h \
    welcomewidget.h

FORMS += \
    controlwidget.ui \
    mainwindow.ui \
    welcomewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../controllers/release/ -lcontrollers
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../controllers/debug/ -lcontrollers
else:unix: LIBS += -L$$OUT_PWD/../controllers/ -lcontrollers

INCLUDEPATH += $$PWD/../controllers
DEPENDPATH += $$PWD/../controllers

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../mylib/release/ -lmylib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../mylib/debug/ -lmylib
else:unix: LIBS += -L$$OUT_PWD/../mylib/ -lmylib

INCLUDEPATH += $$PWD/../mylib
DEPENDPATH += $$PWD/../mylib
