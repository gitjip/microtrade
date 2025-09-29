#include "welcomewidget.h"
#include "logindialog.h"
#include "registerdialog.h"
#include "ui_welcomewidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::WelcomeWidget) {
    ui->setupUi(this);
}

WelcomeWidget::~WelcomeWidget() { delete ui; }

void WelcomeWidget::on_loginPushButton_clicked() {
    LoginDialog *loginDialog = new LoginDialog(this);
    loginDialog->open();
    connect(loginDialog, &LoginDialog::accepted, this, [=]() {
        // qDebug()
        //     << "WelcomeWidget::on_loginPushButton_clicked: loginDialog accepted";
    });
}

void WelcomeWidget::on_registerPushButton_clicked() {
    RegisterDialog *registerDialog = new RegisterDialog(this);
    registerDialog->open();
    connect(registerDialog, &RegisterDialog::accepted, this, [=]() {
        // qDebug() << "WelcomeWidget::on_registerPushButton_clicked: registerDialog "
        //             "accepted";
    });
}

void WelcomeWidget::on_logoutPushButton_clicked() {}
