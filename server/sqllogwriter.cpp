#include "sqllogwriter.h"
#include <QMetaType>
#include <QSqlError>
#include <QSqlQuery>

SqlLogWriter::SqlLogWriter() {}

bool SqlLogWriter::exec(const Log &log) {
    if (log.isNull()) {
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO logs (created_at, removed_at, type, text) VALUES "
                  "(:created_at, :removed_at, :type, :text)");
    query.bindValue(":created_at", log.createdAt().toString());
    query.bindValue(":removed_at",
                    log.removedAt().isValid()
                        ? log.removedAt().toString()
                        : QVariant(QMetaType::fromType<QString>()));
    query.bindValue(":type", Log::typeToString(log.type()));
    query.bindValue(":text", log.text());

    if (!query.exec()) {
        qDebug() << "SqlLogWriter::exec: " << query.lastError().type()
                 << query.lastError().text();
        return false;
    }

    return true;
}
