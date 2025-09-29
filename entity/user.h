#ifndef USER_H
#define USER_H

#include "entity.h"
#include <QDateTime>

class ENTITY_EXPORT User : public Entity {
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
    User(const QString &id, const QString &username, const QString &password,
         const QUrl &avatarUrl, const QDateTime &registeredAt,
         const QDateTime &unregisteredAt, bool isDeleted = false);
    User(const QJsonObject &jsonObj);
    static QString attributeToString(Attribute attribute);
    operator QJsonObject() const override;

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
