#include "registerwindow.h"
#include "ui_registerwindow.h"

RegisterWindow::RegisterWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::closeEvent(QCloseEvent *e)
{
    e->accept();
    emit closed();
}

void RegisterWindow::on_pushButton_register_clicked()
{

}


void RegisterWindow::on_pushButton_cancel_clicked()
{
    close();
}

