#ifndef USER_H
#define USER_H

#include "entity.h"
#include <QUrl>

class ENTITY_EXPORT User : public Entity {
public:
    User();
    User(const qint64 &id, const QDateTime &createdAt, const QDateTime &removedAt,
         const QString &username, const QString &passwordHash,
         const QUrl &avatarUrl = QUrl());
    static User fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;

public:
    QString username() const;
    QString passwordHash() const;
    QUrl avatarUrl() const;

private:
    void initFromJson(const QJsonObject &json) override;

private:
    QString m_username;
    QString m_passwordHash;
    QUrl m_avatarUrl;
};

#endif // USER_H
