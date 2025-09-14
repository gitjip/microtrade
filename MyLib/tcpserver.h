#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "mylib_global.h"
#include "request.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpServer>
#include <QTcpSocket>

namespace My {
class MYLIB_EXPORT TcpServer : public QTcpServer {
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);

signals:
    void readyWrite(QTcpSocket *socket, const My::Request &req);

public slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

private:
    QList<QTcpSocket *> socketList;
};
} // namespace My

#endif // TCPSERVER_H
