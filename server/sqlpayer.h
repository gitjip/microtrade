#ifndef SQLPAYER_H
#define SQLPAYER_H

#include <sqlserver.h>

class SqlPayer : public SqlServer
{
public:
    SqlPayer();
    bool exec(const QString &productId);
};

#endif // SQLPAYER_H
