#include "user.h"

namespace My {
User::User(int id, const QString &username, const QString &password)
    : id(id), username(username), password(password) {}

User::~User() {}
} // namespace My
