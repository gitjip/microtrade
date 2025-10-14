#include "logindialog.h"
#include "authorization.h"
#include "commander.h"
#include "passwordhasher.h"
#include "tcploginclient.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginDialog) {
    ui->setupUi(this);
}

LoginDialog::~LoginDialog() { delete ui; }

void LoginDialog::accept() {
    QMetaObject::invokeMethod(
        this,
        [=]() {
            if (!ui->usernameLineEdit->text().trimmed().isEmpty() &&
                !ui->passwordLineEdit->text().trimmed().isEmpty()) {
                TcpLoginClient *loginClient = new TcpLoginClient(this);
                connect(loginClient, &TcpLoginClient::readyRead, this,
                        &LoginDialog::login);
                connect(loginClient, &TcpLoginClient::timedOut, this, [=]() {
                    QMessageBox::critical(this, "Login failed!",
                                          "Connection timeout.");
                });
                loginClient->sendAsync(
                    ui->usernameLineEdit->text(),
                    PasswordHasher::hash(ui->passwordLineEdit->text()));
                close();
            } else {
                QMessageBox::information(this, "Tip", "Input username and password.");
            }
        },
        Qt::QueuedConnection);
}

void LoginDialog::login(const TcpResponse &response) {
    QMetaObject::invokeMethod(
        this,
        [=]() {
            if (response.success()) {
                QJsonObject responseBody = response.body();
                Authorization authorization =
                    Authorization::fromJson(responseBody["authorization"].toObject());
                Commander::instance()->login(authorization.token());
            } else {
                QMessageBox::critical(
                    this, "Login failed!",
                    "Your username or password maybe wrong. Please try again.");
            }
        },
        Qt::QueuedConnection);
}
