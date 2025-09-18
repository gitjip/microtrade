#include "cartwidget.h"
#include "ui_cartwidget.h"

CartWidget::CartWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CartWidget)
{
    ui->setupUi(this);
}

CartWidget::~CartWidget()
{
    delete ui;
}
