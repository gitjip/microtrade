#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include "tcpresponse.h"
#include <QWidget>

namespace Ui {
class WelcomeWidget;
}

class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWidget(QWidget *parent = nullptr);
    ~WelcomeWidget();

signals:
    void aboutToLogout();

public slots:
    void tryToLogout();

private slots:
    void onLoginPushButtonClicked();
    void onRegisterPushButtonClicked();
    void onLogoutPushButtonClicked();
    void onLogoutClientReadyRead(const TcpResponse &response);
    void onAuthorizationManagerLogin();
    void onAuthorizationManagerLogout();

private:
    Ui::WelcomeWidget *ui;
};

#endif // WELCOMEWIDGET_H
