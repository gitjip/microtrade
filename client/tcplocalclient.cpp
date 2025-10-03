#include "tcplocalclient.h"
#include "config.h"

TcpLocalClient::TcpLocalClient(QObject *parent) : TcpClient{parent} {
    connectToHost(QHostAddress(Config::instance()->hostAddress()),
                  Config::instance()->port());
}

void TcpLocalClient::sendAsync(const QString &route, const QJsonObject &body) {
    TcpRequest request{route,
                       Config::instance()->timeout(),
                       QDateTime::currentDateTime(),
                       Config::instance()->hostAddress(),
                       Config::instance()->port(),
                       body};
    TcpClient::sendAsync(request, Config::instance()->timeout());
}
