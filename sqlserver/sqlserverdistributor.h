#ifndef SQLSERVERDISTRIBUTOR_H
#define SQLSERVERDISTRIBUTOR_H

#include <QObject>

class SqlServerDistributor : public QObject
{
    Q_OBJECT
public:
    explicit SqlServerDistributor(QObject *parent = nullptr);

signals:
};

#endif // SQLSERVERDISTRIBUTOR_H
