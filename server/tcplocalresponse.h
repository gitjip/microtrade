#ifndef TCPLOCALRESPONSE_H
#define TCPLOCALRESPONSE_H

#include "tcpresponse.h"

class TcpLocalResponse : public TcpResponse {
public:
    TcpLocalResponse();
    static TcpResponse make(bool success, TcpResponse::StatusType statusType,
                            const QString &statusDetail,
                            const QJsonObject &body = {});
};

#endif // TCPLOCALRESPONSE_H
