#include "tcpserverdistributor.h"

TcpServerDistributor::TcpServerDistributor(QObject *parent)
    : QObject{parent}
{}

TcpResponse TcpServerDistributor::distribute(const TcpRequest &tcpRequest)
{
    if (tcpRequest.route() == "/login") {
        return m_threadPool->start(nullptr, tcpRequest);
    } else {
        return m_threadPool->start(nullptr, tcpRequest);
    }
}
