#include "usernamealterdialog.h"
#include "tcpalterusernameclient.h"
#include "ui_usernamealterdialog.h"

UsernameAlterDialog::UsernameAlterDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::UsernameAlterDialog) {
    ui->setupUi(this);
}

UsernameAlterDialog::~UsernameAlterDialog() { delete ui; }

void UsernameAlterDialog::setOldUsername(const QString &username) {
    ui->oldLineEdit->setText(username);
    ui->newLineEdit->setText(username);
}

void UsernameAlterDialog::accept() {
    TcpAlterUsernameClient *alterUsernameClient =
        new TcpAlterUsernameClient(this);
    connect(alterUsernameClient, &TcpAlterUsernameClient::readyRead, this,
            &UsernameAlterDialog::onUsernameAlterClientReadyRead);
    alterUsernameClient->sendAsync(ui->newLineEdit->text());
    close();
}

void UsernameAlterDialog::onUsernameAlterClientReadyRead(
    const TcpResponse &response) {
    qDebug() << Q_FUNC_INFO << response.toJson();
    if (response.success()) {
        qDebug() << Q_FUNC_INFO << "success";
        emit altered();
    }
}
