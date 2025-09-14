#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), client(new My::TcpClient),
    user(nullptr) {
    ui->setupUi(this);
    setWindowTitle("Microtrade 1.0.0");
    ui->userCenterTab->setClient(client);
    connect(ui->userCenterTab, &UserCenterWidget::gotUser, this,
            &MainWindow::onGotUser);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onGotUser(My::User *user) {
    this->user = user;
    ui->userCenterTab->setUser(user);
}
