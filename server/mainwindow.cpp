#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcplocalserver.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TcpLocalServer::instance();
}

MainWindow::~MainWindow()
{
    delete ui;
}
