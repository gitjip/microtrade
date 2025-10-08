#include "productdialog.h"
#include "commander.h"
#include "product.h"
#include "promotion.h"
#include "qjsonarray.h"
#include "tcpaddtocartclient.h"
#include "tcpproductclient.h"
#include "tcpproductpromotionlistclient.h"
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
    ui->infoTableWidget->horizontalHeaderItem(0)->setText(
        QString("product-id:  %1").arg(productId));
}

void ProductDialog::update() {
    TcpProductClient *productClient = new TcpProductClient(this);
    connect(productClient, &TcpProductClient::readyRead, this,
            &ProductDialog::onProductClientReadyRead);
    productClient->sendAsync(m_productId);
    TcpProductPromotionListClient *productPromotionListClient =
        new TcpProductPromotionListClient(this);
    connect(productPromotionListClient, &TcpProductPromotionListClient::readyRead,
            this, &ProductDialog::onTcpProductPromotionListClientReadyRead);
    productPromotionListClient->sendAsync(m_productId);
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
    ui->infoTableWidget->verticalHeader()->resizeSection(int(InfoRowName::Image),
                                                         80);
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

void ProductDialog::onTcpProductPromotionListClientReadyRead(
    const TcpResponse &response) {
    qDebug() << Q_FUNC_INFO << response.toJson();
    if (response.success()) {
        QJsonObject responseBody = response.body();
        QJsonArray promotionJsonArray = responseBody["promotionList"].toArray();
        ui->promTableWidget->setRowCount(promotionJsonArray.count());
        for (qsizetype i = 0; i < promotionJsonArray.count(); ++i) {
            Promotion promotion =
                Promotion::fromJson(promotionJsonArray[i].toObject());
            qDebug() << promotion.toJson();
            setPromId(i, promotion.id());
            setPromText(i, promotion.description());
            setPromStart(i, promotion.startAt());
            setPromEndAt(i, promotion.endAt());
        }
    }
}

void ProductDialog::setPromId(int row, qint64 id) {
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(id));
    ui->promTableWidget->setItem(row, int(PromColomnName::Id), item);
}

void ProductDialog::setPromText(int row, const QString &text) {
    QTableWidgetItem *item = new QTableWidgetItem(text);
    ui->promTableWidget->setItem(row, int(PromColomnName::Text), item);
}

void ProductDialog::setPromStart(int row, const QDateTime &startAt) {
    QTableWidgetItem *item = new QTableWidgetItem(startAt.toString());
    ui->promTableWidget->setItem(row, int(PromColomnName::Start), item);
}

void ProductDialog::setPromEndAt(int row, const QDateTime &endAt) {
    QTableWidgetItem *item = new QTableWidgetItem(endAt.toString());
    ui->promTableWidget->setItem(row, int(PromColomnName::End), item);
}
