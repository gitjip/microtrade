#include "welcomewidget.h"
#include "commander.h"
// #include "config.h"
#include "logindialog.h"
#include "registerdialog.h"
#include "tcplogoutclient.h"
#include "ui_welcomewidget.h"
#include <QMessageBox>
#include <QTimer>

WelcomeWidget::WelcomeWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::WelcomeWidget) {
    ui->setupUi(this);
    connect(Commander::instance(), &Commander::loggedin, this,
            &WelcomeWidget::onAuthorizationManagerLogin);
    connect(Commander::instance(), &Commander::loggedout, this,
            &WelcomeWidget::onAuthorizationManagerLogout);
    connect(ui->loginPushButton, &QPushButton::clicked, this,
            &WelcomeWidget::onLoginPushButtonClicked);
    connect(ui->logoutPushButton, &QPushButton::clicked, this,
            &WelcomeWidget::onLogoutPushButtonClicked);
    connect(ui->registerPushButton, &QPushButton::clicked, this,
            &WelcomeWidget::onRegisterPushButtonClicked);
}

WelcomeWidget::~WelcomeWidget() { delete ui; }

void WelcomeWidget::onLoginPushButtonClicked() {
    LoginDialog *loginDialog = new LoginDialog(this);
    loginDialog->open();
}

void WelcomeWidget::onRegisterPushButtonClicked() {
    RegisterDialog *registerDialog = new RegisterDialog(this);
    registerDialog->open();
}

void WelcomeWidget::onLogoutPushButtonClicked() {
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Are you sure to logout?", "Your data will be saved on the cloud.");
    if (reply == QMessageBox::Yes) {
        tryToLogout();
    } else {
        qDebug() << Q_FUNC_INFO << "no";
    }
}

void WelcomeWidget::tryToLogout() {
    ui->logoutPushButton->setEnabled(false);
    Commander::instance()->synchronous();
    QTimer::singleShot(50, this, [=]() {
        TcpLogoutClient *logoutClient = new TcpLogoutClient(this);
        connect(logoutClient, &TcpLocalClient::readyRead, this,
                &WelcomeWidget::onLogoutClientReadyRead);
        logoutClient->sendAsync();
        qDebug() << Q_FUNC_INFO << "yes";
        connect(logoutClient, &TcpLogoutClient::timedOut, this, [=]() {
            qDebug() << Q_FUNC_INFO << "timeout";
            ui->logoutPushButton->setEnabled(true);
        });
    });
}

void WelcomeWidget::onLogoutClientReadyRead(const TcpResponse &response) {
    qDebug() << Q_FUNC_INFO << "response fetched:" << response.toJson();
    if (response.success()) {
        qDebug() << Q_FUNC_INFO << "success";
        Commander::instance()->logout();
        QTimer::singleShot(50, this, [=]() { emit aboutToLogout(); });
    } else {
        qDebug() << Q_FUNC_INFO << "failed";
        ui->logoutPushButton->setEnabled(true);
    }
}

void WelcomeWidget::onAuthorizationManagerLogin() {
    ui->tipLabel->setText("You have been authorized to use this application. You "
                          "can also logout if you want to quit.");
    ui->statusLabel->setText("Status: already login");

    ui->loginPushButton->setEnabled(false);
    ui->registerPushButton->setEnabled(false);
    ui->logoutPushButton->setEnabled(true);
}

void WelcomeWidget::onAuthorizationManagerLogout() {
    ui->tipLabel->setText("You can login if you already have an account. "
                          "Otherwise you should register first.");
    ui->statusLabel->setText("Status: not login");

    ui->loginPushButton->setEnabled(true);
    ui->registerPushButton->setEnabled(true);
    ui->logoutPushButton->setEnabled(false);
}
