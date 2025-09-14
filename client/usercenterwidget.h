#ifndef USERCENTERWIDGET_H
#define USERCENTERWIDGET_H

#include "tcpclient.h"
#include "user.h"
#include <QWidget>

namespace Ui {
class UserCenterWidget;
}

class UserCenterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserCenterWidget(QWidget *parent = nullptr);
    ~UserCenterWidget();
    void setClient(My::TcpClient *client);
    void setUser(My::User *user);

signals:
    void gotUser(My::User *user);

private slots:
    void on_pushButtonLogin_clicked();

private:
    Ui::UserCenterWidget *ui;
    My::TcpClient *client;
    My::User *user;
};

#endif // USERCENTERWIDGET_H
