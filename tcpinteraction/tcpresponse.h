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
    ~TcpResponse() override;
    static TcpResponse fromJson(const QJsonObject &json);
    static TcpResponse fromSocket(QTcpSocket *socket);
    QJsonObject toJson() const override;
    static QString statusTypeToString(StatusType statusType);
    static StatusType stringToStatusType(const QString &statusTypeString);

public:
    bool success() const;
    StatusType statusType() const;
    QString statusDetail() const;

private:
    void initFromJson(const QJsonObject &json) override;
    void initFromSocket(QTcpSocket *socket) override;

private:
    bool m_success = false;
    StatusType m_statusType;
    QString m_statusDetail;
};

#endif // TCPRESPONSE_H
