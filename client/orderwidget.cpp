#include "orderwidget.h"
#include "commander.h"
#include "order.h"
#include "orderitem.h"
#include "productdialog.h"
#include "tcporderclient.h"
#include "ui_orderwidget.h"
#include <QJsonArray>
#include <QMessageBox>

OrderWidget::OrderWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::OrderWidget), currentOrderItem(nullptr) { 
    ui->setupUi(this);
    initFrontEnd();
    connect(Commander::instance(), &Commander::privateUpdated, this, 
            &OrderWidget::update);
    connect(Commander::instance(), &Commander::loggedout, this, 
            &OrderWidget::clear);
    connect(ui->treeWidget, &QTreeWidget::itemDoubleClicked, this, 
            &OrderWidget::onTreeWidgetItemDoubleClicked);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, &QTreeWidget::customContextMenuRequested, this, 
            &OrderWidget::onTreeWidgetCustomContextMenuRequested);
}

OrderWidget::~OrderWidget() { delete ui; }

void OrderWidget::update() {
    TcpOrderClient *orderClient = new TcpOrderClient(this);
    connect(orderClient, &TcpOrderClient::readyRead, this,
            &OrderWidget::onOrderClientReadyRead);
    orderClient->sendAsync();
}

void OrderWidget::onOrderClientReadyRead(const TcpResponse &response) {
    QMetaObject::invokeMethod(
        this,
        [=]() {
            qDebug() << Q_FUNC_INFO << response.toJson();
            if (response.success()) {
                productIdMap.clear();
                orderIdMap.clear();
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
                    orderIdMap[orderWidgetItem] = order.id();
                    
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
                        productIdMap[orderItemWidgetItem] = orderItem.productId();
                    }
                }
                ui->treeWidget->expandAll();
            }
        },
        Qt::QueuedConnection);
}

void OrderWidget::onTreeWidgetCustomContextMenuRequested(const QPoint &pos) {
    QMetaObject::invokeMethod(
        this,
        [=]() {
            qDebug() << Q_FUNC_INFO;
            QTreeWidgetItem *item = ui->treeWidget->itemAt(pos);
            if (!item || item->parent()) {
                return;
            }
            QString statusText = item->text(int(OrderColomn::Status));
            if (!statusText.contains("pending") && !statusText.contains("accepted")) {
                return;
            }
            qDebug() << Q_FUNC_INFO << 2;
            currentOrderItem = item;
            QMenu menu(this);
            QAction *cancelOrderAction = menu.addAction("cancel order");
            connect(cancelOrderAction, &QAction::triggered, this, &OrderWidget::onCancelOrderTriggered);
            menu.exec(ui->treeWidget->mapToGlobal(pos));
        },
        Qt::QueuedConnection);
}

void OrderWidget::onCancelOrderTriggered() {
    QMetaObject::invokeMethod(
        this,
        [=]() {
            qDebug() << Q_FUNC_INFO;
            if (!currentOrderItem) {
                return;
            }
            QMessageBox::StandardButton reply = QMessageBox::question(
                this,
                "Cancel order",
                "Are you sure to cancel the order?",
                QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                qint64 orderId = orderIdMap[currentOrderItem];
                TcpCancelOrderClient *cancelOrderClient = new TcpCancelOrderClient(this);
                connect(cancelOrderClient, &TcpCancelOrderClient::readyRead, this, 
                        &OrderWidget::onCancelOrderClientReadyRead);
                cancelOrderClient->sendAsync(orderId);
            }
        },
        Qt::QueuedConnection);
}

void OrderWidget::onCancelOrderClientReadyRead(const TcpResponse &response) {
    QMetaObject::invokeMethod(
        this,
        [=]() {
            qDebug() << Q_FUNC_INFO << response.toJson();
            if (response.success()) {
                QMessageBox::information(this, "Success", "The order has been cancelled successfully");
                update();
            } else {
                QMessageBox::critical(this, "Error", "The order failed to be cancelled\n" + response.statusDetail());
            }
        },
        Qt::QueuedConnection);
}

void OrderWidget::onTreeWidgetItemDoubleClicked(QTreeWidgetItem *item, int) {
    if (item->parent()) {
        ProductDialog *dialog = new ProductDialog(this);
        dialog->setProductId(productIdMap[item]);
        dialog->update();
        dialog->show();
    }
}

void OrderWidget::clear() { ui->treeWidget->clear(); }

void OrderWidget::initFrontEnd() {
    // set color
    QPalette systemPalette = QApplication::palette();
    ui->treeWidget->setPalette(systemPalette);
    ui->treeWidget->setAlternatingRowColors(true);
    QHeaderView *header = ui->treeWidget->header();
    header->setPalette(systemPalette);
    ui->treeWidget->setAutoFillBackground(true);
    header->setAutoFillBackground(true);
}
