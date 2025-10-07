#include "shopwidget.h"
#include "commander.h"
#include "productdialog.h"
#include "tcpproductlistclient.h"
#include "ui_shopwidget.h"
#include <QJsonArray>
#include <QLabel>

ShopWidget::ShopWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ShopWidget) {
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
        int(ColomnName::View), QHeaderView::ResizeToContents);
    ui->tableWidget->setColumnWidth(int(ColomnName::Image), 80);
    connect(Commander::instance(), &Commander::publicUpdated, this,
            &ShopWidget::update);
}

ShopWidget::~ShopWidget() { delete ui; }

void ShopWidget::update() {
    TcpProductListClient *productListClient = new TcpProductListClient(this);
    productListClient->sendAsync();
    connect(productListClient, &TcpProductListClient::readyRead, this,
            &ShopWidget::onProductListClientReadyRead);
}

void ShopWidget::onProductListClientReadyRead(const TcpResponse &tcpResponse) {
    // qDebug() << Q_FUNC_INFO << "response fetched:" << tcpResponse.toJson();
    if (tcpResponse.success()) {
        QJsonObject responseBody = tcpResponse.body();
        QJsonArray productJsonArray = responseBody["productList"].toArray();
        ui->tableWidget->setRowCount(productJsonArray.count());
        for (qsizetype i = 0; i < productJsonArray.count(); ++i) {
            setProduct(i, Product::fromJson(productJsonArray[i].toObject()));
        }
    }
}

void ShopWidget::setProduct(int row, const Product &product) {
    setProductId(row, product.id());
    setImage(row, product.imageUrl());
    setName(row, product.name());
    setPrice(row, product.price());
    setStock(row, product.stock());
    setView(row, product.id());
}

void ShopWidget::setProductId(int row, qint64 productId) {
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(productId));
    ui->tableWidget->setItem(row, int(ColomnName::Id), item);
}

void ShopWidget::setImage(int row, const QUrl &imageUrl) {
    QTableWidgetItem *item = nullptr;
    QIcon icon(":" + imageUrl.path());
    qDebug() << Q_FUNC_INFO << imageUrl.path();
    if (icon.isNull()) {
        item = new QTableWidgetItem("image");
        // qDebug() << Q_FUNC_INFO << "failed to load image" << imageUrl.path();
    } else {
        item = new QTableWidgetItem(icon, "");
    }
    ui->tableWidget->setItem(row, int(ColomnName::Image), item);
}

void ShopWidget::setName(int row, const QString &productName) {
    QTableWidgetItem *item = new QTableWidgetItem(productName);
    ui->tableWidget->setItem(row, int(ColomnName::Name), item);
}

void ShopWidget::setPrice(int row, double price) {
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(price));
    ui->tableWidget->setItem(row, int(ColomnName::Price), item);
}

void ShopWidget::setStock(int row, qint64 stock) {
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(stock));
    ui->tableWidget->setItem(row, int(ColomnName::Stock), item);
}

void ShopWidget::setView(int row, qint64 productId) {
    QLabel *viewLink =
        new QLabel("<a href='#' style='color: green;'>view details</a>");
    viewLink->setOpenExternalLinks(false);
    ui->tableWidget->setCellWidget(row, int(ColomnName::View), viewLink);
    connect(viewLink, &QLabel::linkActivated, this, [=]() {
        // qDebug() << Q_FUNC_INFO << "QLabel::linkActivated";
        ProductDialog *addToCartDialog = new ProductDialog(this);
        addToCartDialog->setProductId(productId);
        // addToCartDialog->setRow(row);
        addToCartDialog->update();
        connect(addToCartDialog, &ProductDialog::addedToCart, this,
                [=]() { qDebug() << Q_FUNC_INFO << "onPaid"; });
        addToCartDialog->show();
    });
}
