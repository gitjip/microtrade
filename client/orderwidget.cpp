#include "orderwidget.h"
#include "commander.h"
#include "order.h"
#include "orderitem.h"
#include "tcporderclient.h"
#include "ui_orderwidget.h"
#include <QJsonArray>

OrderWidget::OrderWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::OrderWidget) {
    ui->setupUi(this);
    connect(Commander::instance(), &Commander::privateUpdated,
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
    if (response.success()) {
        ui->treeWidget->clear();
        QJsonObject body = response.body();
        QJsonArray orderTree = body["orderTree"].toArray();
        for (qsizetype i = 0; i < orderTree.count(); ++i) {
            QJsonObject orderPair = orderTree[i].toObject();
            Order order = Order::fromJson(orderPair["order"].toObject());
            QTreeWidgetItem *orderWidgetItem = new QTreeWidgetItem(ui->treeWidget);
            orderWidgetItem->setText(0, QString::number(order.id()));
            QJsonArray orderItemList = orderPair["orderItemList"].toArray();
            for (qsizetype j = 0; j < orderItemList.count(); ++j) {
                OrderItem orderItem = OrderItem::fromJson(orderItemList[j].toObject());
                QTreeWidgetItem *orderItemWidgetItem =
                    new QTreeWidgetItem(orderWidgetItem);
                orderItemWidgetItem->setText(0, QString::number(orderItem.id()));
            }
        }
        ui->treeWidget->expandAll();
    }
}
