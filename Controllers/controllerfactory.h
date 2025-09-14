#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include "controller.h"
#include "request.h"
#include "tcpserver.h"
#include <QObject>

namespace My {
class CONTROLLERS_EXPORT ControllerFactory : public QObject {
    Q_OBJECT
public:
    explicit ControllerFactory(TcpServer *server, QObject *parent = nullptr);
    Controller *produce(const Request &req);

signals:

public slots:
    void write(QTcpSocket *socket, const My::Request &req);

private:
    TcpServer *server;
};
} // namespace My

#endif // CONTROLLERFACTORY_H
