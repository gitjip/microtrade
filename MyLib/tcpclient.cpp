#include "tcpclient.h"
#include "constants.h"

namespace My {
TcpClient::TcpClient(QObject *parent) : QTcpSocket{parent} {}

Response TcpClient::get(const QString &route, const QJsonObject &headers,
                        const QJsonValue &body) {
    return send("get", route, headers, body);
}

Response TcpClient::post(const QString &route, const QJsonObject &headers,
                         const QJsonValue &body) {
    return send("post", route, headers, body);
}

Response TcpClient::put(const QString &route, const QJsonObject &headers,
                        const QJsonValue &body) {
    return send("put", route, headers, body);
}

Response TcpClient::del(const QString &route, const QJsonObject &headers,
                        const QJsonValue &body) {
    return send("del", route, headers, body);
}

void TcpClient::setTimeout(int timeout) { this->timeout = timeout; }

Response TcpClient::send(const QString &method, const QString &route,
                         const QJsonObject &headers, const QJsonValue &body) {
    return send(Request(method, route, headers, body));
}

Response TcpClient::send(const Request &request) {
    if (state() != QTcpSocket::ConnectedState) {
        connectToHost(ServerHostAddress, ServerPort);
        if (!waitForConnected(timeout)) {
            qDebug() << "未连接服务器";
            return Response(1, QJsonObject(), QJsonValue(), "connect to host failed");
        }
    }
    write(QJsonDocument(request).toJson(QJsonDocument::Compact));
    if (!waitForReadyRead(timeout)) {
        qDebug() << "请求失败";
        abort();
        return Response(1, QJsonObject(), QJsonValue(), "timeout");
    }
    qDebug() << "获得数据";
    return QJsonDocument::fromJson(readAll()).object();
}
} // namespace My
