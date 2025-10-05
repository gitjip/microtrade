#ifndef SQLORDERCREATOR_H
#define SQLORDERCREATOR_H

#include "sqllocalserver.h"
#include "product.h"
#include "user.h"

class SqlOrderCreator : public SqlLocalServer
{
public:
    SqlOrderCreator();
    qint64 exec(const User &user, const QMap<Product,qint64> &quantityMap);
};

#endif // SQLORDERCREATOR_H
