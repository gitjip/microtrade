#include "sqlproductfinder.h"
#include <QSqlError>

SqlProductFinder::SqlProductFinder() {}

Product SqlProductFinder::exec(const Product &product) {
    qDebug() << "SqlProductFinder::exec:" << "productId:" << product.id();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM products WHERE id=:id AND removed_at=NULL");
    query.bindValue(":id", product.id());
    if (!query.exec()) {
        qDebug() << "SqlProductFinder::exec:" << query.lastError().type()
                 << query.lastError().text();
        return {};
    }
    if (!query.next()) {
        qDebug() << "SqlProductFinder::exec:" << "not found";
        return {};
    }
    Product returned{
        query.value("id").toLongLong(),
        query.value("created_at").toDateTime(),
        query.value("removed_at").toDateTime(),
        query.value("name").toString(),
        query.value("description").toString(),
        query.value("price").toDouble(),
        query.value("stock").toLongLong(),
        Product::stringToCategory(query.value("category").toString()),
        QUrl(query.value("image_url").toString())};
    return returned;
}
