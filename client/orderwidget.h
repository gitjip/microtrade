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
    enum class OrderColomn { Id, Cost, Status, CreatedAt };
    enum class OrderItemColomn { Id, Cost, Quantity, CreatedAt, ProductId };

private:
    void initFrontEnd();

private:
    Ui::OrderWidget *ui;
};

#endif // ORDERWIDGET_H
