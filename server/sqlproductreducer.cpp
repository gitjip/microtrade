#include "sqlproductreducer.h"
#include <QSqlError>

SqlProductReducer::SqlProductReducer() {}

QMap<Product, qint64> SqlProductReducer::exec(const Product &product) {
    qDebug() << "SqlPayer::exec:" << "product_id:" << product.id();
}
