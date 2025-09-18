#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "tcpclient.h"
#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    void setClient(My::TcpClient *client);

signals:
    void readySetUserId(int userId);

private slots:
    void on_pushButtonConfirm_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::LoginDialog *ui;
    My::TcpClient *client;
};

#endif // LOGINDIALOG_H
