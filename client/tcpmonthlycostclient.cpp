#include "tcpmonthlycostclient.h"
#include "commander.h"

TcpMonthlyCostClient::TcpMonthlyCostClient(QObject *parent)
    : TcpLocalClient{parent}
{}

void TcpMonthlyCostClient::sendAsync(int year, int month){
    QJsonObject body;
    body["authorizationToken"] = Commander::instance()->token();
    body["year"]=year;
    body["month"]=month;
    TcpLocalClient::sendAsync("/monthly-cost", body);
}
