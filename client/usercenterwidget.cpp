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

void UserCenterWidget::setUserId(int userId) { this->userId = userId; }

void UserCenterWidget::on_pushButtonLogin_clicked() {
    LoginDialog *loginDialog = new LoginDialog(this);
    loginDialog->setClient(client);
    loginDialog->show();
    connect(loginDialog, &LoginDialog::gotUserId, this,
            [=]() { emit gotUserId(userId); });
}

void UserCenterWidget::on_pushButtonRegister_clicked() {
    RegisterDialog *registerDialog = new RegisterDialog(this);
    registerDialog->setClient(client);
    registerDialog->show();
}

void UserCenterWidget::on_pushButtonLogout_clicked() { emit gotUserId(0); }

void UserCenterWidget::onGotUserId(int userId) {
    QJsonObject headers;
    headers["id"] = userId;
    My::Response res = client->get("/api/user", headers, QJsonValue());
    // need to be refactoried
}
