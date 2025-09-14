#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tcpclient.h"
#include "user.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onGotUser(My::User *user);

private:
    Ui::MainWindow *ui;
    My::TcpClient *client;
    My::User *user;
};
#endif // MAINWINDOW_H
