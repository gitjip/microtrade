#include "tcpclient.h"

namespace My {
TcpClient::TcpClient(QObject *parent) : QTcpSocket{parent} {}

Response TcpClient::post(const QString &route, const QJsonObject &headers,
                         const QJsonValue &body) {
    return send("post", route, headers, body);
}

void TcpClient::setTimeout(int timeout) { this->timeout = timeout; }

Response TcpClient::send(const QString &method, const QString &route,
                         const QJsonObject &headers, const QJsonValue &body) {
    return send(Request(method, route, headers, body));
}

Response TcpClient::send(const Request &request) {
    write(QJsonDocument(request).toJson(QJsonDocument::Compact));
    if (waitForReadyRead(timeout)) {
        return QJsonDocument::fromJson(readAll()).object();
    } else {
        return Response(-1, QJsonObject(), QJsonValue(), "timeout");
    }
}
} // namespace My
