TEMPLATE = subdirs

SUBDIRS += \
    client \
    entity \
    server \
    sqlserver \
    tcpclient \
    tcpinteraction \
    tcpserver

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/tcpinteraction/release/ -ltcpinteraction
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/tcpinteraction/debug/ -ltcpinteraction
else:unix: LIBS += -L$$OUT_PWD/tcpinteraction/ -ltcpinteraction

INCLUDEPATH += $$PWD/tcpinteraction
DEPENDPATH += $$PWD/tcpinteraction
