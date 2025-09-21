#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "mylib_constants.h"
#include "mylib_global.h"
#include "request.h"
#include "response.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QThread>

namespace My {
class MYLIB_EXPORT TcpClient : public QTcpSocket {
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    Response post(const QString &route, const Headers &headers, const Body &body);
    void postAsync(const QString &route, const Headers &headers,
                   const Body &body);
    void setTimeout(int timeout);

private:
    Response send(const QString &method, const QString &route,
                  const Headers &headers, const Body &body);
    Response send(const Request &request);
    void sendAsync(const QString &method, const QString &route,
                   const Headers &headers, const Body &body);
    void sendAsync(const Request &request);

signals:
    void readyRead(const My::Response &response);

private:
    int timeout = 100;
};
} // namespace My

#endif // TCPCLIENT_H
