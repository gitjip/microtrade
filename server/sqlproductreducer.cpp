#include "sqlproductreducer.h"
#include <QSqlError>

SqlProductReducer::SqlProductReducer() {}

QMap<Product, qint64>
SqlProductReducer::exec(const QMap<Product, qint64> &quantityMap) {
    QSqlQuery checkQuery(db);
    QSqlQuery reduceQuery(db);
    checkQuery.prepare(
        "SELECT stock FROM products WHERE id=:id AND removed_at IS NULL");
    reduceQuery.prepare(
        "UPDATE products SET stock=:stock WHERE id=:id AND removed_at IS NULL");
    QMap<Product, qint64> returned;
    QMapIterator it(quantityMap);
    while (it.hasNext()) {
        it.next();
        checkQuery.bindValue(":id", it.key().id());
        if (!checkQuery.exec()) {
            qDebug() << Q_FUNC_INFO << "check error:" << checkQuery.lastError().text()
                     << it.key().id() << it.value();
        } else {
            qint64 stock = checkQuery.value("stock").toLongLong();
            qint64 finalQuantity = qMin(it.value(), stock);
            reduceQuery.bindValue(":id", it.key().id());
            reduceQuery.bindValue(":stock", stock - finalQuantity);
            if (!reduceQuery.exec()) {
                qDebug() << Q_FUNC_INFO
                         << "reduce error:" << reduceQuery.lastError().text()
                         << it.key().id() << it.value();
            } else {
                returned.insert(it.key(), finalQuantity);
            }
        }
    }
    return returned;
}
