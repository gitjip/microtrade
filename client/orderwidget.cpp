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
    
    // 设置右键菜单
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
            
            // 保存订单ID映射
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
}

void OrderWidget::onTreeWidgetCustomContextMenuRequested(const QPoint &pos) {
    QTreeWidgetItem *item = ui->treeWidget->itemAt(pos);
    if (!item || item->parent()) { // 只对订单项显示右键菜单，不对订单项显示
        return;
    }
    
    // 检查订单状态是否允许取消
    QString statusText = item->text(int(OrderColomn::Status));
    if (!statusText.contains("Pending") && !statusText.contains("Accepted")) {
        return;
    }
    
    currentOrderItem = item;
    QMenu menu(this);
    QAction *cancelOrderAction = menu.addAction("取消订单");
    connect(cancelOrderAction, &QAction::triggered, this, &OrderWidget::onCancelOrderTriggered);
    menu.exec(ui->treeWidget->mapToGlobal(pos));
}

void OrderWidget::onCancelOrderTriggered() {
    if (!currentOrderItem) {
        return;
    }
    
    // 显示确认对话框
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "取消订单",
        "确定要取消该订单吗？",
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        qint64 orderId = orderIdMap[currentOrderItem];
        TcpCancelOrderClient *cancelOrderClient = new TcpCancelOrderClient(this);
        connect(cancelOrderClient, &TcpCancelOrderClient::readyRead, this, 
                &OrderWidget::onCancelOrderClientReadyRead);
        cancelOrderClient->sendAsync(orderId);
    }
}

void OrderWidget::onCancelOrderClientReadyRead(const TcpResponse &response) {
    qDebug() << Q_FUNC_INFO << response.toJson();
    if (response.success()) {
        QMessageBox::information(this, "成功", "订单已成功取消！");
        update(); // 刷新订单列表
    } else {
        QMessageBox::critical(this, "错误", "取消订单失败！\n" + response.message());
    }
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
