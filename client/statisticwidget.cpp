#include "statisticwidget.h"
#include "commander.h"
#include "tcpmonthdailycostclient.h"
#include "ui_statisticwidget.h"
#include <QJsonArray>
#include <QTime>
#include <QTimer>

StatisticWidget::StatisticWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::StatisticWidget) {
    ui->setupUi(this);
    ui->chartWidget->hide();
    connect(Commander::instance(), &Commander::privateUpdated, this,
            &StatisticWidget::updateChart);
    connect(ui->calendarWidget, &QCalendarWidget::currentPageChanged, this,
            &StatisticWidget::updateChart);
    connect(Commander::instance(), &Commander::loggedout, this,
            &StatisticWidget::clearChart);
}

StatisticWidget::~StatisticWidget() { delete ui; }

void StatisticWidget::clearChart() { ui->chartWidget->hide(); }

void StatisticWidget::updateChart() {
    TcpMonthDailyCostClient *monthDailyCostClient =
        new TcpMonthDailyCostClient(this);
    connect(monthDailyCostClient, &TcpMonthDailyCostClient::readyRead, this,
            &StatisticWidget::readyUpdateChart);
    monthDailyCostClient->sendAsync(ui->calendarWidget->yearShown(),
                                    ui->calendarWidget->monthShown());
}

void StatisticWidget::readyUpdateChart(const TcpResponse &response) {
    if (response.success()) {
    QJsonObject body = response.body();
    QJsonArray costArray = body["costArray"].toArray();
    QLineSeries *series = new QLineSeries();

    double totalCost = 0;
    double maxCost = 0;

    for (qsizetype i = 0; i < costArray.count(); ++i) {
        QJsonObject dailyCost = costArray[i].toObject();
        QDate date = QDate::fromString(dailyCost["date"].toString());
        double cost = dailyCost["cost"].toDouble();
        totalCost += cost;
        maxCost = qMax(maxCost, cost);
        series->append(QDateTime(date, QTime(12, 0)).toMSecsSinceEpoch(), cost);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(
        QString("Consumption of This Month: %1").arg(totalCost, 0, 'f', 2));
    chart->setTheme(QChart::ChartThemeDark);

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setFormat("MM-dd");
    axisX->setTitleText("date");

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("expense");
    axisY->setMax(maxCost + 10);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    ui->chartWidget->setChart(chart);
    ui->chartWidget->setRenderHint(QPainter::Antialiasing);
    ui->chartWidget->show();
    }
}
