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
    initFrontEnd();
    connect(Commander::instance(), &Commander::privateUpdated, this,
            &OrderWidget::update);
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
            orderWidgetItem->setText(int(OrderColomn::Id),
                                     QString("order/id:  %1").arg(order.id(), 0));
            orderWidgetItem->setText(
                int(OrderColomn::Cost),
                QString("cost:  %1").arg(order.cost(), 0, 'f', 2));
            orderWidgetItem->setText(
                int(OrderColomn::Status),
                QString("status:  %1").arg(Order::statusToString(order.status()), 0));
            orderWidgetItem->setText(
                int(OrderColomn::CreatedAt),
                QString("created:  %1").arg(order.createdAt().toString()));
            QJsonArray orderItemList = orderPair["orderItemList"].toArray();
            for (qsizetype j = 0; j < orderItemList.count(); ++j) {
                OrderItem orderItem = OrderItem::fromJson(orderItemList[j].toObject());
                QTreeWidgetItem *orderItemWidgetItem =
                    new QTreeWidgetItem(orderWidgetItem);
                orderItemWidgetItem->setText(
                    int(OrderItemColomn::Id),
                    QString("item/id:  %1").arg(orderItem.id(), 0));
                orderItemWidgetItem->setText(
                    int(OrderItemColomn::ProductId),
                    QString("product:  %1").arg(orderItem.productId(), 0));
                orderItemWidgetItem->setText(
                    int(OrderItemColomn::Quantity),
                    QString("quantity:  %1").arg(orderItem.quantity(), 0));
                orderItemWidgetItem->setText(
                    int(OrderItemColomn::Cost),
                    QString("cost:  %1").arg(orderItem.cost(), 0, 'f', 2));
                orderItemWidgetItem->setText(
                    int(OrderItemColomn::CreatedAt),
                    QString("created:  %1").arg(orderItem.createdAt().toString()));
            }
        }
        ui->treeWidget->expandAll();
    }
}

void OrderWidget::initFrontEnd() {
    // set color
    QPalette systemPalette = QApplication::palette();
    ui->treeWidget->setPalette(systemPalette);
    ui->treeWidget->setAlternatingRowColors(true);
    QHeaderView *header = ui->treeWidget->header();
    header->setPalette(systemPalette);
    ui->treeWidget->setAutoFillBackground(true);
    header->setAutoFillBackground(true);
    // set resize mode
    // header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    // header->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    // header->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    // header->setSectionResizeMode(3, QHeaderView::Stretch);
    // header->setSectionResizeMode(4, QHeaderView::ResizeToContents);
}
