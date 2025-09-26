#ifndef TCPRESPONSE_H
#define TCPRESPONSE_H

#include "tcpinteraction_global.h"
#include "tcpinteraction.h"
#include <QDateTime>

class TCPINTERACTION_EXPORT TcpResponse : public TcpInteraction {
public:
    TcpResponse();
    TcpResponse(bool isValid, const QDateTime &dateTime,
                const QHostAddress &hostAddress, quint64 port, bool success,
                const QString &statusType, const QString &statusDetail,
                const QJsonObject &body);
    TcpResponse(const QJsonObject &jsonObj);
    ~TcpResponse() override;
    operator QJsonObject() const override;

public:
    bool success() const;
    QString statusType() const;
    QString statusDetail() const;

private:
    bool m_success = false;
    QString m_statusType;
    QString m_statusDetail;
};

#endif // TCPRESPONSE_H
