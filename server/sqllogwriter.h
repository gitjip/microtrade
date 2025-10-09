#ifndef SQLLOGWRITER_H
#define SQLLOGWRITER_H

#include "sqllocalserver.h"
#include "log.h"

/**
 * @brief 将日志写入到数据库中
 */
class SqlLogWriter : public SqlLocalServer
{
public:
    SqlLogWriter();
    bool exec(const Log &log);
};

#endif // SQLLOGWRITER_H