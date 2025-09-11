#ifndef USER_H
#define USER_H

#include <QtGlobal>
#include <QString>

class User
{
public:
    User();
    virtual ~User();

private:
    int id;
    QString username;
    QString password;
};

#endif // USER_H
