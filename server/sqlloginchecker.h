#ifndef SQLLOGINCHECKER_H
#define SQLLOGINCHECKER_H

#include "sqllocalserver.h"
#include "user.h"

/**
 * @brief find userId with username and passwordHash, especially on user trying to login
 */
class SqlLoginChecker : public SqlLocalServer
{
public:
    SqlLoginChecker();
    User exec(const User &user);
};

#endif // SQLLOGINCHECKER_H
