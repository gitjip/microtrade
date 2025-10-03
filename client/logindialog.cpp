#include "logindialog.h"
#include "authorizationmanager.h"
#include "passwordhasher.h"
#include "tcploginclient.h"
#include "ui_logindialog.h"
#include "user.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginDialog) {
    ui->setupUi(this);
}

LoginDialog::~LoginDialog() { delete ui; }

void LoginDialog::accept() {
    TcpLoginClient *tcpLoginClient = new TcpLoginClient(this);
    connect(tcpLoginClient, &TcpLoginClient::readyRead, this,
            &LoginDialog::login);
    tcpLoginClient->sendAsync(
        User(-1, {}, {}, ui->usernameLineEdit->text(),
             PasswordHasher::hash(ui->passwordLineEdit->text())));
    close();
}

void LoginDialog::login(const TcpResponse &response) {
    qDebug() << "LoginDialog::accept"
             << "response" << response.toJson();
    if (response.success()) {
        QJsonObject responseBody = response.body();
        AuthorizationManager::instance()->login(
            responseBody["authorization"].toString());
    } else {
        qDebug() << "LoginDialog::accept" << "error"
                 << TcpResponse::statusTypeToString(response.statusType())
                 << response.statusDetail();
    }
}
