#ifndef CART_H
#define CART_H

#include "entity.h"
#include <QDateTime>

class ENTITY_EXPORT Cart : public Entity
{
public:
    enum class Attribute { Id, UserId, CreatedAt, DeletedAt, IsDeleted };

public:
    Cart();
    Cart(const QString &id, const QString &userId, const QDateTime &createdAt,
         const QDateTime &deletedAt, bool isDeleted = false);
    Cart(const QJsonObject &jsonObj);
    static QString attributeToString(Attribute attribute);
    operator QJsonObject() const override;

public:
    QString id() const;
    QString userId() const;
    QDateTime createdAt() const;
    QDateTime deletedAt() const;
    bool isDeleted() const;

private:
    QString m_id;
    QString m_userId;
    QDateTime m_createdAt;
    QDateTime m_deletedAt;
    bool m_isDeleted = false;
};

#endif // CART_H
