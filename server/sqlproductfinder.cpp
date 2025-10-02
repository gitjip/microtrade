#include "sqlproductfinder.h"
#include "config.h"
#include <QSqlError>

SqlProductFinder::SqlProductFinder() {
    if (SqlServer::open(Config::instance()->databaseName())) {
        qDebug() << "SqlProductFinder::SqlProductFinder:"
                 << "successfully open database";
    }
}

Product SqlProductFinder::exec(const QString &productId) {
    qDebug() << "SqlProductFinder::exec:" << "productId:" << productId;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM products WHERE id=:id AND is_deleted=0");
    query.bindValue(":id", productId);
    if (!query.exec()) {
        qDebug() << "SqlProductFinder::exec:" << "executing error:"
                 << query.lastError().text();
        return Product();
    }
    if (!query.next()) {
        qDebug() << "SqlProductFinder::exec:" << "not found";
        return Product();
    }
    return Product(query.value("id").toString(), query.value("name").toString(),
                   query.value("description").toString(),
                   query.value("price").toDouble(),
                   query.value("stock").toLongLong(),
                   Product::stringToCategory(query.value("category").toString()),
                   QUrl(query.value("image_url").toString()),
                   query.value("listed_at").toDateTime(),
                   query.value("delisted_at").toDateTime(),
                   query.value("is_deleted").toBool());
}
