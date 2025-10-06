#include "orderwidget.h"
#include "tcporderclient.h"
#include "ui_orderwidget.h"
#include "authorizationmanager.h"

OrderWidget::OrderWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::OrderWidget) {
    ui->setupUi(this);
    connect(AuthorizationManager::instance(), &AuthorizationManager::updated,
            this, &OrderWidget::update);
}

OrderWidget::~OrderWidget() { delete ui; }

void OrderWidget::update() {
    TcpOrderClient *orderClient = new TcpOrderClient(this);
    connect(orderClient, &TcpOrderClient::readyRead, this,
            &OrderWidget::onOrderClientReadyRead);
    orderClient->sendAsync();
}

void OrderWidget::onOrderClientReadyRead(const TcpResponse &response) {
    qDebug() << Q_FUNC_INFO << response.toJson();
}
