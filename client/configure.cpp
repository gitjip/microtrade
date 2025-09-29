#include "configure.h"

Configure::Configure(QObject *parent)
    : QObject(parent),
    m_settings(new QSettings("client.ini", QSettings::IniFormat, this)) {
    qDebug() << "Configure::Configure:" << "fileName:" << m_settings->fileName();
    qDebug() << "Configure::Configure:" << "host_address" << hostAddress();
    qDebug() << "Configure::Configure:" << "port" << port();
    qDebug() << "Configure::Configure:" << "timeout" << timeout();
}

Configure *Configure::instance() {
    static Configure config;
    return &config;
}

/**
 * @brief from Network
 * @return hostAddress to QHostAddress
 */
QString Configure::hostAddress() const {
    return m_settings->value("Network/host_address").toString();
}

/**
 * @brief from Network
 * @return port
 */
quint64 Configure::port() const {
    return m_settings->value("Network/port").toULongLong();
}

/**
 * @brief from Network
 * @return timeout
 */
qint64 Configure::timeout() const {
    return m_settings->value("Network/timeout").toLongLong();
}
