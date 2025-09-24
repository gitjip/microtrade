#include "registerdialog.h"
#include "tcpclient.h"
#include "ui_registerdialog.h"
#include <QMessageBox>

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::RegisterDialog) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

RegisterDialog::~RegisterDialog() { delete ui; }

void RegisterDialog::on_pushButtonConfirm_clicked() {
    My::TcpClient *client = new My::TcpClient;
    QJsonObject body;
    body["username"] = ui->lineEditUsername->text();
    body["password"] = ui->lineEditPassword->text();
    My::Response res = client->post("/register", QJsonObject(), body);
    if (res.status == 200) {
        QMessageBox::information(this, "注册成功", "请回到用户中心继续登录");
    } else {
        QMessageBox::critical(this, "注册失败", res.error);
    }
    client->deleteLater();
    close();
}

void RegisterDialog::on_pushButtonCancel_clicked() { close(); }
