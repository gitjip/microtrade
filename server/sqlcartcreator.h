#ifndef SQLCARTCREATOR_H
#define SQLCARTCREATOR_H

#include "sqllocalserver.h"
#include "user.h"

/**
 * @brief create cart with userId, especially on user registering
 */
class SqlCartCreator : public SqlLocalServer
{
public:
    SqlCartCreator();
    bool exec(const User &user);
};

#endif // SQLCARTCREATOR_H
