#include "promotionwidget.h"
#include "ui_promotionwidget.h"

PromotionWidget::PromotionWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PromotionWidget)
{
    ui->setupUi(this);
}

PromotionWidget::~PromotionWidget()
{
    delete ui;
}
