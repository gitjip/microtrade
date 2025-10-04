#include "addtocartdialog.h"
#include "authorizationmanager.h"
#include "product.h"
#include "tcpaddtocartclient.h"
#include "tcpproductclient.h"
#include "ui_addtocartdialog.h"

AddToCartDialog::AddToCartDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddToCartDialog) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    connect(AuthorizationManager::instance(), &AuthorizationManager::updated,
            this, &AddToCartDialog::update);
    connect(ui->addToCartPushButton, &QPushButton::clicked, this,
            &AddToCartDialog::onAddToCartPushButtonClicked);
}

AddToCartDialog::~AddToCartDialog() { delete ui; }

void AddToCartDialog::setProductId(qint64 productId) {
    m_productId = productId;
    qDebug() << Q_FUNC_INFO << productId;
}

void AddToCartDialog::setRow(int row) {
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(row + 1));
    ui->tableWidget->setItem(int(RowName::Row), 0, item);
}

void AddToCartDialog::update() {
    TcpProductClient *productClient = new TcpProductClient(this);
    productClient->sendAsync(m_productId);
    connect(productClient, &TcpProductClient::readyRead, this,
            &AddToCartDialog::onProductClientReadyRead);
}

void AddToCartDialog::setImage(const QUrl &imageUrl) {
    QPixmap pixmap;
    QTableWidgetItem *item = nullptr;
    if (!pixmap.load(imageUrl.toString())) {
        item = new QTableWidgetItem("image");
        qDebug() << Q_FUNC_INFO << "failed to load image" << imageUrl.toString();
    } else {
        item = new QTableWidgetItem(pixmap, "");
    }
    ui->tableWidget->setItem(int(RowName::Image), 0, item);
}

void AddToCartDialog::setName(const QString &name) {
    QTableWidgetItem *item = new QTableWidgetItem(name);
    ui->tableWidget->setItem(int(RowName::Name), 0, item);
}

void AddToCartDialog::setPrice(double price) {
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(price));
    ui->tableWidget->setItem(int(RowName::Price), 0, item);
}

void AddToCartDialog::setStock(qint64 stock) {
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(stock));
    ui->tableWidget->setItem(int(RowName::Stock), 0, item);
}

void AddToCartDialog::setDescription(const QString &description) {
    QTableWidgetItem *item = new QTableWidgetItem(description);
    ui->tableWidget->setItem(int(RowName::Description), 0, item);
}

void AddToCartDialog::onAddToCartPushButtonClicked() {
    qDebug() << Q_FUNC_INFO;
    TcpAddToCartClient *addToCartClient = new TcpAddToCartClient(this);
    connect(addToCartClient, &TcpProductClient::readyRead, this,
            &AddToCartDialog::onAddToCartClientReadyRead);
    addToCartClient->sendAsync(m_productId);
}

void AddToCartDialog::onProductClientReadyRead(const TcpResponse &request) {
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

void AddToCartDialog::onAddToCartClientReadyRead(const TcpResponse &response) {
    qDebug() << Q_FUNC_INFO << "response:" << response.toJson();
    if (response.success()) {
        AuthorizationManager::instance()->update();
        emit addedToCart();
    }
}
