#include "sqlcartsyncer.h"
#include <QSqlError>

SqlCartSyncer::SqlCartSyncer() {}

bool SqlCartSyncer::exec(const Cart &cart,
                         const QList<CartItem> &cartItemList) {
    QSqlQuery query(db);
    query.prepare(
        "UPDATE cart_items SET quantity=:quantity WHERE cart_id=:cart_id AND "
        "product_id=:product_id AND removed_at IS NULL");
    bool success = true;
    for (int i = 0; i < cartItemList.count(); ++i) {
        query.bindValue(":quantity", cartItemList[i].quantity());
        query.bindValue(":cart_id", cart.id());
        query.bindValue(":product_id", cartItemList[i].productId());
        if (!query.exec()) {
            // qDebug() << Q_FUNC_INFO << cartItemList[i].toJson()
            //          << query.lastError().text();
            success = false;
        }
    }
    // qDebug() << Q_FUNC_INFO << "success";
    return success;
}
