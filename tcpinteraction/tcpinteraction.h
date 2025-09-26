#ifndef TCPINTERACTION_H
#define TCPINTERACTION_H

#include <QDateTime>
#include <QHostAddress>
#include <QJsonObject>

class TcpInteraction {
public:
    enum Item {         // Qt           QJsonValue

        IsValid,        // bool         Bool
        DateTime,       // QDateTime    String
        HostAddress,    // QHostAddress String
        Port,           // quint64      Integer
        Body,           // QJsonObject  Object
        AuthorizedToken,// QString      String
        Route,          // QString      String
        Timeout,        // qint64       Integer
        Success,        // bool         Bool
        StatusType,     // QString      String
        StatusDetail    // QString      String
    };

public:
    TcpInteraction();
    TcpInteraction(bool isValid, const QDateTime &dateTime,
                   const QHostAddress &hostAddress, quint64 port,
                   const QJsonObject &body);
    virtual ~TcpInteraction();
    virtual operator QJsonObject() const = 0;
    operator QByteArray() const;
    static QString toString(Item data);

public:
    QDateTime dateTime() const;
    QHostAddress hostAddress() const;
    quint64 port() const;
    QJsonObject body() const;

protected:
    bool m_isValid;
    QDateTime m_dateTime;
    QHostAddress m_hostAddress;
    quint64 m_port = 0;
    QJsonObject m_body;

private:
    static QByteArray toFixedBytes(qint64 value);
    static qint64 toValue(QByteArray bytes);
};

#endif // TCPINTERACTION_H
