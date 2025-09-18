#ifndef USERCENTERWIDGET_H
#define USERCENTERWIDGET_H

#include "tcpclient.h"
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
    void refresh(int userId);

signals:
    void gotUserId(int userId);

private slots:
    void on_pushButtonLogin_clicked();
    void on_pushButtonRegister_clicked();
    void on_pushButtonLogout_clicked();

private:
    Ui::UserCenterWidget *ui;
    My::TcpClient *client;
};

#endif // USERCENTERWIDGET_H
