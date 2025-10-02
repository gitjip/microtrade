#include "tcpserverpaymenthandler.h"

TcpServerPaymentHandler::TcpServerPaymentHandler(QObject *parent)
    : TcpServerHandler{parent}
{}

TcpResponse TcpServerPaymentHandler::handle(const TcpRequest &request){
    return {};
}
