#ifndef TCPALTERUSERNAMECLIENT_H
#define TCPALTERUSERNAMECLIENT_H

#include "tcplocalclient.h"

class TcpAlterUsernameClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpAlterUsernameClient(QObject *parent = nullptr);
    void sendAsync(const QString &username);
};

#endif // TCPALTERUSERNAMECLIENT_H
