#include "sqlproductreducer.h"
#include <QSqlError>

SqlProductReducer::SqlProductReducer() {}

QMap<Product, qint64>
SqlProductReducer::exec(const QMap<Product, qint64> &quantityMap) {
    QSqlQuery checkQuery(db);
    QSqlQuery reduceQuery(db);
    checkQuery.prepare(
        "SELECT * FROM products WHERE id=:id AND removed_at IS NULL");
    reduceQuery.prepare(
        "UPDATE products SET stock=:stock WHERE id=:id AND removed_at IS NULL");
    QMap<Product, qint64> returned;
    QMapIterator it(quantityMap);
    while (it.hasNext()) {
        it.next();
        checkQuery.bindValue(":id", it.key().id());
        // qDebug() << Q_FUNC_INFO << it.key().id() << it.value()
        //          << checkQuery.boundValueNames();
        // qDebug() << Q_FUNC_INFO << it.key().id() << it.value()
        //          << checkQuery.boundValues();
        if (!checkQuery.exec()) {
            qDebug() << Q_FUNC_INFO << "check error:" << checkQuery.lastError().text()
                     << it.key().id() << it.value();
        } else if (!checkQuery.next()) {
            qDebug() << Q_FUNC_INFO
                     << "check error:" << checkQuery.lastError().text();
        } else {
            qint64 stock = checkQuery.value("stock").toLongLong();
            qint64 finalQuantity = qMin(it.value(), stock);
            reduceQuery.bindValue(":id", it.key().id());
            reduceQuery.bindValue(":stock", stock - finalQuantity);
            // qDebug() << Q_FUNC_INFO << it.key().id() << it.value()
            //          << reduceQuery.boundValueNames();
            // qDebug() << Q_FUNC_INFO << it.key().id() << it.value()
            //          << reduceQuery.boundValues();
            if (!reduceQuery.exec()) {
                qDebug() << Q_FUNC_INFO
                         << "reduce error:" << reduceQuery.lastError().text()
                         << it.key().id() << it.value();
            } else if (finalQuantity > 0) {
                returned.insert(it.key(), finalQuantity);
            }
        }
    }
    return returned;
}
