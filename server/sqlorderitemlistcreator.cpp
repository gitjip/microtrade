#include "sqlorderitemlistcreator.h"
#include <QSqlError>

SqlOrderItemListCreator::SqlOrderItemListCreator() {}

bool SqlOrderItemListCreator::exec(qint64 orderId,
                                   const QMap<Product, qint64> &quantityMap) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO order_items "
                  "(created_at,order_id,product_id,quantity,cost) VALUES "
                  "(:created_at,:order_id,:product_id,:quantity,:cost)");
    query.bindValue(":created_at", QDateTime::currentDateTime());
    query.bindValue(":order_id", orderId);
    bool success = true;
    QMapIterator it(quantityMap);
    while (it.hasNext()) {
        it.next();
        query.bindValue(":product_id", it.key().id());
        query.bindValue(":quantity", it.value());
        query.bindValue(":cost", it.key().price() * it.value());
        if (!query.exec()) {
            qDebug() << Q_FUNC_INFO << query.lastError().text() << it.key().id()
                     << it.value();
            success = false;
        }
    }
    return success;
}
