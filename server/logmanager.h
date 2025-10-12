#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QObject>
#include <QDateTime>
#include "log.h"

/**
 * @brief The global log writting manager
 */
class LogManager : public QObject
{
    Q_OBJECT
public:
    static LogManager *instance();
    void info(const QString &text);
    void warning(const QString &text);
    void error(const QString &text);
    bool exec(const Log &log);
    
private:
    explicit LogManager(QObject *parent = nullptr);
    LogManager(const LogManager &other) = delete;
    LogManager &operator=(const LogManager &other) = delete;
};

#endif // LOGMANAGER_H
