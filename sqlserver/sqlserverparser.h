#ifndef SQLSERVERPARSER_H
#define SQLSERVERPARSER_H

#include <QObject>

class SqlServerParser : public QObject
{
    Q_OBJECT
public:
    explicit SqlServerParser(QObject *parent = nullptr);

signals:
};

#endif // SQLSERVERPARSER_H
