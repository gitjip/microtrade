#ifndef SQLPRODUCTSEARCHER_H
#define SQLPRODUCTSEARCHER_H

#include "sqllocalserver.h"
#include "product.h"

class SqlProductSearcher : public SqlLocalServer
{
public:
    SqlProductSearcher();
    QList<Product> exec(const QStringList &tokens);
};

#endif // SQLPRODUCTSEARCHER_H
