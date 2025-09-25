#ifndef TCPRESPONSE_H
#define TCPRESPONSE_H

#include "tcpinteraction.h"
#include <QDateTime>

class TcpResponse : public TcpInteraction
{
public:
    TcpResponse();
    TcpResponse(qint64 contentLength, const QDateTime &dateTime,
                const QHostAddress &hostAddress, quint64 port, bool success,
                const QString &statusType, const QString &statusDetail,
                const QJsonObject &body);
    TcpResponse(const QJsonObject &jsonObj);
    ~TcpResponse() override;
    operator QJsonObject() const override;

private:
    bool m_success = false;
    QString m_statusType;
    QString m_statusDetail;
};

#endif // TCPRESPONSE_H
