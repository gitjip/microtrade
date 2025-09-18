#include "logindialog.h"
#include "mylib_constants.h"
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
    QJsonObject body;
    body["username"] = ui->lineEditUsername->text();
    body["password"] = ui->lineEditPassword->text();
    My::Response res = client->post("/login", My::Headers(), body);
    if (res.status == 200) {
        int userId = res.body["id"].toInt();
        qDebug() << "LoginDialog::on_pushButtonConfirm_clicked:"
                 << res.body["id"].toInt() << res.body["username"].toString()
                 << res.body["password"].toString();
        emit readySetUserId(userId);
        qDebug() << "LoginDialog::on_pushButtonConfirm_clicked:" << userId;
    } else {
        QMessageBox::critical(this, "login failed", res.error);
    }
    close();
}

void LoginDialog::on_pushButtonCancel_clicked() { close(); }
