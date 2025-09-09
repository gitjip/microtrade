QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

VERSION = 1.0.0
QMAKE_TARGET_PRODUCT = "Microtrade_Client_1.0.0"
QMAKE_TARGET_COMPANY = "JLU"
QMAKE_TARGET_DESCRIPTION = "Microtrade_Client"
QMAKE_TARGET_COPYRIGHT = "Copyright(C)_2025_JLU._All_rights_reserved."
# RC_ICONS = .ico

DEFINES += VERSION_STR=\\\"$$VERSION\\\"
DEFINES += PRODUCT=\\\"$$QMAKE_TARGET_PRODUCT\\\"
DEFINES += COMPANY=\\\"$$QMAKE_TARGET_COMPANY\\\"
DEFINES += DESCRIPTION=\\\"$$QMAKE_TARGET_DESCRIPTION\\\"
DEFINES += COPYRIGHT=\\\"$$QMAKE_TARGET_COPYRIGHT\\\"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    registerwindow.cpp

HEADERS += \
    loginwindow.h \
    mainwindow.h \
    registerwindow.h

FORMS += \
    loginwindow.ui \
    mainwindow.ui \
    registerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../MyLib/release/ -lMyLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../MyLib/debug/ -lMyLib
else:unix: LIBS += -L$$OUT_PWD/../MyLib/ -lMyLib

INCLUDEPATH += $$PWD/../MyLib
DEPENDPATH += $$PWD/../MyLib
