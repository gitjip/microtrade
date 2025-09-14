#ifndef TCPCLIENT_H
#define TCPCLIENT_H

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
    Response get(const QString &route, const QJsonObject &headers,
                  const QJsonValue &body);
    Response post(const QString &route, const QJsonObject &headers,
                  const QJsonValue &body);
    Response put(const QString &route, const QJsonObject &headers,
                  const QJsonValue &body);
    Response del(const QString &route, const QJsonObject &headers,
                  const QJsonValue &body);
    void setTimeout(int timeout);

private:
    Response send(const QString &method, const QString &route,
                  const QJsonObject &headers, const QJsonValue &body);
    Response send(const Request &request);

signals:

private:
    int timeout = 100;
};
} // namespace My

#endif // TCPCLIENT_H
