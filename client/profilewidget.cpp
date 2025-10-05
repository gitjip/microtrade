#include "profilewidget.h"
#include "authorizationmanager.h"
#include "tcpuserclient.h"
#include "ui_profilewidget.h"
#include <QPixmap>

ProfileWidget::ProfileWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ProfileWidget) {
    ui->setupUi(this);
    connect(AuthorizationManager::instance(), &AuthorizationManager::updated,
            this, &ProfileWidget::update);
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
    }
}

void ProfileWidget::setUser(const User &user) {
    setUserAvatar(user.avatarUrl());
    setUserName(user.username());
}

void ProfileWidget::setUserAvatar(const QUrl &avatarUrl) {
    QPixmap pixmap;
    if (!pixmap.load(avatarUrl.toString())) {
        ui->avatarLabel->setText("image");
        qDebug() << Q_FUNC_INFO << "failed to load image" << avatarUrl.toString();
    } else {
        ui->avatarLabel->setPixmap(pixmap);
    }
}

void ProfileWidget::setUserName(const QString &username) {
    ui->usernameLineEdit->setText(username);
}
