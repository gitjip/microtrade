#include "logindialog.h"
#include "ui_logindialog.h"

#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginDialog), client(nullptr) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

LoginDialog::~LoginDialog() { delete ui; }

void LoginDialog::setClient(My::TcpClient *client) { this->client = client; }

void LoginDialog::setUser(My::User *user) { this->user = user; }

void LoginDialog::on_pushButtonConfirm_clicked() {
    QJsonObject headers;
    headers["username"] = ui->lineEditUsername->text();
    headers["password"] = ui->lineEditPassword->text();
    My::Response res = client->get("/api/user", headers, QJsonValue());
    if (res.status == 200) {
        My::User *user =
            new My::User(res.body["id"].toInt(), res.body["username"].toString(),
                                      res.body["password"].toString());
        emit(user);
    } else {
        QMessageBox::critical(this, "登录失败", "用户名或密码错误");
    }
    close();
}

void LoginDialog::on_pushButtonCancel_clicked() { close(); }
