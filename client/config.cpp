#include "config.h"

Config::Config(QObject *parent)
    : QObject(parent),
    m_settings(new QSettings("client.ini", QSettings::IniFormat, this)) {
    qDebug() << "Configure::Configure:" << "fileName:" << m_settings->fileName();
    qDebug() << "Configure::Configure:" << "host_address" << hostAddress();
    qDebug() << "Configure::Configure:" << "port" << port();
    qDebug() << "Configure::Configure:" << "timeout" << timeout();
}

Config *Config::instance() {
    static Config config;
    return &config;
}

/**
 * @brief from Network
 * @return hostAddress to QHostAddress
 */
QString Config::hostAddress() const {
    return m_settings->value("Network/host_address").toString();
}

/**
 * @brief from Network
 * @return port
 */
quint64 Config::port() const {
    return m_settings->value("Network/port").toULongLong();
}

/**
 * @brief from Network
 * @return timeout
 */
qint64 Config::timeout() const {
    return m_settings->value("Network/timeout").toLongLong();
}
