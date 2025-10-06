#include "sqllocalserver.h"
#include "config.h"

SqlLocalServer::SqlLocalServer() {
    if (SqlServer::open(Config::instance()->databaseName())) {
        qDebug() << "SqlLocalServer::SqlLocalServer:"
                 << "successfully open database";
    }
}
