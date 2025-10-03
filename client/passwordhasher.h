#ifndef PASSWORDHASHER_H
#define PASSWORDHASHER_H

#include <QString>

class PasswordHasher
{
public:
    PasswordHasher();
    static QString hash(const QString &password);
};

#endif // PASSWORDHASHER_H
