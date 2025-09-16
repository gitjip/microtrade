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

void LoginDialog::on_pushButtonConfirm_clicked() {
    QJsonObject headers;
    headers["username"] = ui->lineEditUsername->text();
    headers["password"] = ui->lineEditPassword->text();
    My::Response res = client->get("/api/user", headers, QJsonValue());
    if (res.status == 200) {
        int userId = res.body["id"].toInt();
        qDebug() << res.body["id"].toInt() << res.body["username"].toString()
                 << res.body["password"].toString();
        emit gotUserId(userId);
    } else {
        QMessageBox::critical(this, "登录失败", res.error);
    }
    close();
}

void LoginDialog::on_pushButtonCancel_clicked() { close(); }
