#ifndef SQLQUERY_H
#define SQLQUERY_H

#include "mylib_global.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

namespace My {
class MYLIB_EXPORT SqlQuery : public QSqlQuery {
public:
    SqlQuery();
    virtual ~SqlQuery();

private:
    QSqlDatabase db;
};
} // namespace My

#endif // SQLQUERY_H
