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
        // qDebug() << "RegisterDialog::onReadyRead:" << "response:"
        //          << response.toJson();
        if (response.success()) {
            // qDebug() << "RegisterDialog::onReadyRead:" << "success";
            QMessageBox::information(this, "Register successfully!",
                                     "You can login with this account now!");
        } else {
            // qDebug() << "RegisterDialog::onReadyRead:" << "error:"
            //          << response.statusDetail();
            QMessageBox::critical(
                this, "Register failed!",
                "Your username may already be used by another user.");
        }
        },
        Qt::QueuedConnection);
}
