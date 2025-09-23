#include "controllerfactory.h"
#include "logincontroller.h"
#include "registercontroller.h"
#include "shopcontroller.h"
#include "unregistercontroller.h"
#include "usercontroller.h"

namespace My {
ControllerFactory::ControllerFactory(TcpServer *server, QObject *parent)
    : QObject(parent), server(server) {
    connect(server, &TcpServer::readyWrite, this, &ControllerFactory::write);
}

Controller *ControllerFactory::produce(const Request &req) {
    if (req.route == "/login") {
        return new LoginController(this);
    } else if (req.route == "/register") {
        return new RegisterController(this);
    } else if (req.route == "/unregister") {
        return new UnregisterController(this);
    } else if (req.route == "/user") {
        return new UserController(this);
    } else if (req.route == "/shop") {
        return new ShopController(this);
    }
    return nullptr;
}

void ControllerFactory::write(QTcpSocket *socket, const Request &req) {
    Controller *controller = produce(req);
    if (controller != nullptr) {
        qDebug() << "controller returns data";
        Response res = controller->send(req.method, req.headers, req.body);
        socket->write(QJsonDocument(res).toJson(QJsonDocument::Compact));
        delete controller;
    } else {
        Response res(1, QJsonObject(), QJsonValue(), "invalid route");
        socket->write(QJsonDocument(res).toJson(QJsonDocument::Compact));
    }
}
} // namespace My
