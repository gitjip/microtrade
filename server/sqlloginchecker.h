#ifndef SQLLOGINCHECKER_H
#define SQLLOGINCHECKER_H

#include "sqlserver.h"

class SqlLoginChecker : public SqlServer
{
public:
    SqlLoginChecker();
    QString exec(const QString &username, const QString &password);
};

#endif // SQLLOGINCHECKER_H
