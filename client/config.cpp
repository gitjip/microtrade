#include "config.h"

Config::Config(QObject *parent)
    : QObject(parent),
    m_settings(new QSettings("client.ini", QSettings::IniFormat, this)) {
    qDebug() << "======================";
    qDebug() << "[Config] fileName:" << m_settings->fileName();
    qDebug() << "[Config] host_address" << hostAddress().toString();
    qDebug() << "[Config] port" << port();
    qDebug() << "[Config] timeout" << timeout();
    qDebug() << "======================";
}

Config *Config::instance() {
    static Config config;
    return &config;
}

/**
 * @brief from Network
 * @return hostAddress to QHostAddress
 */
QHostAddress Config::hostAddress() const {
    return QHostAddress(m_settings->value("Network/host_address").toString());
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
