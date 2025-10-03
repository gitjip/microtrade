#include "tcplocalresponse.h"
#include "config.h"

TcpLocalResponse::TcpLocalResponse() {}

TcpResponse TcpLocalResponse::make(bool success,
                                   TcpResponse::StatusType statusType,
                                   const QString &statusDetail,
                                   const QJsonObject &body) {
    return TcpResponse(
        success, statusType, statusDetail, QDateTime::currentDateTime(),
        Config::instance()->hostAddress(), Config::instance()->port(), body);
}
