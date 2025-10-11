#include "logmanager.h"
#include "sqllogwriter.h"
#include <QDebug>

LogManager::LogManager(QObject *parent) : QObject(parent) {}

LogManager *LogManager::getInstance() {
    static LogManager instance;
    return &instance;
}

void LogManager::info(const QString &text) {
    Log log(-1, QDateTime::currentDateTime(), QDateTime(), Log::Type::Info, text);
    bool result = exec(log);
    if (result) {
        qDebug() << "[INFO]" << text;
    }
}

void LogManager::warning(const QString &text) {
    Log log(-1, QDateTime::currentDateTime(), QDateTime(), Log::Type::Warning, text);
    bool result = exec(log);
    if (result) {
        qDebug() << "[WARNING]" << text;
    }
}

void LogManager::error(const QString &text) {
    Log log(-1, QDateTime::currentDateTime(), QDateTime(), Log::Type::Error, text);
    bool result = exec(log);
    if (result) {
        qDebug() << "[ERROR]" << text;
    }
}

bool LogManager::exec(const Log &log) {
    SqlLogWriter logWriter;
    bool result = logWriter.exec(log);
    if (!result) {
        qDebug() << "Failed to write log to database:" << log.text();
    }
    return result;
}
