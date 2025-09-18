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

void UserCenterWidget::refresh(int userId) {
    QJsonObject body;
    body["id"] = userId;
    My::Response res = client->post("/user", My::Headers(), body);
    qDebug() << "UserCenterWidget::refresh:" << res.status << res.headers
             << res.body << res.error;
    My::User user(res.body.toObject());
    ui->lineEditUsername->setText(user.username);
    ui->lineEditPassword->setText(user.password);
}

void UserCenterWidget::on_pushButtonLogin_clicked() {
    LoginDialog *loginDialog = new LoginDialog(this);
    loginDialog->setClient(client);
    loginDialog->show();
    connect(loginDialog, &LoginDialog::gotUserId, this,
            [=](int userId) { emit gotUserId(userId); });
}

void UserCenterWidget::on_pushButtonRegister_clicked() {
    RegisterDialog *registerDialog = new RegisterDialog(this);
    registerDialog->setClient(client);
    registerDialog->show();
}

void UserCenterWidget::on_pushButtonLogout_clicked() { emit gotUserId(0); }
