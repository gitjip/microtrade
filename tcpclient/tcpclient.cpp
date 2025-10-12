#include "tcpclient.h"
#include <QJsonDocument>
#include <QTimer>

TcpClient::TcpClient(QObject *parent)
    : QObject(parent), m_socket(new QTcpSocket(this)) {}

void TcpClient::connectToHost(const QHostAddress &hostAddress, qint64 port) {
    m_socket->connectToHost(hostAddress, port);
}

/**
 * @brief TcpClient::sendAsync
 * @param request
 * @param timeout disabled if equals to -1
 */
void TcpClient::sendAsync(const TcpRequest &request, qint64 timeout) {
    QTimer *timer = new QTimer(this);
    if (timeout != -1) {
        timer->setInterval(timeout);
        timer->setSingleShot(true);
        timer->start();
    }
    connect(timer, &QTimer::timeout, this, [=]() {
        qDebug() << "TcpClient::sendAsync: timeout";
        emit timedOut();
        deleteLater();
    });
    connect(m_socket, &QTcpSocket::connected, this, [=]() {
        qDebug() << "socket state:" << m_socket->state();
        if (timer->remainingTime() == 0) {
            emit timedOut();
            deleteLater();
        } else {
            if (!send(request)) {
                qDebug() << "TcpClient::sendAsync: failed";
                deleteLater();
            } else {
                connect(m_socket, &QTcpSocket::readyRead, this, [=]() {
                    emit readyRead(TcpResponse::fromSocket(m_socket));
                    // qDebug() << "TcpClient::sendAsync:" << "request:"
                    //          << request.toJson();
                    deleteLater();
                });
            }
        }
    });
}

/**
 * @brief TcpClient::send
 * @param request
 * @return return false if an error occurred
 */
bool TcpClient::send(const TcpRequest &request) {
    if (!m_socket || !m_socket->isOpen()) {
        qDebug() << "TcpClient::send: socket not open";
        emit notOpened();
        return false;
    }
    if (m_socket->write(request.toBytes()) == -1) {
        qDebug() << "TcpClient::send: socket writing error";
        emit writtingErrorOccurred();
        return false;
    }
    return true;
}
