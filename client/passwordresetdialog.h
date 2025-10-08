#ifndef PASSWORDRESETDIALOG_H
#define PASSWORDRESETDIALOG_H

#include "tcpresponse.h"
#include <QDialog>

namespace Ui {
class PasswordResetDialog;
}

class PasswordResetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordResetDialog(QWidget *parent = nullptr);
    ~PasswordResetDialog();

signals:
    void reseted();

public slots:
    void accept() override;

private:
    void onPasswordUpdaterClientReadyRead(const TcpResponse &response);

private:
    Ui::PasswordResetDialog *ui;
};

#endif // PASSWORDRESETDIALOG_H
