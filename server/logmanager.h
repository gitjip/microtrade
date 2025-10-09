#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QObject>
#include <QDateTime>
#include "log.h"

/**
 * @brief 全局日志管理器类，提供统一的日志记录接口
 */
class LogManager : public QObject
{
    Q_OBJECT
public:
    static LogManager *getInstance();
    
    // 记录不同级别的日志
    void info(const QString &text);
    void warning(const QString &text);
    void error(const QString &text);
    
    // 直接记录一个日志对象
    bool log(const Log &log);
    
private:
    explicit LogManager(QObject *parent = nullptr);
    LogManager(const LogManager &other) = delete;
    LogManager &operator=(const LogManager &other) = delete;
    
    // 防止复制和赋值
};

#endif // LOGMANAGER_H