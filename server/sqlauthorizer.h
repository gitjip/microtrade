#ifndef SQLAUTHORIZER_H
#define SQLAUTHORIZER_H

#include "sqllocalserver.h"
#include "user.h"
#include "authorization.h"

class SqlAuthorizer : public SqlLocalServer
{
public:
    SqlAuthorizer();
    Authorization exec(const User &user);
};

#endif // SQLAUTHORIZER_H
