#include "paymentwidget.h"
#include "ui_paymentwidget.h"

PaymentWidget::PaymentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaymentWidget)
{
    ui->setupUi(this);
}

PaymentWidget::~PaymentWidget()
{
    delete ui;
}
