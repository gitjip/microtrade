#ifndef SQLORDERMODIFIER_H
#define SQLORDERMODIFIER_H

#include "sqllocalserver.h"

class SqlOrderModifier : public SqlLocalServer
{
public:
    SqlOrderModifier();
    bool exec(qint64 orderId, qint64 userId);
};

#endif // SQLORDERMODIFIER_H
