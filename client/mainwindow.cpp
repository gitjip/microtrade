#include "mainwindow.h"
#include "commander.h"
#include "ui_mainwindow.h"
#include <QImageReader>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    Commander::instance()->publicUpdate();
    connect(ui->actionPublicRefresh, &QAction::triggered, this, [=]() {
        qDebug() << Q_FUNC_INFO << "QAction::triggered:";
        Commander::instance()->publicUpdate();
    });
    connect(ui->actionPrivateRefresh, &QAction::triggered, this, [=]() {
        qDebug() << Q_FUNC_INFO << "QAction::triggered:";
        Commander::instance()->privateUpdate();
    });
    connect(ui->actionSync, &QAction::triggered, this, [=]() {
        qDebug() << Q_FUNC_INFO << "QAction::triggered:";
        Commander::instance()->synchronous();
    });
    QList<QByteArray> formats = QImageReader::supportedImageFormats();
    qDebug() << formats;
}

MainWindow::~MainWindow() { delete ui; }
