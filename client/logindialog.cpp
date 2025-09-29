#include "logindialog.h"
#include "authorizationmanager.h"
#include "configure.h"
#include "tcploginclient.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginDialog) {
    ui->setupUi(this);
}

LoginDialog::~LoginDialog() { delete ui; }

void LoginDialog::accept() {
    TcpLoginClient *tcpLoginClient = new TcpLoginClient(this);
    tcpLoginClient->sendAsync(ui->usernameLineEdit->text(),
                              ui->passwordLineEdit->text(),
                              Configure::instance()->timeout());
    connect(tcpLoginClient, &TcpLoginClient::readyRead, this,
            [=](const TcpResponse &tcpResponse) {
                qDebug() << "LoginDialog::accept:"
                 << "response fetched:" << QJsonObject(tcpResponse);
        if (tcpResponse.success()) {
                    QJsonObject responseBody = tcpResponse.body();
            AuthorizationManager::instance()->login(
                        responseBody["authorized_token"].toString());
        } else {
            qDebug() << "LoginDialog::accept:" << "error:"
                     << TcpResponse::statusTypeToString(tcpResponse.statusType())
                     << tcpResponse.statusDetail();
        }
    });
    close();
}
