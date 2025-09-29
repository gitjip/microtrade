#include "mainwindow.h"
#include "ui_mainwindow.h"
// #include "authorizationmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connect(AuthorizationManager::instance(), &AuthorizationManager::loggedin, this, [=](){
    //     ui->cartTab->setEnabled(true) ;
    //     ui->notificationTab->setEnabled(true);
    //     ui->orderTab->setEnabled(true);
    //     ui->profileTab->setEnabled(true);
    //     ui->shopTab->setEnabled(true);
    // });
    // connect(AuthorizationManager::instance(), &AuthorizationManager::loggedout, this, [=](){
    //     ui->cartTab->setEnabled(false);
    //     ui->notificationTab->setEnabled(false);
    //     ui->orderTab->setEnabled(false);
    //     ui->profileTab->setEnabled(false);
    //     ui->shopTab->setEnabled(false);
    // });
}

MainWindow::~MainWindow()
{
    delete ui;
}
