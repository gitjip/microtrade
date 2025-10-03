#include "authorization.h"

Authorization::Authorization() {}

Authorization::Authorization(const qint64 &id, const QDateTime &createdAt,
                             const QDateTime &removedAt, const qint64 &userId,
                             const QString &token)
    : Entity(id, createdAt, removedAt), m_userId(userId), m_token(token) {}

Authorization Authorization::fromJson(const QJsonObject &json) {
    Authorization authorization;
    authorization.initFromJson(json);
    return authorization;
}

QJsonObject Authorization::toJson() const {
    QJsonObject json = Entity::toJson();
    json["userId"] = m_userId;
    json["token"] = m_token;
    return json;
}

void Authorization::initFromJson(const QJsonObject &json) {
    Entity::initFromJson(json);
    m_userId = json["userId"].toInteger();
    m_token = json["token"].toString();
}

qint64 Authorization::userId() const { return m_userId; }

QString Authorization::token() const { return m_token; }
