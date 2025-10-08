#ifndef TCPRESETPASSWORDCLIENT_H
#define TCPRESETPASSWORDCLIENT_H

#include "tcplocalclient.h"

class TcpResetPasswordClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpResetPasswordClient(QObject *parent = nullptr);
    void sendAsync(const QString &oldPasswordHash, const QString &newPasswordHash);
};

#endif // TCPRESETPASSWORDCLIENT_H
