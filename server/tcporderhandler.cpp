#include "tcporderhandler.h"

TcpOrderHandler::TcpOrderHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpOrderHandler::handle(const TcpRequest &request) {}
