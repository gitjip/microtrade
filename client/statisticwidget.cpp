#include "statisticwidget.h"
#include "commander.h"
#include "tcpmonthdailycostclient.h"
#include "ui_statisticwidget.h"
#include <QJsonArray>
#include <QTime>
#include <QTimer>
#include <QToolTip>

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

        QVector<QPair<QDateTime, double>> pointData;

        for (qsizetype i = 0; i < costArray.count(); ++i) {
            QJsonObject dailyCost = costArray[i].toObject();
            QDate date = QDate::fromString(dailyCost["date"].toString());
            double cost = dailyCost["cost"].toDouble();
            totalCost += cost;
            maxCost = qMax(maxCost, cost);

            QDateTime dateTime(date, QTime(12, 0));
            series->append(dateTime.toMSecsSinceEpoch(), cost);
            pointData.append(qMakePair(dateTime, cost));
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

        if (costArray.count() > 0) {
            axisX->setMin(
                QDateTime::fromString(costArray.first().toString()).addDays(-1));
            axisX->setMax(
                QDateTime::fromString(costArray.last().toString()).addDays(1));
        }

        series->setPointsVisible(true);

        connect(series, &QLineSeries::hovered, this,
                [pointData](const QPointF &point, bool state) {
            if (state) {
                for (const auto &data : pointData) {
                    if (qAbs(data.first.toMSecsSinceEpoch() - point.x()) <
                        86400000) {
                        QToolTip::showText(QCursor::pos(),
                                           QString("Date: %1\nCost: %2")
                                               .arg(data.first.toString("MM-dd"))
                                               .arg(data.second, 0, 'f', 2));
                        break;
                    }
                }
            } else {
                QToolTip::hideText();
            }
        });
        connect(series, &QLineSeries::clicked, this,
                [pointData, this](const QPointF &point) {
            for (const auto &data : pointData) {
                if (qAbs(data.first.toMSecsSinceEpoch() - point.x()) <
                    86400000) {
                    ui->calendarWidget->setSelectedDate(data.first.date());
                    break;
                }
            }
        });

        // series->setPointsVisible(true);
        // series->setPointLabelsVisible(true);
        // series->setPointLabelsFormat("@yPoint");
        // series->setPointLabelsColor(Qt::white);
        // series->setPointLabelsFont(QFont("Arial", 9, QFont::Bold));

        ui->chartWidget->setChart(chart);
        ui->chartWidget->setRenderHint(QPainter::Antialiasing);
        ui->chartWidget->show();
    }
}
