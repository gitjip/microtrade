#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), client(new My::TcpClient),
    userId(0) {
    ui->setupUi(this);
    setWindowTitle("Microtrade 1.0.0");
    ui->userCenterTab->setClient(client);
    connect(ui->userCenterTab, &UserCenterWidget::gotUserId, this,
            &MainWindow::onGotUserId);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onGotUserId(int userId) {
    this->userId = userId;
    ui->userCenterTab->setUserId(userId);
}
