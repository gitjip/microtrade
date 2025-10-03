#include "notification.h"

Notification::Notification() {}

Notification::Notification(const qint64 &id, const QDateTime &createdAt, const QDateTime &removedAt,
                           const qint64 &userId, const QString &content)
    : Entity(id, createdAt, removedAt), m_userId(userId), m_content(content) {}

Notification Notification::fromJson(const QJsonObject &json) {
    Notification notification;
    notification.initFromJson(json);
    return notification;
}

QJsonObject Notification::toJson() const {
    QJsonObject json = Entity::toJson();
    json["userId"] = m_userId;
    json["content"] = m_content;
    return json;
}

void Notification::initFromJson(const QJsonObject &json) {
    Entity::initFromJson(json);
    m_userId = json["userId"].toInteger();
    m_content = json["content"].toString();
}

qint64 Notification::userId() const { return m_userId; }
QString Notification::content() const { return m_content; }
