#include "cartwidget.h"
#include "authorizationmanager.h"
#include "cartitem.h"
#include "tcpcartproductlistclient.h"
#include "tcpcartsyncclient.h"
#include "tcppaymentclient.h"
#include "ui_cartwidget.h"
#include <QJsonArray>
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
    ui->tableWidget->setColumnWidth(int(ColomnName::Image), 80);
    connect(AuthorizationManager::instance(), &AuthorizationManager::updated,
            this, &CartWidget::update);
    connect(ui->payPushButton, &QPushButton::clicked, this,
            &CartWidget::onPayPushButtonClicked);
}

CartWidget::~CartWidget() { delete ui; }

void CartWidget::update() {
    TcpCartProductListClient *cartProductListClient =
        new TcpCartProductListClient(this);
    connect(cartProductListClient, &TcpLocalClient::readyRead, this,
            &CartWidget::onCartProductListClientReadyRead);
    cartProductListClient->sendAsync();
}

void CartWidget::onCartProductListClientReadyRead(const TcpResponse &response) {
    qDebug() << Q_FUNC_INFO << "response:" << response.toJson();
    if (response.success()) {
        QJsonObject body = response.body();
        QJsonArray productQuantityJsonArray = body["productQuantityMap"].toArray();
        ui->tableWidget->setRowCount(productQuantityJsonArray.count());
        for (qsizetype i = 0; i < productQuantityJsonArray.count(); ++i) {
            QJsonObject productQuantityPair = productQuantityJsonArray[i].toObject();
            Product product =
                Product::fromJson(productQuantityPair["product"].toObject());
            qint64 quantity = productQuantityPair["quantity"].toInteger();
            setProduct(i, product, quantity);
        }
    }
}

void CartWidget::onPayPushButtonClicked() {
    qDebug() << Q_FUNC_INFO;
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
    connect(cartSyncClient, &TcpLocalClient::readyRead, this,
            &CartWidget::sendPaymentRequest);
    cartSyncClient->sendAsync(cartItemList);
}

void CartWidget::onCartSyncClientReadyRead(const TcpResponse &response) {
    qDebug() << Q_FUNC_INFO << response.toJson();
    AuthorizationManager::instance()->update();
}

void CartWidget::sendPaymentRequest(const TcpResponse &) {
    TcpPaymentClient *paymentClient = new TcpPaymentClient(this);
    connect(paymentClient, &TcpLocalClient::readyRead, this,
            &CartWidget::onPaymentClientReadyRead);
    paymentClient->sendAsync();
}

void CartWidget::onPaymentClientReadyRead(const TcpResponse &response) {
    qDebug() << Q_FUNC_INFO << response.toJson();
    AuthorizationManager::instance()->update();
}

void CartWidget::setProduct(int row, const Product &product, qint64 quantity) {
    setProductId(row, product.id());
    setImage(row, product.imageUrl());
    setName(row, product.name());
    setPrice(row, product.price());
    setStock(row, product.stock());
    setQuantity(row, quantity);
}

void CartWidget::setProductId(int row, qint64 productId) {
    qDebug() << Q_FUNC_INFO << productId;
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(productId));
    ui->tableWidget->setItem(row, int(ColomnName::Id), item);
}

void CartWidget::setImage(int row, const QUrl &imageUrl) {
    QPixmap pixmap;
    QTableWidgetItem *item = nullptr;
    if (!pixmap.load(imageUrl.toString())) {
        item = new QTableWidgetItem("image");
        qDebug() << Q_FUNC_INFO << "failed to load image" << imageUrl.toString();
    } else {
        item = new QTableWidgetItem(pixmap, "");
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
    if (!ui->tableWidget->cellWidget(row, int(ColomnName::Quantity))) {
        QSpinBox *spinBox = new QSpinBox;
        ui->tableWidget->setCellWidget(row, int(ColomnName::Quantity), spinBox);
    } else {
        QSpinBox *spinBox = qobject_cast<QSpinBox *>(ui->tableWidget->cellWidget(row, int(ColomnName::Quantity)));
        spinBox->setValue(quantity);
    }
}
