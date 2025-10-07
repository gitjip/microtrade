#include "productdialog.h"
#include "commander.h"
#include "product.h"
#include "tcpaddtocartclient.h"
#include "tcpproductclient.h"
#include "ui_productdialog.h"

ProductDialog::ProductDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::ProductDialog) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->infoTableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    connect(Commander::instance(), &Commander::privateUpdated, this,
            &ProductDialog::update);
    connect(ui->addToCartPushButton, &QPushButton::clicked, this,
            &ProductDialog::onAddToCartPushButtonClicked);
}

ProductDialog::~ProductDialog() { delete ui; }

void ProductDialog::setProductId(qint64 productId) {
    m_productId = productId;
    qDebug() << Q_FUNC_INFO << productId;
    // QTableWidgetItem *item = new QTableWidgetItem(QString::number(productId));
    // ui->tableWidget->setItem(int(RowName::Id), 0, item);
    ui->infoTableWidget->horizontalHeaderItem(0)->setText(QString("product-id:  %1").arg(productId));
}

// void ProductDialog::setRow(int row) {
//     QTableWidgetItem *item = new QTableWidgetItem(QString::number(row + 1));
//     ui->tableWidget->setItem(int(RowName::Row), 0, item);
// }

void ProductDialog::update() {
    TcpProductClient *productClient = new TcpProductClient(this);
    productClient->sendAsync(m_productId);
    connect(productClient, &TcpProductClient::readyRead, this,
            &ProductDialog::onProductClientReadyRead);
}

void ProductDialog::setImage(const QUrl &imageUrl) {
    QTableWidgetItem *item = nullptr;
    QIcon icon(":" + imageUrl.path());
    if (icon.isNull()) {
        item = new QTableWidgetItem("image");
        qDebug() << Q_FUNC_INFO << "failed to load image" << imageUrl.path();
    } else {
        item = new QTableWidgetItem(icon, "");
    }
    ui->infoTableWidget->verticalHeader()->resizeSection(int(InfoRowName::Image), 80);
    ui->infoTableWidget->setItem(int(InfoRowName::Image), 0, item);
}

void ProductDialog::setName(const QString &name) {
    QTableWidgetItem *item = new QTableWidgetItem(name);
    ui->infoTableWidget->setItem(int(InfoRowName::Name), 0, item);
}

void ProductDialog::setPrice(double price) {
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(price));
    ui->infoTableWidget->setItem(int(InfoRowName::Price), 0, item);
}

void ProductDialog::setStock(qint64 stock) {
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(stock));
    ui->infoTableWidget->setItem(int(InfoRowName::Stock), 0, item);
}

void ProductDialog::setDescription(const QString &description) {
    QTableWidgetItem *item = new QTableWidgetItem(description);
    ui->infoTableWidget->setItem(int(InfoRowName::Description), 0, item);
}

void ProductDialog::onAddToCartPushButtonClicked() {
    qDebug() << Q_FUNC_INFO;
    Commander::instance()->synchronous();
    TcpAddToCartClient *addToCartClient = new TcpAddToCartClient(this);
    connect(addToCartClient, &TcpProductClient::readyRead, this,
            &ProductDialog::onAddToCartClientReadyRead);
    addToCartClient->sendAsync(m_productId);
}

void ProductDialog::onProductClientReadyRead(const TcpResponse &request) {
    qDebug() << Q_FUNC_INFO << "response:" << request.toJson();
    if (request.success()) {
        QJsonObject responseBody = request.body();
        Product product = Product::fromJson(responseBody["product"].toObject());
        setImage(product.imageUrl());
        setName(product.name());
        setPrice(product.price());
        setStock(product.stock());
        setDescription(product.description());
    }
}

void ProductDialog::onAddToCartClientReadyRead(const TcpResponse &response) {
    qDebug() << Q_FUNC_INFO << "response:" << response.toJson();
    if (response.success()) {
        Commander::instance()->privateUpdate();
        emit addedToCart();
    }
}
