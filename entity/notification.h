#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "entity.h"
#include <QDateTime>

class Notification : public Entity
{
public:
    enum class Attribute { Id, UserId, Content, CreatedAt, DeletedAt, IsDeleted };

public:
    Notification();
    static QString toString(Attribute attribute);
    operator QJsonObject() const override;

public:
    QString id() const;
    QString userId() const;
    QString content() const;
    QDateTime createdAt() const;
    QDateTime deletedAt() const;
    bool isDeleted() const;

private:
    QString m_id;
    QString m_userId;
    QString m_content;
    QDateTime m_createdAt;
    QDateTime m_deletedAt;
    bool m_isDeleted;
};

#endif // NOTIFICATION_H
