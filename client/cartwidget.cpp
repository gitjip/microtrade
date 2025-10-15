#include "cartwidget.h"
#include "cartitem.h"
#include "commander.h"
#include "productdialog.h"
#include "tcpcartproductlistclient.h"
#include "tcpcartsyncclient.h"
#include "tcppaymentclient.h"
#include "tcpremovefromcartclient.h"
#include "ui_cartwidget.h"
#include <QJsonArray>
#include <QLabel>
#include <QMessageBox>
#include <QSpinBox>

CartWidget::CartWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::CartWidget) {
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        int(ColomnName::Id), QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        int(ColomnName::Image), QHeaderView::Fixed);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        int(ColomnName::Name), QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        int(ColomnName::Price), QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        int(ColomnName::Stock), QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        int(ColomnName::Quantity), QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        int(ColomnName::Remove), QHeaderView::ResizeToContents);
    ui->tableWidget->setColumnWidth(int(ColomnName::Image), 80);
    connect(Commander::instance(), &Commander::privateUpdated, this,
            &CartWidget::update);
    connect(Commander::instance(), &Commander::synchronoused, this,
            &CartWidget::onCommanderSynchronoused);
    connect(Commander::instance(), &Commander::loggedout, this,
            &CartWidget::clear);
    connect(ui->payPushButton, &QPushButton::clicked, this,
            &CartWidget::onPayPushButtonClicked);
    connect(ui->tableWidget, &QTableWidget::itemDoubleClicked, this,
            &CartWidget::onItemDoubleClicked);
}

CartWidget::~CartWidget() { delete ui; }

void CartWidget::update() {
    QMetaObject::invokeMethod(this, [=](){
        TcpCartProductListClient *cartProductListClient =
            new TcpCartProductListClient(this);
        connect(cartProductListClient, &TcpLocalClient::readyRead, this,
                &CartWidget::onCartProductListClientReadyRead);
        cartProductListClient->sendAsync();
    },Qt::QueuedConnection);
}

void CartWidget::onCartProductListClientReadyRead(const TcpResponse &response) {
    if (response.success()) {
        QJsonObject body = response.body();
        QJsonArray productQuantityJsonArray = body["productQuantityMap"].toArray();
        productIdList.clear();
        ui->tableWidget->setRowCount(productQuantityJsonArray.count());
        for (qsizetype i = 0; i < productQuantityJsonArray.count(); ++i) {
            QJsonObject productQuantityPair = productQuantityJsonArray[i].toObject();
            Product product =
                Product::fromJson(productQuantityPair["product"].toObject());
            qint64 quantity = productQuantityPair["quantity"].toInteger();
            setProduct(i, product, quantity);
            productIdList.append(product.id());
        }
    }
}

void CartWidget::onPayPushButtonClicked() {
    QMetaObject::invokeMethod(
        this,
        [=]() {
        QList<CartItem> cartItemList;
        for (qsizetype i = 0; i < ui->tableWidget->rowCount(); ++i) {
            QTableWidgetItem *idItem =
                ui->tableWidget->item(i, int(ColomnName::Id));
            QSpinBox *quantityItem = qobject_cast<QSpinBox *>(
                ui->tableWidget->cellWidget(i, int(ColomnName::Quantity)));
            cartItemList.append({-1,
                                 {},
                                 {},
                                 -1,
                                 idItem->text().toLongLong(),
                                 quantityItem->value()});
        }
        TcpCartSyncClient *cartSyncClient = new TcpCartSyncClient(this);
        connect(cartSyncClient, &TcpLocalClient::readyRead, this,
                &CartWidget::onCartSyncClientReadyRead);
        connect(cartSyncClient, &TcpLocalClient::readyRead, this,
                &CartWidget::sendPaymentRequest);
        connect(cartSyncClient, &TcpLocalClient::timeout, this, [=]() {
            QMessageBox::critical(this, "Sync cart failed!", "Connection timeout.");
        });
        cartSyncClient->sendAsync(cartItemList);
        },
        Qt::QueuedConnection);
}

void CartWidget::onCartSyncClientReadyRead(const TcpResponse &) {
    Commander::instance()->privateUpdate();
}

void CartWidget::sendPaymentRequest(const TcpResponse &) {
    QMetaObject::invokeMethod(
        this,
        [=]() {
            TcpPaymentClient *paymentClient = new TcpPaymentClient(this);
            connect(paymentClient, &TcpLocalClient::readyRead, this,
                    &CartWidget::onPaymentClientReadyRead);
            connect(paymentClient, &TcpLocalClient::timeout, this, [=]() {
                QMessageBox::critical(this, "Pay failed!", "Connection timeout.");
            });
            paymentClient->sendAsync();
        },
        Qt::QueuedConnection);
}

void CartWidget::onPaymentClientReadyRead(const TcpResponse &response) {
    QMetaObject::invokeMethod(
        this,
        [=]() {
        if (response.success()) {
            Commander::instance()->privateUpdate();
            QMessageBox::information(this, "Pay all products successfully!",
                                     "The order has been generated.");
        } else {
            if (response.statusType() == TcpResponse::StatusType::Failed) {
                QMessageBox::warning(this, "Cannot pay all!", "The order is empty.");
            } else {
                QMessageBox::critical(this, "Payment failed!",
                                      "Unknown error occurred.");
            }
        }
        },
        Qt::QueuedConnection);
}

void CartWidget::onCommanderSynchronoused() {
    QList<CartItem> cartItemList;
    for (qsizetype i = 0; i < ui->tableWidget->rowCount(); ++i) {
        QTableWidgetItem *idItem = ui->tableWidget->item(i, int(ColomnName::Id));
        QSpinBox *quantityItem = qobject_cast<QSpinBox *>(
            ui->tableWidget->cellWidget(i, int(ColomnName::Quantity)));
        cartItemList.append(
            {-1, {}, {}, -1, idItem->text().toLongLong(), quantityItem->value()});
    }
    TcpCartSyncClient *cartSyncClient = new TcpCartSyncClient(this);
    connect(cartSyncClient, &TcpLocalClient::readyRead, this,
            &CartWidget::onCartSyncClientReadyRead);
    cartSyncClient->sendAsync(cartItemList);
}

void CartWidget::onItemDoubleClicked(QTableWidgetItem *item) {
    ProductDialog *dialog = new ProductDialog(this);
    dialog->setProductId(productIdList[item->row()]);
    dialog->update();
    dialog->show();
}

void CartWidget::clear() { ui->tableWidget->setRowCount(0); }

void CartWidget::setProduct(int row, const Product &product, qint64 quantity) {
    setProductId(row, product.id());
    setImage(row, product.imageUrl());
    setName(row, product.name());
    setPrice(row, product.price());
    setStock(row, product.stock());
    setQuantity(row, quantity);
    setRemove(row, product.id());
}

void CartWidget::setProductId(int row, qint64 productId) {
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(productId));
    ui->tableWidget->setItem(row, int(ColomnName::Id), item);
}

void CartWidget::setImage(int row, const QUrl &imageUrl) {
    QTableWidgetItem *item = nullptr;
    QIcon icon(":" + imageUrl.path());
    if (icon.isNull()) {
        item = new QTableWidgetItem("image");
    } else {
        item = new QTableWidgetItem(icon, "");
    }
    ui->tableWidget->setItem(row, int(ColomnName::Image), item);
}

void CartWidget::setName(int row, const QString &productName) {
    QTableWidgetItem *item = new QTableWidgetItem(productName);
    ui->tableWidget->setItem(row, int(ColomnName::Name), item);
}

void CartWidget::setPrice(int row, double price) {
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(price));
    ui->tableWidget->setItem(row, int(ColomnName::Price), item);
}

void CartWidget::setStock(int row, qint64 stock) {
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(stock));
    ui->tableWidget->setItem(row, int(ColomnName::Stock), item);
}

void CartWidget::setQuantity(int row, qint64 quantity) {
    QSpinBox *spinBox = nullptr;
    if (!ui->tableWidget->cellWidget(row, int(ColomnName::Quantity))) {
        spinBox = new QSpinBox;
        ui->tableWidget->setCellWidget(row, int(ColomnName::Quantity), spinBox);
    } else {
        spinBox = qobject_cast<QSpinBox *>(
            ui->tableWidget->cellWidget(row, int(ColomnName::Quantity)));
    }
    spinBox->setValue(quantity);
}

void CartWidget::setRemove(int row, qint64 productId) {
    QLabel *removalLink =
        new QLabel("<a href='#' style='color: red;'>remove</a>");
    removalLink->setOpenExternalLinks(false);
    ui->tableWidget->setCellWidget(row, int(ColomnName::Remove), removalLink);
    connect(removalLink, &QLabel::linkActivated, this, [=]() {
        TcpRemoveFromCartClient *client = new TcpRemoveFromCartClient(this);
        connect(client, &TcpRemoveFromCartClient::readyRead, this,
                [=](const TcpResponse &response) {
            if (response.success()) {
                Commander::instance()->privateUpdate();
            }
        });
        client->sendAsync(productId);
    });
}
