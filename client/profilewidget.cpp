#include "profilewidget.h"
#include "commander.h"
#include "passwordresetdialog.h"
#include "tcpuserclient.h"
#include "ui_profilewidget.h"
#include "usernamealterdialog.h"
#include <QPixmap>

ProfileWidget::ProfileWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ProfileWidget) {
    ui->setupUi(this);
    connect(Commander::instance(), &Commander::privateUpdated, this,
            &ProfileWidget::update);
    connect(Commander::instance(), &Commander::loggedout, this,
            &ProfileWidget::clear);
    connect(ui->usernameAlterPushButton, &QPushButton::clicked, this,
            &ProfileWidget::onUsernameAlterPushButtonClicked);
    connect(ui->passwordResetPushButton, &QPushButton::clicked, this,
            &ProfileWidget::onPasswordResetPushButtonClicked);
}

ProfileWidget::~ProfileWidget() { delete ui; }

void ProfileWidget::update() {
    TcpUserClient *userClient = new TcpUserClient(this);
    connect(userClient, &TcpLocalClient::readyRead, this,
            &ProfileWidget::onUserClientReadyRead);
    userClient->sendAsync();
}

void ProfileWidget::onUserClientReadyRead(const TcpResponse &response) {
    qDebug() << Q_FUNC_INFO << response.toJson();
    if (response.success()) {
        QJsonObject body = response.body();
        User user = User::fromJson(body["user"].toObject());
        setUser(user);
        ui->usernameAlterPushButton->setEnabled(true);
        ui->passwordResetPushButton->setEnabled(true);
    }
}

void ProfileWidget::clear() {
    // ui->avatarLabel->clear();
    ui->usernameLineEdit->clear();
    ui->usernameAlterPushButton->setEnabled(false);
    ui->passwordResetPushButton->setEnabled(false);
}

void ProfileWidget::onUsernameAlterPushButtonClicked() {
    qDebug() << Q_FUNC_INFO;
    UsernameAlterDialog *dialog = new UsernameAlterDialog(this);
    dialog->setOldUsername(ui->usernameLineEdit->text());
    connect(dialog, &UsernameAlterDialog::altered, this, &ProfileWidget::update);
    dialog->open();
}

void ProfileWidget::onPasswordResetPushButtonClicked() {
    qDebug() << Q_FUNC_INFO;
    PasswordResetDialog *dialog = new PasswordResetDialog(this);
    connect(dialog, &PasswordResetDialog::reseted, this, &ProfileWidget::update);
    dialog->open();
}

void ProfileWidget::setUser(const User &user) {
    // setUserAvatar(user.avatarUrl());
    setUserName(user.username());
}

// void ProfileWidget::setUserAvatar(const QUrl &avatarUrl) {
//     QPixmap pixmap;
//     if (!pixmap.load(avatarUrl.toString())) {
//         ui->avatarLabel->setText("image");
//         qDebug() << Q_FUNC_INFO << "failed to load image" <<
//         avatarUrl.toString();
//     } else {
//         ui->avatarLabel->setPixmap(pixmap);
//     }
// }

void ProfileWidget::setUserName(const QString &username) {
    ui->usernameLineEdit->setText(username);
}
