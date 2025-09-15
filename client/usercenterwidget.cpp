#include "usercenterwidget.h"
#include "logindialog.h"
#include "registerdialog.h"
#include "ui_usercenterwidget.h"

UserCenterWidget::UserCenterWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::UserCenterWidget), client(nullptr) {
    ui->setupUi(this);
}

UserCenterWidget::~UserCenterWidget() { delete ui; }

void UserCenterWidget::setClient(My::TcpClient *client) {
    this->client = client;
}

void UserCenterWidget::setUser(My::User *user) { this->user = user; }

void UserCenterWidget::on_pushButtonLogin_clicked() {
    LoginDialog *loginDialog = new LoginDialog(this);
    loginDialog->setClient(client);
    loginDialog->show();
    connect(loginDialog, &LoginDialog::gotUser, this, [=](){
        emit gotUser(user);
    });
}

void UserCenterWidget::on_pushButtonRegister_clicked()
{
    RegisterDialog *registerDialog = new RegisterDialog(this);
    registerDialog->setClient(client);
    registerDialog->show();
}

