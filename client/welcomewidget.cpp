#include "welcomewidget.h"
#include "commander.h"
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
            &WelcomeWidget::onCommanderLogin);
    connect(Commander::instance(), &Commander::loggedout, this,
            &WelcomeWidget::onCommanderLogout);
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
    }
}

void WelcomeWidget::tryToLogout() {
    QMetaObject::invokeMethod(this, [=](){
        ui->logoutPushButton->setEnabled(false);
        Commander::instance()->synchronous();
        QTimer::singleShot(50, this, [=]() {
            TcpLogoutClient *logoutClient = new TcpLogoutClient(this);
            connect(logoutClient, &TcpLocalClient::readyRead, this,
                    &WelcomeWidget::onLogoutClientReadyRead);
            connect(logoutClient, &TcpLogoutClient::timeout, this, [=]() {
                QMessageBox::critical(this, "Logout failed!", "Connection timeout.");
                ui->logoutPushButton->setEnabled(true);
            });
            logoutClient->sendAsync();
        });
    }, Qt::QueuedConnection);
}

void WelcomeWidget::onLogoutClientReadyRead(const TcpResponse &response) {
    QMetaObject::invokeMethod(this, [=]() {
        if (response.success()) {
            Commander::instance()->logout();
            QTimer::singleShot(50, this, [=]() { emit aboutToLogout(); });
        } else {
            QMessageBox::critical(this, "Logout failed!",
                                  "You can refresh the page and try again.");
            ui->logoutPushButton->setEnabled(true);
        }
    }, Qt::QueuedConnection);
}

void WelcomeWidget::onCommanderLogin() {
    ui->tipLabel->setText("You have been authorized to use this application. You "
                          "can also logout if you want to quit.");
    ui->statusLabel->setText("Status: Already Login");
    ui->loginPushButton->setEnabled(false);
    ui->registerPushButton->setEnabled(false);
    ui->logoutPushButton->setEnabled(true);
}

void WelcomeWidget::onCommanderLogout() {
    ui->tipLabel->setText("You can login if you already have an account. "
                          "Otherwise you should register first.");
    ui->statusLabel->setText("Status: Not Login");
    ui->loginPushButton->setEnabled(true);
    ui->registerPushButton->setEnabled(true);
    ui->logoutPushButton->setEnabled(false);
}
