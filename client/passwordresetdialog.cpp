#include "passwordresetdialog.h"
#include "passwordhasher.h"
#include "tcpresetpasswordclient.h"
#include "ui_passwordresetdialog.h"

PasswordResetDialog::PasswordResetDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::PasswordResetDialog) {
    ui->setupUi(this);
}

PasswordResetDialog::~PasswordResetDialog() { delete ui; }

void PasswordResetDialog::accept() {
    TcpResetPasswordClient *resetPasswordClient =
        new TcpResetPasswordClient(this);
    connect(resetPasswordClient, &TcpResetPasswordClient::readyRead, this,
            &PasswordResetDialog::onPasswordUpdaterClientReadyRead);
    QString oldPasswordHash = PasswordHasher::hash(ui->oldLineEdit->text());
    QString newPasswordHash = PasswordHasher::hash(ui->newLineEdit->text());
    resetPasswordClient->sendAsync(oldPasswordHash, newPasswordHash);
    close();
}

void PasswordResetDialog::onPasswordUpdaterClientReadyRead(
    const TcpResponse &response) {
    qDebug() << Q_FUNC_INFO << response.toJson();
    if (response.success()) {
        qDebug() << Q_FUNC_INFO << "success";
        emit reseted();
    }
}
