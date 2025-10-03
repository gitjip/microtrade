#ifndef SQLAUTHENTICATOR_H
#define SQLAUTHENTICATOR_H

#include <sqlserver.h>

class SqlAuthenticator : public SqlServer
{
public:
    SqlAuthenticator();
    QString exec(const QString &authorization);
};

#endif // SQLAUTHENTICATOR_H
