#ifndef SQLAUTHENTICATOR_H
#define SQLAUTHENTICATOR_H

#include "sqllocalserver.h"
#include "authorization.h"
#include "user.h"

class SqlAuthenticator : public SqlLocalServer
{
public:
    SqlAuthenticator();
    User exec(const Authorization &authorization);
};

#endif // SQLAUTHENTICATOR_H
