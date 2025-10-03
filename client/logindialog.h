#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "tcpresponse.h"
#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void accept() override;
    void login(const TcpResponse &response);

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
