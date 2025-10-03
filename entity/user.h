#ifndef USER_H
#define USER_H

#include "entity.h"
#include <QDateTime>

class ENTITY_EXPORT User : public Entity {
public:
    User();
    User(const qint64 &id, const QString &username, const QString &passwordHash,
         const QUrl &avatarUrl, const QDateTime &createdAt,
         const QDateTime &removedAt, bool isDeleted = false);
    User(const QJsonObject &jsonObj);
    operator QJsonObject() const override;

public:
    qint64 id() const;
    QString username() const;
    QString passwordHash() const;
    QUrl avatarUrl() const;
    QDateTime createdAt() const;
    QDateTime removedAt() const;
    bool isRemoved() const;
    bool isValid() const;

private:
    qint64 m_id;
    QString m_username;
    QString m_passwordHash;
    QUrl m_avatarUrl;
    QDateTime m_createdAt;
    QDateTime m_removedAt;
    bool m_isRemoved = false;
    bool m_isValid = false;
};

#endif // USER_H
