#ifndef TCPRESETPASSWORDHANDLER_H
#define TCPRESETPASSWORDHANDLER_H

#include <tcphandler.h>

class TcpResetPasswordHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpResetPasswordHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request) override;
};

#endif // TCPRESETPASSWORDHANDLER_H
