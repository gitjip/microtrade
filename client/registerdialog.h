#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include "tcpresponse.h"
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

public slots:
    void accept() override;
    void onReadyRead(const TcpResponse &response);

private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
