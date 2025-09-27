#ifndef USER_H
#define USER_H

#include "entity.h"
#include <QDateTime>

class User : public Entity
{
public:
    enum class Attribute {
        Id,
        Username,
        Password,
        AvatarUrl,
        RegisteredAt,
        UnregisteredAt,
        IsDeleted
    };

public:
    User();
    QString toString(Attribute attribute);

public:
    QString id() const;
    QString username() const;
    QString password() const;
    QUrl avatarUrl() const;
    QDateTime registeredAt() const;
    QDateTime unregisteredAt() const;
    bool isDeleted() const;

private:
    QString m_id;
    QString m_username;
    QString m_password;
    QUrl m_avatarUrl;
    QDateTime m_registeredAt;
    QDateTime m_unregisteredAt;
    bool m_isDeleted = false;
};

#endif // USER_H
