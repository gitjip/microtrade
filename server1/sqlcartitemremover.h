#ifndef SQLCARTITEMREMOVER_H
#define SQLCARTITEMREMOVER_H

#include "sqllocalserver.h"

class SqlCartItemRemover : public SqlLocalServer
{
public:
    SqlCartItemRemover();
    bool exec(qint64 cartId, qint64 productId);
};

#endif // SQLCARTITEMREMOVER_H
