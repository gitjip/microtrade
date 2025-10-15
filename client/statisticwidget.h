#ifndef STATISTICWIDGET_H
#define STATISTICWIDGET_H

#include "tcpresponse.h"
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

namespace Ui {
class StatisticWidget;
}

class StatisticWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticWidget(QWidget *parent = nullptr);
    ~StatisticWidget();

public slots:
    void updateChart();
    void readyUpdateChart(const TcpResponse &response);
    void clearChart();

private:
    Ui::StatisticWidget *ui;
};

#endif // STATISTICWIDGET_H
