#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), client(new My::TcpClient),
    userId(0) {
    ui->setupUi(this);
    setWindowTitle("Microtrade 1.0.0");
    ui->userCenterTab->setClient(client);
    connect(ui->userCenterTab, &UserCenterWidget::readySetUserId, this,
            &MainWindow::setUserId);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::refreshAll() {
    ui->userCenterTab->refresh();
}

void MainWindow::setUserId(int userId) {
    this->userId = userId;
    ui->userCenterTab->setUserId(userId);
    refreshAll();
}
