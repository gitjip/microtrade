#include "notificationwidget.h"
#include "ui_notificationwidget.h"

NotificationWidget::NotificationWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NotificationWidget)
{
    ui->setupUi(this);
}

NotificationWidget::~NotificationWidget()
{
    delete ui;
}
