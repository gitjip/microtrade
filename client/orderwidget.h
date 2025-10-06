#ifndef ORDERWIDGET_H
#define ORDERWIDGET_H

#include "tcpresponse.h"
#include <QWidget>

namespace Ui {
class OrderWidget;
}

class OrderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWidget(QWidget *parent = nullptr);
    ~OrderWidget();

public slots:
    void update();
    void onOrderClientReadyRead(const TcpResponse &response);

private:
    Ui::OrderWidget *ui;
};

#endif // ORDERWIDGET_H
