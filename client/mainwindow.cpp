#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "registerwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("welcome - " + QString(PRODUCT));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    LoginWindow *loginWindow = new LoginWindow;
    loginWindow->setGeometry(geometry());
    hide();
    loginWindow->show();
    connect(loginWindow, &LoginWindow::closed, this, [=](){
        delete loginWindow;
        show();
    });
}


void MainWindow::on_pushButton_register_clicked()
{
    RegisterWindow *registerWindow = new RegisterWindow;
    registerWindow->setGeometry(geometry());
    hide();
    registerWindow->show();
    connect(registerWindow, &RegisterWindow::closed, this, [=](){
        delete registerWindow;
        show();
    });
}


void MainWindow::on_pushButton_quit_clicked()
{
    close();
}

