#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::closeEvent(QCloseEvent *e)
{
    e->accept();
    emit closed();
}

void LoginWindow::on_pushButton_login_clicked()
{

}

void LoginWindow::on_pushButton_cancel_clicked()
{
    close();
}

