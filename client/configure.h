#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QSettings>

class Configure : public QObject {
    Q_OBJECT
public:
    static Configure *instance();

public:
    QString hostAddress() const;
    quint64 port() const;
    qint64 timeout() const;

private:
    explicit Configure(QObject *parent = nullptr);
    Configure(const Configure &config) = delete;
    Configure &operator=(const Configure &config) = delete;

private:
    QSettings *m_settings;
};

#endif // CONFIGURE_H
