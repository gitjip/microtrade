#include "logindialog.h"
#include "mylib_constants.h"
#include "ui_logindialog.h"

#include "tcpclient.h"
#include "localusermanager.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginDialog) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

LoginDialog::~LoginDialog() { delete ui; }

void LoginDialog::on_pushButtonConfirm_clicked() {
    My::TcpClient *client = new My::TcpClient(this);
    QJsonObject body;
    body["username"] = ui->lineEditUsername->text();
    body["password"] = ui->lineEditPassword->text();
    My::Response res = client->post("/login", My::Headers(), body);
    if (res.status == 200) {
        int userId = res.body["id"].toInt();

        qDebug() << "LoginDialog::on_pushButtonConfirm_clicked:" << userId
                 << res.body["username"].toString()
                 << res.body["password"].toString();
    } else {
        QMessageBox::critical(this, "login failed", res.error);
    }
    client->deleteLater();
    close();
}

void LoginDialog::on_pushButtonCancel_clicked() { close(); }
