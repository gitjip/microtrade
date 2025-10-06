#ifndef SQLAUTHORIZER_H
#define SQLAUTHORIZER_H

#include "sqllocalserver.h"
#include "user.h"
#include "authorization.h"

/**
 * @brief create authorization with userId and token, especially on user ready login
 */
class SqlAuthorizer : public SqlLocalServer
{
public:
    SqlAuthorizer();
    Authorization exec(const User &user);
};

#endif // SQLAUTHORIZER_H
