#ifndef SQLAUTHORIZER_H
#define SQLAUTHORIZER_H

#include <sqlserver.h>

class SqlAuthorizer : public SqlServer
{
public:
    SqlAuthorizer();
    QString exec(const QString &userId);
};

#endif // SQLAUTHORIZER_H
