#ifndef SQLTOKENGENERATOR_H
#define SQLTOKENGENERATOR_H

#include <sqlserver.h>

class SqlTokenGenerator : public SqlServer
{
public:
    SqlTokenGenerator();
    QString exec(const QString &userId);
};

#endif // SQLTOKENGENERATOR_H
