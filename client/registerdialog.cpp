#include "registerdialog.h"
#include "passwordhasher.h"
#include "tcpregisterclient.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::RegisterDialog) {
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog() { delete ui; }

void RegisterDialog::accept() {
    TcpRegisterClient *registerClient = new TcpRegisterClient(this);
    connect(registerClient, &TcpClient::readyRead, this,
            &RegisterDialog::onReadyRead);
    registerClient->sendAsync(ui->usernameLineEdit->text(),
                              PasswordHasher::hash(ui->passwordLineEdit->text()));
    close();
}

void RegisterDialog::onReadyRead(const TcpResponse &response) {
    qDebug() << "RegisterDialog::onReadyRead:" << "response:"
             << response.toJson();
    if (response.success()) {
        qDebug() << "RegisterDialog::onReadyRead:" << "success";
    } else {
        qDebug() << "RegisterDialog::onReadyRead:" << "error:"
                 << response.statusDetail();
    }
}
