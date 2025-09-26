#include "tcpclient.h"
#include <QTimer>
#include <QJsonDocument>

TcpClient::TcpClient(QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this))
{}

void TcpClient::sendAsync(const TcpRequest &tcpRequest)
{
    if (!parseSend(tcpRequest)) {
        qDebug() << "TcpClient::sendAsync(const TcpRequest &): failed";
        return;
    }
    connect(socket, &QTcpSocket::readyRead, this, [=](){

    });
}

void TcpClient::sendAsync(const TcpRequest &tcpRequest, qint64 timeout)
{
    if (!parseSend(tcpRequest)) {
        qDebug() << "TcpClient::sendAsync(const TcpRequest &, qint64): failed";
        return;
    }
}

bool TcpClient::parseSend(const TcpRequest &tcpRequest)
{
    if (!socket || socket->isOpen()) {
        qDebug() << "TcpClient::parseSend: socket not open";
        return false;
    }
    if (socket->write(tcpRequest) == -1) {
        qDebug() << "TcpClient::parseSend: socket writing error";
        return false;
    }
    return true;
}
