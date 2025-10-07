#include "sqlcartitemremover.h"
#include <QDateTime>
#include <QSqlError>

SqlCartItemRemover::SqlCartItemRemover() {}

bool SqlCartItemRemover::exec(qint64 cartId, qint64 productId) {
    QSqlQuery query(db);
    query.prepare(
        "UPDATE cart_items SET removed_at=:removed_at WHERE cart_id=:cart_id AND "
        "product_id=:product_id AND removed_at IS NULL");
    query.bindValue(":removed_at", QDateTime::currentDateTime());
    query.bindValue(":cart_id", cartId);
    query.bindValue(":product_id", productId);
    if (!query.exec()) {
        // qDebug() << Q_FUNC_INFO << query.lastError().text();
        return false;
    }
    // qDebug() << Q_FUNC_INFO << "success";
    return true;
}
