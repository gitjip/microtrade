#include "serverwidget.h"
#include "configure.h"
#include "tcpserver.h"
#include "tcpserverlocaldistributor.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ServerWidget) {
    ui->setupUi(this);
    TcpServerLocalDistributor *distributor = new TcpServerLocalDistributor(this);
    // qDebug() << "ServerWidget::ServerWidget"
    //          << QThreadPool::globalInstance()->maxThreadCount();
    TcpServer::instance(distributor)
        ->listen(QHostAddress(Configure::instance()->hostAddress()),
                 Configure::instance()->port());
}

ServerWidget::~ServerWidget() { delete ui; }
