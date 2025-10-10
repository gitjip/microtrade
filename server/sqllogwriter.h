#ifndef SQLLOGWRITER_H
#define SQLLOGWRITER_H

#include "sqllocalserver.h"
#include "log.h"

/**
 * @brief write log into database
 */
class SqlLogWriter : public SqlLocalServer
{
public:
    SqlLogWriter();
    bool exec(const Log &log);
};

#endif // SQLLOGWRITER_H
