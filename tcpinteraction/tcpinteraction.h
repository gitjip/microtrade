#ifndef TCPINTERACTION_H
#define TCPINTERACTION_H

#include "tcpinteraction_global.h"
#include <QDateTime>
#include <QHostAddress>
#include <QJsonObject>

class TCPINTERACTION_EXPORT TcpInteraction
{
public:
    enum Item {             // Qt           QJsonValue
        ContentLength,      // qint64       Integer
        DateTime,           // QDateTime    String
        HostAddress,        // QHostAddress String
        Port,               // quint64      String
        Body,               // QJsonObject  Object
        AuthorizedToken,    // QString      String
        Route,              // QString      String
        Timeout,            // qint64       Integer
        Success,            // bool         Bool
        StatusType,         // QString      String
        StatusDetail        // QString      String
    };

public:
    TcpInteraction();
    TcpInteraction(qint64 contentLength, const QDateTime &dateTime,
                   const QHostAddress &hostAddress, quint64 port,
                   const QJsonObject &body);
    virtual ~TcpInteraction();
    virtual operator QJsonObject() const = 0;
    static QString toString(Item data);

protected:
    qint64 m_contentLength = 0;
    QDateTime m_dateTime;
    QHostAddress m_hostAddress;
    quint64 m_port = 0;
    QJsonObject m_body;
};

#endif // TCPINTERACTION_H
