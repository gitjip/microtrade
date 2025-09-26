#include "usercenterwidget.h"
#include "logindialog.h"
#include "mylib_constants.h"
#include "registerdialog.h"
#include "ui_usercenterwidget.h"
#include "user.h"

UserCenterWidget::UserCenterWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::UserCenterWidget), client(nullptr) {
    ui->setupUi(this);
}

UserCenterWidget::~UserCenterWidget() { delete ui; }

void UserCenterWidget::setClient(My::TcpClient *client) {
    this->client = client;
}

void UserCenterWidget::setUserId(int userId) { this->userId = userId; }

void UserCenterWidget::refresh() {
    QJsonObject body;
    body["id"] = userId;
    My::Response res = client->post("/user", My::Headers(), body);
    qDebug() << "UserCenterWidget::refresh:" << res.status << res.headers
             << res.body << res.error;
    if (res.status == 200) {
        My::User user(res.body.toObject());
        ui->lineEditUsername->setText(user.username);
        ui->lineEditPassword->setText(user.password);
    } else {
        ui->lineEditUsername->clear();
        ui->lineEditPassword->clear();
    }
}

void UserCenterWidget::on_pushButtonLogin_clicked() {
    LoginDialog *loginDialog = new LoginDialog(this);
    loginDialog->setClient(client);
    loginDialog->show();
    connect(loginDialog, &LoginDialog::readySetUserId, this, [=](int userId) {
        emit readySetUserId(userId);
        ui->pushButtonLogin->setDisabled(true);
        ui->pushButtonLogout->setDisabled(false);
        ui->pushButtonUnregister->setDisabled(false);
    });
}

void UserCenterWidget::on_pushButtonRegister_clicked() {
    RegisterDialog *registerDialog = new RegisterDialog(this);
    registerDialog->setClient(client);
    registerDialog->show();
}

void UserCenterWidget::on_pushButtonLogout_clicked() {
    emit readySetUserId(0);
    ui->pushButtonLogout->setDisabled(true);
    ui->pushButtonLogin->setDisabled(false);
    ui->pushButtonUnregister->setDisabled(true);
}

void UserCenterWidget::on_pushButtonUnregister_clicked() {
    My::Response res = client->post("/unregister", My::Headers(), userId);
    qDebug() << "UserCenterWidget::on_pushButtonUnregister_clicked:" << res.status
             << res.headers << res.body << res.error;
    emit readySetUserId(0);
    ui->pushButtonUnregister->setDisabled(true);
    ui->pushButtonLogin->setDisabled(false);
    ui->pushButtonLogout->setDisabled(true);
}
