#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "entity.h"

class ENTITY_EXPORT Notification : public Entity {
public:
    Notification();
    Notification(const qint64 &id, const QDateTime &createdAt,
                 const QDateTime &removedAt, const qint64 &userId,
                 const QString &content);
    static Notification fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;

public:
    qint64 userId() const;
    QString content() const;

private:
    void initFromJson(const QJsonObject &json) override;

private:
    qint64 m_userId = -1;
    QString m_content;
};

#endif // NOTIFICATION_H
