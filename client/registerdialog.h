#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include "tcpclient.h"
#include "user.h"
#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();
    void setClient(My::TcpClient *client);
    void setUser(My::User *user);

private slots:
    void on_pushButtonConfirm_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::RegisterDialog *ui;
    My::TcpClient *client;
    My::User *user;
};

#endif // REGISTERDIALOG_H
