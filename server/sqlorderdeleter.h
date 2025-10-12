#ifndef SQLORDERDELETER_H
#define SQLORDERDELETER_H

#include "sqllocalserver.h"

class SqlOrderDeleter : public SqlLocalServer
{
public:
    SqlOrderDeleter();
    bool exec(qint64 orderId, qint64 userId);
};

#endif // SQLORDERDELETER_H