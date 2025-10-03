#include "sqlauthenticator.h"
#include <QSqlError>

SqlAuthenticator::SqlAuthenticator() {}

QString SqlAuthenticator::exec(const QString &authorization){
    QSqlQuery query(db);
    query.prepare("SELECT * FROM login_records WHERE authorized_token=:authorization AND is_deleted=0");
    query.bindValue(":authorization", authorization);
    if(!query.exec()){

        return {};
    }
}
