#ifndef SQLCARTFINDER_H
#define SQLCARTFINDER_H

#include "sqllocalserver.h"
#include "cart.h"
#include "user.h"

class SqlCartFinder : public SqlLocalServer
{
public:
    SqlCartFinder();
    Cart exec(const User &user);
};

#endif // SQLCARTFINDER_H
