#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tcpclient.h"
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
    void onGotUserId(int userId);

private:
    Ui::MainWindow *ui;
    My::TcpClient *client;
    int userId;
};
#endif // MAINWINDOW_H
