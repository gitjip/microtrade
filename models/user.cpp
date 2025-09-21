#include "user.h"

namespace My {
User::User(int id, const QString &username, const QString &password, bool active)
    : id(id), username(username), password(password), active(active) {}

User::User(const QJsonObject &object) {
    id = object["id"].toInt();
    username = object["username"].toString();
    password = object["password"].toString();
}

User::~User() {}

User::operator QJsonObject() const {
    QJsonObject res;
    res["id"] = id;
    res["username"] = username;
    res["password"] = password;
    return res;
}
} // namespace My
