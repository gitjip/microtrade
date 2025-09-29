#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QObject>
#include <QSettings>

class Configure : public QObject {
    Q_OBJECT
public:
    static Configure* instance();

public:
    // NetWork
    QString hostAddress() const;
    quint64 port() const;
    qint64 timeout() const;
    // ThreadPool
    int maxThreadCount() const;
    // Database
    QString databaseName() const;

signals:

private:
    explicit Configure(QObject *parent = nullptr);
    Configure(const Configure &configure) = delete;
    Configure &operator=(const Configure &configure) = delete;

private:
    QSettings *m_settings;
};

#endif // CONFIGURE_H
