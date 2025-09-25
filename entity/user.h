#ifndef USER_H
#define USER_H

#include "entity.h"

class User : public Entity
{
public:
    User();

private:
    QString m_id;
    QString m_username;
    QString m_password;
    QString m_avatarUrl;
    bool m_isDeleted = false;
};

#endif // USER_H
