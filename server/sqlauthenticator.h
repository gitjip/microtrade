#ifndef SQLAUTHENTICATOR_H
#define SQLAUTHENTICATOR_H

#include "sqllocalserver.h"
#include "authorization.h"
#include "user.h"

/**
 * @brief find authorization where token matches, which is useful for SQL functions in need for pre-authentication
 */
class SqlAuthenticator : public SqlLocalServer
{
public:
    SqlAuthenticator();
    User exec(const Authorization &authorization);
};

#endif // SQLAUTHENTICATOR_H
