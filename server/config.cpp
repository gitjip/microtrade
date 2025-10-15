#include "config.h"

Config *Config::instance() {
    static Config configure;
    return &configure;
}

Config::Config(QObject *parent)
    : QObject{parent},
    m_settings(new QSettings("server.ini", QSettings::IniFormat, this)) {
    qDebug() << "================================";
    qDebug() << "[Config] host_address" << hostAddress();
    qDebug() << "[Config] port" << port();
    qDebug() << "[Config] timeout" << timeout();
    qDebug() << "[Config] max_thread_count" << maxThreadCount();
    qDebug() << "[Config] database_name" << databaseName();
    qDebug() << "================================";
}

QHostAddress Config::hostAddress() const {
    return QHostAddress(m_settings->value("Network/host_address").toString());
}

quint64 Config::port() const {
    return m_settings->value("Network/port").toULongLong();
}

qint64 Config::timeout() const {
    return m_settings->value("Network/timeout").toLongLong();
}

int Config::maxThreadCount() const {
    return m_settings->value("ThreadPool/max_thread_count").toInt();
}

QString Config::databaseName() const {
    return m_settings->value("Database/database_name").toString();
}
