#ifndef TCPMONTHLYCOSTCLIENT_H
#define TCPMONTHLYCOSTCLIENT_H

#include "tcplocalclient.h"

class TcpMonthlyCostClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpMonthlyCostClient(QObject *parent = nullptr);
    void sendAsync(int year, int month);
};

#endif // TCPMONTHLYCOSTCLIENT_H
