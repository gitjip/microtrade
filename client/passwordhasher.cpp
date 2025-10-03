#include "passwordhasher.h"
#include <QCryptographicHash>

PasswordHasher::PasswordHasher() {}

QString PasswordHasher::hash(const QString &password){
    QByteArray data = password.toUtf8();
    return QCryptographicHash::hash(data, QCryptographicHash::Sha256).toHex();
}
