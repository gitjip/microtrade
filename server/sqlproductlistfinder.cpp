#include "sqlproductlistfinder.h"
#include "configure.h"
#include <QSqlError>

SqlProductListFinder::SqlProductListFinder() {
    if (SqlServer::open(Configure::instance()->databaseName())) {
        qDebug() << "SqlProductListFinder::SqlProductListFinder:"
                 << "successfully open database";
    }
}

QList<Product> SqlProductListFinder::exec() {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM products");
    if (!query.exec()) {
        qDebug() << "SqlProductListFinder::exec:" << "executing error:"
                 << query.lastError().text();
        return {};
    }
    QList<Product> productList;
    while (query.next()) {
        productList.append(Product(
            query.value("id").toString(), query.value("name").toString(),
            query.value("description").toString(), query.value("price").toDouble(),
            query.value("stock").toLongLong(),
            Product::stringToCategory(query.value("category").toString()),
            QUrl(query.value("image_url").toString()),
            query.value("listed_at").toDateTime(),
            query.value("delisted_at").toDateTime(),
            query.value("is_deleted").toBool()));
    }
    return productList;
}
