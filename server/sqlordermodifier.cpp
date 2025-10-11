#include "sqlordermodifier.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>
#include "order.h"

SqlOrderModifier::SqlOrderModifier() {}

bool SqlOrderModifier::exec(qint64 orderId, qint64 userId)
{
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    // 开始事务
    if (!db.transaction()) {
        qDebug() << "Failed to start transaction: " << db.lastError().text();
        return false;
    }

    try {
        // 检查订单是否存在且属于该用户
        QSqlQuery checkQuery(db);
        checkQuery.prepare("SELECT id FROM `orders` WHERE id = ? AND user_id = ? AND removed_at IS NULL");
        checkQuery.addBindValue(orderId);
        checkQuery.addBindValue(userId);
        if (!checkQuery.exec()) {
            qDebug() << "Failed to check order: " << checkQuery.lastError().text();
            db.rollback();
            return false;
        }

        if (!checkQuery.next()) {
            qDebug() << "Order not found or does not belong to user";
            db.rollback();
            return false;
        }

        // 更新订单状态为Cancelled
        QSqlQuery updateQuery(db);
        updateQuery.prepare("UPDATE `orders` SET status = ? WHERE id = ? AND removed_at IS NULL");
        updateQuery.addBindValue(Order::statusToString(Order::Status::Cancelled));
        updateQuery.addBindValue(orderId);
        if (!updateQuery.exec()) {
            qDebug() << "Failed to update order status: " << updateQuery.lastError().text();
            db.rollback();
            return false;
        }

        // 提交事务
        if (!db.commit()) {
            qDebug() << "Failed to commit transaction: " << db.lastError().text();
            db.rollback();
            return false;
        }

        return true;
    }
    catch (const std::exception &e) {
        qDebug() << "Exception occurred: " << e.what();
        db.rollback();
        return false;
    }
}
