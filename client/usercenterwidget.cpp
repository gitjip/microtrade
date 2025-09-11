#include "usercenterwidget.h"
#include "ui_usercenterwidget.h"
#include "logindialog.h"

UserCenterWidget::UserCenterWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserCenterWidget)
{
    ui->setupUi(this);
}

UserCenterWidget::~UserCenterWidget()
{
    delete ui;
}

void UserCenterWidget::on_pushButtonLogin_clicked()
{
    LoginDialog *loginDialog = new LoginDialog(this);
    loginDialog->show();
}

