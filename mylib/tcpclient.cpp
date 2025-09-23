#include "tcpclient.h"
#include "mylib_constants.h"

namespace My {
TcpClient::TcpClient(QObject *parent) : QTcpSocket{parent} {}

Response TcpClient::post(const QString &route, const Headers &headers,
                         const Body &body) {
    return send("post", route, headers, body);
}

void TcpClient::postAsync(const QString &route, const Headers &headers,
                          const Body &body) {
    sendAsync("post", route, headers, body);
}

void TcpClient::setTimeout(int timeout) { this->timeout = timeout; }

Response TcpClient::send(const QString &method, const QString &route,
                         const Headers &headers, const Body &body) {
    return send(Request(method, route, headers, body));
}

Response TcpClient::send(const Request &request) {
    if (state() != QTcpSocket::ConnectedState) {
        connectToHost(ServerHostAddress, ServerPort);
        if (!waitForConnected(timeout)) {
            qDebug() << "My::TcpClient::send: connect to host failed";
            return Response(1, Headers(), Body(), "connect to host failed");
        }
    }
    write(QJsonDocument(request).toJson(QJsonDocument::Compact));
    if (!waitForReadyRead(timeout)) {
        qDebug() << "My::TcpClient::send: request timeout";
        abort();
        return Response(1, Headers(), Body(), "timeout");
    }
    qDebug() << "My::TcpClient::send: gained data";
    return QJsonDocument::fromJson(readAll()).object();
}

void TcpClient::sendAsync(const QString &method, const QString &route,
                          const Headers &headers, const Body &body) {
    sendAsync(Request(method, route, headers, body));
}

void TcpClient::sendAsync(const Request &request) {
    if (state() != QTcpSocket::ConnectedState) {
        connectToHost(ServerHostAddress, ServerPort);
    }
    connect(this, &QTcpSocket::connected, this, [=]() {
        write(QJsonDocument(request).toJson(QJsonDocument::Compact));
    });
    connect(this, &QTcpSocket::readyRead, this, [=]() {
        emit readyRead(QJsonDocument::fromJson(readAll()).object());
    });
}
} // namespace My
