#include "logindialog.h"
#include "authorization.h"
#include "authorizationmanager.h"
#include "passwordhasher.h"
#include "tcploginclient.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginDialog) {
    ui->setupUi(this);
}

LoginDialog::~LoginDialog() { delete ui; }

void LoginDialog::accept() {
    TcpLoginClient *loginClient = new TcpLoginClient(this);
    connect(loginClient, &TcpLoginClient::readyRead, this, &LoginDialog::login);
    loginClient->sendAsync(ui->usernameLineEdit->text(),
                           PasswordHasher::hash(ui->passwordLineEdit->text()));
    close();
}

void LoginDialog::login(const TcpResponse &response) {
    qDebug() << "LoginDialog::accept:"
             << "response:" << response.toJson();
    if (response.success()) {
        QJsonObject responseBody = response.body();
        Authorization authorization =
            Authorization::fromJson(responseBody["authorization"].toObject());
        qDebug() << "LoginDialog::login:" << authorization.token();
        AuthorizationManager::instance()->login(authorization.token());
    } else {
        qDebug() << "LoginDialog::accept:" << "error:"
                 << TcpResponse::statusTypeToString(response.statusType())
                 << response.statusDetail();
    }
}
