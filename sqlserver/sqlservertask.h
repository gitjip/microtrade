#ifndef SQLSERVERTASK_H
#define SQLSERVERTASK_H

#include <QObject>

class SqlServerHandler : public QObject
{
    Q_OBJECT
public:
    explicit SqlServerHandler(QObject *parent = nullptr);

signals:
};

#endif // SQLSERVERTASK_H
