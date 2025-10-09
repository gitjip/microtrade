#include "usernamealterdialog.h"
#include "tcpalterusernameclient.h"
#include "ui_usernamealterdialog.h"
#include <QMessageBox>

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
    QMetaObject::invokeMethod(
        this,
        [=]() {
        if (!ui->newLineEdit->text().trimmed().isEmpty()) {
                TcpAlterUsernameClient *alterUsernameClient =
                new TcpAlterUsernameClient(this);
            connect(alterUsernameClient, &TcpAlterUsernameClient::readyRead, this,
                        &UsernameAlterDialog::onUsernameAlterClientReadyRead);
                alterUsernameClient->sendAsync(ui->newLineEdit->text());
            close();
        } else {
            QMessageBox::information(this, "Tip", "Input new username.");
        }
        },
        Qt::QueuedConnection);
}

void UsernameAlterDialog::onUsernameAlterClientReadyRead(
    const TcpResponse &response) {
    QMetaObject::invokeMethod(
        this,
        [=]() {
            qDebug() << Q_FUNC_INFO << response.toJson();
            if (response.success()) {
                qDebug() << Q_FUNC_INFO << "success";
                emit altered();
                QMessageBox::information(this, "Alter username successfully!",
                                         "Your username has been updated.");
            } else {
                if (response.statusType() == TcpResponse::StatusType::Failed) {
                    QMessageBox::critical(this, "Alter username failed!",
                                          "This username may be used by another user.");
                } else {
                    QMessageBox::critical(this, "Alter username failed!",
                                          "Unknown error occurred.");
                }
            }
        },
        Qt::QueuedConnection);
}
