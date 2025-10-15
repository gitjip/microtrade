#include "statisticwidget.h"
#include "commander.h"
#include "tcpmonthdailycostclient.h"
#include "tcpmonthlycostclient.h"
#include "ui_statisticwidget.h"
#include <QJsonArray>
#include <QTime>
#include <QTimer>

StatisticWidget::StatisticWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::StatisticWidget) {
    ui->setupUi(this);
    connect(Commander::instance(), &Commander::privateUpdated, this,
            &StatisticWidget::updateChart);
    connect(ui->calendarWidget, &QCalendarWidget::currentPageChanged, this,
            &StatisticWidget::updateChart);
}

StatisticWidget::~StatisticWidget() { delete ui; }

void StatisticWidget::updateChart() {
    TcpMonthDailyCostClient *monthDailyCostClient =
        new TcpMonthDailyCostClient(this);
    connect(monthDailyCostClient, &TcpMonthDailyCostClient::readyRead, this,
            &StatisticWidget::readyUpdateChart);
    monthDailyCostClient->sendAsync(ui->calendarWidget->yearShown(),
                                    ui->calendarWidget->monthShown());
}

void StatisticWidget::readyUpdateChart(const TcpResponse &response) {
    qDebug() << Q_FUNC_INFO << response.toJson();
    QJsonObject body = response.body();
    QJsonArray costArray = body["costArray"].toArray();
    QLineSeries *series = new QLineSeries();

    for (qsizetype i = 0; i < costArray.count(); ++i) {
        QJsonObject dailyCost = costArray[i].toObject();
        QDate date = QDate::fromString(dailyCost["date"].toString());
        double cost = dailyCost["cost"].toDouble();
        series->append(QDateTime(date, QTime(12, 0)).toMSecsSinceEpoch(), cost);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Consumption of This Month");

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setFormat("MM-dd");
    axisX->setTitleText("date");

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("expense");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    ui->chartWidget->setChart(chart);
    ui->chartWidget->setRenderHint(QPainter::Antialiasing);
}
