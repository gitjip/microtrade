#ifndef TCPMONTHDAILYCOSTCLIENT_H
#define TCPMONTHDAILYCOSTCLIENT_H

#include "tcplocalclient.h"

class TcpMonthDailyCostClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpMonthDailyCostClient(QObject *parent = nullptr);
    void sendAsync(int year, int month);
};

#endif // TCPMONTHDAILYCOSTCLIENT_H
