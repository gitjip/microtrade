#ifndef SQLSERVERTHREADPOOL_H
#define SQLSERVERTHREADPOOL_H

#include <QObject>

class SqlServerThreadPool : public QObject
{
    Q_OBJECT
public:
    explicit SqlServerThreadPool(QObject *parent = nullptr);

signals:
};

#endif // SQLSERVERTHREADPOOL_H
