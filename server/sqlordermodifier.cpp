#include "sqlordermodifier.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>

SqlOrderModifier::SqlOrderModifier(QObject *parent) : QObject{parent}
{
    m_db = SqlServer::instance()->db();
}

bool SqlOrderModifier::cancelOrder(qint64 orderId, qint64 userId)
{
    if (!m_db.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    // 开始事务
    if (!m_db.transaction()) {
        qDebug() << "Failed to start transaction: " << m_db.lastError().text();
        return false;
    }

    try {
        // 检查订单是否存在且属于该用户
        QSqlQuery checkQuery(m_db);
        checkQuery.prepare("SELECT id FROM `order` WHERE id = ? AND user_id = ?");
        checkQuery.addBindValue(orderId);
        checkQuery.addBindValue(userId);
        if (!checkQuery.exec()) {
            qDebug() << "Failed to check order: " << checkQuery.lastError().text();
            m_db.rollback();
            return false;
        }

        if (!checkQuery.next()) {
            qDebug() << "Order not found or does not belong to user";
            m_db.rollback();
            return false;
        }

        // 更新订单状态为Cancelled
        QSqlQuery updateQuery(m_db);
        updateQuery.prepare("UPDATE `order` SET status = ? WHERE id = ?");
        updateQuery.addBindValue(2); // 2 对应 Order::Status::Cancelled
        updateQuery.addBindValue(orderId);
        if (!updateQuery.exec()) {
            qDebug() << "Failed to update order status: " << updateQuery.lastError().text();
            m_db.rollback();
            return false;
        }

        // 提交事务
        if (!m_db.commit()) {
            qDebug() << "Failed to commit transaction: " << m_db.lastError().text();
            m_db.rollback();
            return false;
        }

        return true;
    }
    catch (const std::exception &e) {
        qDebug() << "Exception occurred: " << e.what();
        m_db.rollback();
        return false;
    }
}