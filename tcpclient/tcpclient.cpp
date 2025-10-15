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
 * @param maxTime disabled if equals to -1
 */
void TcpClient::sendAsync(const TcpRequest &request, qint64 maxTime) {
    QTimer *timer = new QTimer(this);
    if (maxTime != -1) {
        timer->setInterval(maxTime);
        timer->setSingleShot(true);
        timer->start();
    }
    connect(timer, &QTimer::timeout, this, [=]() {
        emit timeout();
        deleteLater();
    });
    connect(m_socket, &QTcpSocket::readyRead, this, [=]() {
        timer->stop();
        emit readyRead(TcpResponse::fromSocket(m_socket));
        deleteLater();
    });
    if (!send(request)) {
        qDebug() << Q_FUNC_INFO << "failed";
        deleteLater();
    }
}

/**
 * @brief TcpClient::send
 * @param request
 * @return return false if an error occurred
 */
bool TcpClient::send(const TcpRequest &request) {
    if (!m_socket || !m_socket->isOpen()) {
        qDebug() << Q_FUNC_INFO << "socket not open";
        emit notOpened();
        return false;
    }
    if (m_socket->write(request.toBytes()) == -1) {
        qDebug() << Q_FUNC_INFO << "socket writing error";
        emit writtingErrorOccurred();
        return false;
    }
    return true;
}
