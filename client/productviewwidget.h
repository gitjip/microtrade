#ifndef PAYMENTWIDGET_H
#define PAYMENTWIDGET_H

#include <QWidget>

namespace Ui {
class PaymentWidget;
}

class PaymentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PaymentWidget(QWidget *parent = nullptr);
    ~PaymentWidget();

private:
    Ui::PaymentWidget *ui;
};

#endif // PAYMENTWIDGET_H
