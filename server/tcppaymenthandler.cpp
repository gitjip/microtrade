#include "tcppaymenthandler.h"

TcpPaymentHandler::TcpPaymentHandler(QObject *parent)
    : TcpHandler{parent}
{}

TcpResponse TcpPaymentHandler::handle(const TcpRequest &request){
    return {};
}
