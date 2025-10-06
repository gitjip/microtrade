#include "sqlproductlistfinder.h"
#include <QSqlError>

SqlProductListFinder::SqlProductListFinder() {}

QList<Product> SqlProductListFinder::exec() {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM products WHERE removed_at IS NULL");
    if (!query.exec()) {
        qDebug() << "SqlProductListFinder::exec:" << query.lastError().type()
                 << query.lastError().text();
        return {};
    }
    QList<Product> productList;
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
        productList.append(product);
        qDebug() << Q_FUNC_INFO << product.id()
                 << query.value("image_url").toString()
                 << QUrl(query.value("image_url").toString()).errorString();
    }
    return productList;
}
