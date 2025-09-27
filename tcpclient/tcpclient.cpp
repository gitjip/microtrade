#include "tcpclient.h"
#include <QTimer>
#include <QJsonDocument>

TcpClient::TcpClient(QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this))
{}

void TcpClient::connectToHost(const QHostAddress &hostAddress, qint64 port) {
    socket->connectToHost(hostAddress, port);
}

/**
 * @brief TcpClient::sendAsync
 * @param tcpRequest
 * @param timeout disabled if equals to -1
 */
void TcpClient::sendAsync(const TcpRequest &tcpRequest, qint64 timeout)
{
    if (!send(tcpRequest)) {
        qDebug() << "TcpClient::sendAsync: failed";
        return;
    }
    if (timeout != -1) {
        QTimer::singleShot(timeout, this, [=]() {
            qDebug() << "TcpClient::sendAsync: timeout";
            emit timedOut();
            return;
        });
    }
    connect(socket, &QTcpSocket::readyRead, this, [=](){
        emit readyRead(TcpResponse::fromSocket(socket));
    });
}

/**
 * @brief TcpClient::send
 * @param tcpRequest
 * @return return false if an error occurred
 */
bool TcpClient::send(const TcpRequest &tcpRequest)
{
    if (!socket || !socket->isOpen()) {
        qDebug() << "TcpClient::send: socket not open";
        emit notOpened();
        return false;
    }
    if (socket->write(tcpRequest) == -1) {
        qDebug() << "TcpClient::send: socket writing error";
        emit writtingErrorOccurred();
        return false;
    }
    return true;
}
