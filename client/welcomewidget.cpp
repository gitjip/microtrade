#include "welcomewidget.h"
#include "authorizationmanager.h"
#include "logindialog.h"
#include "registerdialog.h"
#include "ui_welcomewidget.h"
#include <QMessageBox>

WelcomeWidget::WelcomeWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::WelcomeWidget) {
    ui->setupUi(this);
    connect(AuthorizationManager::instance(), &AuthorizationManager::loggedin,
            this, &WelcomeWidget::onLogin);
    connect(AuthorizationManager::instance(), &AuthorizationManager::loggedout,
            this, &WelcomeWidget::onLogout);
    connect(ui->loginPushButton, &QPushButton::clicked, this, &WelcomeWidget::tryLogin);
    connect(ui->logoutPushButton, &QPushButton::clicked, this, &WelcomeWidget::tryLogout);
    connect(ui->registerPushButton, &QPushButton::clicked, this, &WelcomeWidget::tryRegister);
}

WelcomeWidget::~WelcomeWidget() { delete ui; }

void WelcomeWidget::tryLogin() {
    LoginDialog *loginDialog = new LoginDialog(this);
    loginDialog->open();
}

void WelcomeWidget::tryRegister() {
    RegisterDialog *registerDialog = new RegisterDialog(this);
    registerDialog->open();
}

void WelcomeWidget::tryLogout() {
    QMessageBox::StandardButton reply =
        QMessageBox::question(this, "Are you sure to logout?",
            "Your data will be safely stored on the cloud.");
    if (reply == QMessageBox::Yes) {
        AuthorizationManager::instance()->logout();
        qDebug() << "WelcomeWidget::tryLogout:" << "yes";
    } else {
        qDebug() << "WelcomeWidget::tryLogout:" << "no";
    }
}

void WelcomeWidget::onLogin() {
    ui->tipLabel->setText("You have been authorized to use this application. You "
                          "can also logout if you want to quit.");
    ui->statusLabel->setText("Status: already login");

    ui->loginPushButton->setEnabled(false);
    ui->registerPushButton->setEnabled(false);
    ui->logoutPushButton->setEnabled(true);
}

void WelcomeWidget::onLogout() {
    ui->tipLabel->setText("You can login if you already have an account. "
                          "Otherwise you should register first.");
    ui->statusLabel->setText("Status: not login");

    ui->loginPushButton->setEnabled(true);
    ui->registerPushButton->setEnabled(true);
    ui->logoutPushButton->setEnabled(false);
}
