#ifndef USERNAMEALTERDIALOG_H
#define USERNAMEALTERDIALOG_H

#include "tcpresponse.h"
#include <QDialog>

namespace Ui {
class UsernameAlterDialog;
}

class UsernameAlterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UsernameAlterDialog(QWidget *parent = nullptr);
    ~UsernameAlterDialog();
    void setOldUsername(const QString &username);

signals:
    void altered();

public slots:
    void accept() override;

private slots:
    void onUsernameAlterClientReadyRead(const TcpResponse &response);

private:
    Ui::UsernameAlterDialog *ui;
};

#endif // USERNAMEALTERDIALOG_H
