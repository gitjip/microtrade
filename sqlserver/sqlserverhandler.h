#ifndef SQLSERVERHANDLER_H
#define SQLSERVERHANDLER_H

#include <QObject>

class SqlServerHandler : public QObject
{
    Q_OBJECT
public:
    explicit SqlServerHandler(QObject *parent = nullptr);

signals:
};

#endif // SQLSERVERHANDLER_H
