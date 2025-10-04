#include "sqlcartitemcreator.h"
#include <QSqlError>

SqlCartItemCreator::SqlCartItemCreator() {}

CartItem SqlCartItemCreator::exec(const Cart &cart, const Product &product) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO cart_items (cart_id,product_id) VALUES "
                  "(:cart_id,:product_id)");
    query.bindValue(":cart_id", cart.id());
    query.bindValue("product_id", product.id());
    if (!query.exec()) {
        qDebug() << "SqlCartItemCreator::exec:" << query.lastError().text();
        return {};
    }
    return {};
}
