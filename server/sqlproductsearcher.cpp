#include "sqlproductsearcher.h"
#include <QSqlError>

SqlProductSearcher::SqlProductSearcher() {}

QList<Product> SqlProductSearcher::exec(const QStringList &tokens) {
    QSqlQuery query(db);
    QString sql = "SELECT * FROM products WHERE removed_at IS NULL";
    QMap<QString, QString> valueMap;
    if (!tokens.isEmpty()) {
        sql += " AND (";
        QList<QString> conditions;
        int paramIndex = 0;
        foreach (const QString &token, tokens) {
            QString cond = QString("(name LIKE :token%1 OR "
                                   "description LIKE :token%1 OR "
                                   "category LIKE :token%1)")
                               .arg(paramIndex);
            conditions << cond;
            valueMap[QString(":token%1").arg(paramIndex)] = "%" + token + "%";
            paramIndex++;
        }
        sql += conditions.join(" OR ") + ")";
    }
    query.prepare(sql);
    for (QMapIterator it(valueMap); it.hasNext();) {
        it.next();
        qDebug() << it.key() << it.value();
        query.bindValue(it.key(), it.value());
    }
    qDebug() << Q_FUNC_INFO << sql;
    qDebug() << Q_FUNC_INFO << query.boundValueNames();
    qDebug() << Q_FUNC_INFO << query.boundValues();
    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return {};
    }
    QList<Product> results;
    while (query.next()) {
        Product product{
                        query.value("id").toLongLong(),
            query.value("created_at").toDateTime(),
            query.value("removed_at").toDateTime(),
            query.value("name").toString(),
            query.value("description").toString(),
            query.value("price").toDouble(),
            query.value("stock").toLongLong(),
            Product::stringToCategory(query.value("category").toString()),
            QUrl(query.value("image_url").toString())};
        results.append(product);
    }
    return results;
}
