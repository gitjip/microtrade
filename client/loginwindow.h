#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    void closeEvent(QCloseEvent *e) override;

signals:
    void closed();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
