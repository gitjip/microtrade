#include "sqlcartitemlistfinder.h"
#include <QSqlError>

SqlCartItemListFinder::SqlCartItemListFinder() {}

QList<CartItem> SqlCartItemListFinder::exec(const Cart &cart) {
    QSqlQuery query(db);
    query.prepare(
        "SELECT * FROM cart_items WHERE cart_id=:cart_id AND removed_at IS NULL");
    query.bindValue(":cart_id", cart.id());
    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return {};
    }
    QList<CartItem> cartItemList;
    while (query.next()) {
        CartItem cartItem{query.value("id").toLongLong(),
                          query.value("created_at").toDateTime(),
                          query.value("removed_at").toDateTime(),
                          query.value("cart_id").toLongLong(),
                          query.value("product_id").toLongLong(),
                          query.value("quantity").toLongLong()};
        cartItemList.append(cartItem);
    }
    return cartItemList;
}
