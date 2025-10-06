#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QHostAddress>

class Config : public QObject {
    Q_OBJECT
public:
    static Config* instance();

public:
    // NetWork
    QHostAddress hostAddress() const;
    quint64 port() const;
    qint64 timeout() const;
    // ThreadPool
    int maxThreadCount() const;
    // Database
    QString databaseName() const;

signals:

private:
    explicit Config(QObject *parent = nullptr);
    Config(const Config &configure) = delete;
    Config &operator=(const Config &configure) = delete;

private:
    QSettings *m_settings;
};

#endif // CONFIG_H
