#include "controllerfactory.h"
#include "usercontroller.h"

namespace My {
ControllerFactory::ControllerFactory(TcpServer *server, QObject *parent)
    : QObject(parent), server(server) {
    connect(server, &TcpServer::readyWrite, this, &ControllerFactory::write);
}

Controller *ControllerFactory::produce(const Request &req) {
    if (req.route == "/api/user") {
        return new UserController(this);
    } else {
        return nullptr;
    }
}

void ControllerFactory::write(QTcpSocket *socket, const Request &req) {
    Controller *controller = produce(req);
    if (controller != nullptr) {
        qDebug() << "控制器返回信息";
        Response res = controller->send(req.method, req.headers, req.body);
        socket->write(QJsonDocument(res).toJson(QJsonDocument::Compact));
        delete controller;
    } else {
        Response res(1, QJsonObject(), QJsonValue(), "invalid route");
        socket->write(QJsonDocument(res).toJson(QJsonDocument::Compact));
    }
}
} // namespace My
