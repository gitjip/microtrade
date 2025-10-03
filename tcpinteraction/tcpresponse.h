#ifndef TCPRESPONSE_H
#define TCPRESPONSE_H

#include "tcpinteraction_global.h"
#include "tcpinteraction.h"
#include <QTcpSocket>

class TCPINTERACTION_EXPORT TcpResponse : public TcpInteraction {
public:
    enum class StatusType {
        Success,
        NotFound,
        Failed,
        Unauthorized,
        RuntimeError,
        Timeout,
        InvalidRequest
    };

public:
    TcpResponse();
    TcpResponse(const QDateTime &dateTime,
                const QHostAddress &hostAddress, quint64 port, bool success,
                StatusType statusType, const QString &statusDetail,
                const QJsonObject &body = QJsonObject());
    TcpResponse(const QJsonObject &jsonObj);
    ~TcpResponse() override;
    operator QJsonObject() const override;
    static TcpResponse fromSocket(QTcpSocket *socket);
    static QString statusTypeToString(StatusType statusType);
    static StatusType stringToStatusType(const QString &statusTypeString);

public:
    bool success() const;
    StatusType statusType() const;
    QString statusDetail() const;

private:
    bool m_success = false;
    StatusType m_statusType;
    QString m_statusDetail;
};

#endif // TCPRESPONSE_H
