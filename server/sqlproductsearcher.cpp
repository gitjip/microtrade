#include "sqlproductsearcher.h"
#include <QSqlError>

SqlProductSearcher::SqlProductSearcher() {}

QList<Product> SqlProductSearcher::exec(const QString &keyword) {
    QSqlQuery query(db);
    if (keyword.isEmpty()) {
        query.prepare("SELECT * FROM products WHERE removed_at IS NULL");
    } else {
        query.prepare("SELECT * FROM products WHERE "
                      "(name LIKE :keyword OR description LIKE :keyword) "
                      "AND removed_at IS NULL");
        query.bindValue(":keyword", "%" + keyword + "%");
    }
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
