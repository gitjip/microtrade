#include "registerdialog.h"
#include "passwordhasher.h"
#include "tcpregisterclient.h"
#include "ui_registerdialog.h"
#include <QMessageBox>

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::RegisterDialog) {
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog() { delete ui; }

void RegisterDialog::accept() {
    QMetaObject::invokeMethod(
        this,
        [=]() {
            if (!ui->usernameLineEdit->text().trimmed().isEmpty() &&
                !ui->passwordLineEdit->text().trimmed().isEmpty()) {
                TcpRegisterClient *registerClient = new TcpRegisterClient(this);
                connect(registerClient, &TcpClient::readyRead, this,
                        &RegisterDialog::onReadyRead);
                connect(registerClient, &TcpRegisterClient::timeout, this, [=]() {
                    QMessageBox::critical(this, "Register failed!",
                                          "Connection timeout.");
                });
                registerClient->sendAsync(
                    ui->usernameLineEdit->text(),
                    PasswordHasher::hash(ui->passwordLineEdit->text()));
                close();
            } else {
                QMessageBox::information(this, "Tip", "Input username and password.");
            }
        },
        Qt::QueuedConnection);
}

void RegisterDialog::onReadyRead(const TcpResponse &response) {
    QMetaObject::invokeMethod(
        this,
        [=]() {
        if (response.success()) {
                QMessageBox::information(this, "Register successfully!",
                                     "You can login with this account now!");
        } else {
            QMessageBox::critical(
                this, "Register failed!",
                "Your username may already be used by another user.");
        }
        },
        Qt::QueuedConnection);
}
