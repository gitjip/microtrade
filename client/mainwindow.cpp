#include "mainwindow.h"
#include "commander.h"
#include "ui_mainwindow.h"
#include <QCloseEvent>
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    Commander::instance()->publicUpdate();
    connect(ui->actionPublicRefresh, &QAction::triggered, Commander::instance(),
            &Commander::publicUpdate);
    connect(ui->actionPrivateRefresh, &QAction::triggered, Commander::instance(),
            &Commander::privateUpdate);
    connect(ui->actionSync, &QAction::triggered, Commander::instance(),
            &Commander::synchronous);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::closeEvent(QCloseEvent *e) {
    if (Commander::instance()->isLoggedin()) {
        e->ignore();
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Are you sure to quit?",
            "We will try to make you logout before you run away.");
        if (reply == QMessageBox::Yes) {
            ui->welcomeTab->tryToLogout();
            connect(ui->welcomeTab, &WelcomeWidget::aboutToLogout, this,
                    &MainWindow::close);
            QTimer::singleShot(1000, this, [=]() {
                qDebug() << "the server break down, cannot logout";
                qApp->exit(0);
            });
        }
    } else {
        e->accept();
    }
}
