#include "configure.h"

Configure *Configure::instance() {
    static Configure configure;
    return &configure;
}

Configure::Configure(QObject *parent)
    : QObject{parent},
    m_settings(new QSettings("server.ini", QSettings::IniFormat, this)) {
    qDebug() << "server:" << "Configure::Configure:" << "host_address"
             << hostAddress();
    qDebug() << "server:" << "Configure::Configure:" << "port" << port();
    qDebug() << "server:" << "Configure::Configure:" << "timeout" << timeout();
    qDebug() << "server:" << "Configure::Configure:" << "max_thread_count" << maxThreadCount();
    qDebug() << "server:" << "Configure::Configure:" << "database_name" << databaseName();
}

QString Configure::hostAddress() const {
    return m_settings->value("Network/host_address").toString();
}

quint64 Configure::port() const {
    return m_settings->value("Network/port").toULongLong();
}

qint64 Configure::timeout() const {
    return m_settings->value("Network/timeout").toLongLong();
}

int Configure::maxThreadCount() const {
    return m_settings->value("ThreadPool/max_thread_count").toInt();
}

QString Configure::databaseName() const{
    return m_settings->value("Database/database_name").toString();
}
