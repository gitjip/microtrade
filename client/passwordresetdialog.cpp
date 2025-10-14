#include "passwordresetdialog.h"
#include "passwordhasher.h"
#include "tcpresetpasswordclient.h"
#include "ui_passwordresetdialog.h"
#include <QMessageBox>

PasswordResetDialog::PasswordResetDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::PasswordResetDialog) {
    ui->setupUi(this);
}

PasswordResetDialog::~PasswordResetDialog() { delete ui; }

void PasswordResetDialog::accept() {
    QMetaObject::invokeMethod(
        this,
        [=]() {
            if (!ui->oldLineEdit->text().trimmed().isEmpty() &&
                !ui->newLineEdit->text().trimmed().isEmpty()) {
                TcpResetPasswordClient *resetPasswordClient =
                    new TcpResetPasswordClient(this);
                connect(resetPasswordClient, &TcpResetPasswordClient::readyRead, this,
                        &PasswordResetDialog::onPasswordUpdaterClientReadyRead);
                connect(resetPasswordClient, &TcpResetPasswordClient::timedOut,
                        this, [=]() {
                    QMessageBox::critical(this, "Reset password failed!",
                                          "Connection timeout.");
                });
                QString oldPasswordHash =
                    PasswordHasher::hash(ui->oldLineEdit->text());
                QString newPasswordHash =
                    PasswordHasher::hash(ui->newLineEdit->text());
                resetPasswordClient->sendAsync(oldPasswordHash, newPasswordHash);
                close();
            } else {
                QMessageBox::information(this, "Tip", "Input password.");
            }
        },
        Qt::QueuedConnection);
}

void PasswordResetDialog::onPasswordUpdaterClientReadyRead(
    const TcpResponse &response) {
    QMetaObject::invokeMethod(
        this,
        [=]() {
        qDebug() << Q_FUNC_INFO << response.toJson();
        if (response.success()) {
            qDebug() << Q_FUNC_INFO << "success";
            emit reseted();
            QMessageBox::information(this, "Reset password successfully!",
                                     "Your password has been updated.");
        } else {
            if (response.statusType() == TcpResponse::StatusType::Failed) {
                QMessageBox::critical(this, "Reset password failed!",
                                      "Old Password is wrong.");
            } else {
                QMessageBox::critical(this, "Reset password failed!",
                                      "Unknown error occurred.");
            }
        }
        },
        Qt::QueuedConnection);
}
