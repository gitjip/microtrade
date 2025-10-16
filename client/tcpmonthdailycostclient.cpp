#include "tcpmonthdailycostclient.h"
#include "commander.h"

TcpMonthDailyCostClient::TcpMonthDailyCostClient(QObject *parent)
    : TcpLocalClient{parent} {}

void TcpMonthDailyCostClient::sendAsync(int year, int month) {
    QJsonObject body;
    body["authorizationToken"] = Commander::instance()->token();
    body["year"] = year;
    body["month"] = month;
    TcpLocalClient::sendAsync("/month-daily-cost", body);
}
