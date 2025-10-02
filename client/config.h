#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>

class Config : public QObject {
    Q_OBJECT
public:
    static Config *instance();

public:
    QString hostAddress() const;
    quint64 port() const;
    qint64 timeout() const;

private:
    explicit Config(QObject *parent = nullptr);
    Config(const Config &config) = delete;
    Config &operator=(const Config &config) = delete;

private:
    QSettings *m_settings;
};

#endif // CONFIG_H
