#include "addtocartdialog.h"
#include "product.h"
#include "tcpproductclient.h"
#include "ui_addtocartdialog.h"
#include "tcpaddtocartclient.h"

AddToCartDialog::AddToCartDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddToCartDialog) {
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);

    connect(ui->payPushButton, &QPushButton::clicked, this, &AddToCartDialog::addToCart);
}

AddToCartDialog::~AddToCartDialog() { delete ui; }

void AddToCartDialog::setProductId(qint64 productId) {
    m_productId = productId;
    qDebug() << "PaymentDialog::setProductId:" << productId;
}

void AddToCartDialog::setRow(int row){
    ui->tableWidget->setItem(int(RowName::Row), 0,
                             new QTableWidgetItem(QString::number(row + 1)));
}

void AddToCartDialog::update() {
    TcpProductClient *productClient = new TcpProductClient(this);
    productClient->sendAsync(m_productId);
    connect(productClient, &TcpProductClient::readyRead, this, &AddToCartDialog::tryUpdate);
}

void AddToCartDialog::setImage(const QUrl &imageUrl) {
    QPixmap pixmap;
    if (!pixmap.load(imageUrl.toString())) {
        ui->tableWidget->setItem(int(RowName::Image), 0,
                                 new QTableWidgetItem("image"));
        qDebug() << "PaymentDialog::setImage:" << "failed to load image"
                 << imageUrl.toString();
    } else {
        ui->tableWidget->setItem(int(RowName::Image), 0,
                                 new QTableWidgetItem(pixmap, ""));
    }
}

void AddToCartDialog::setName(const QString &name) {
    ui->tableWidget->setItem(int(RowName::Name), 0, new QTableWidgetItem(name));
}

void AddToCartDialog::setPrice(double price) {
    ui->tableWidget->setItem(int(RowName::Price), 0, new QTableWidgetItem(QString::number(price)));
}

void AddToCartDialog::setStock(qint64 stock) {
    ui->tableWidget->setItem(int(RowName::Stock), 0, new QTableWidgetItem(QString::number(stock)));
}

void AddToCartDialog::setDescription(const QString &description) {
    ui->tableWidget->setItem(int(RowName::Description), 0,
                             new QTableWidgetItem(description));
}

void AddToCartDialog::addToCart()
{
    qDebug()<<"PaymentDialog::on_payPushButton_clicked";
    TcpAddToCartClient *paymentClient = new TcpAddToCartClient(this);
    paymentClient->sendAsync(m_productId);
    connect(paymentClient, &TcpProductClient::readyRead, this,
            &AddToCartDialog::tryAddToCart);
}

void AddToCartDialog::tryUpdate(const TcpResponse &request){
    qDebug() << "PaymentDialog::update:" << "response fetched:"
             << request.toJson();
    if (request.success()) {
        QJsonObject responseBody = request.body();
        Product product = Product::fromJson(responseBody["product"].toObject());
        setImage(product.imageUrl());
        setName(product.name());
        setPrice(product.price());
        setStock(product.stock());
        setDescription(product.description());
    } else {
        qDebug() << "PaymentDialog::update:"
                 << TcpResponse::statusTypeToString(
                        request.statusType())
                 << request.statusDetail();
    }
}

void AddToCartDialog::tryAddToCart(const TcpResponse &response){
    qDebug() << "PaymentDialog::tryAddToCart:" << "response fetched:"
             << response.toJson();
    if (response.success()) {
        // QJsonObject responseBody = response.body();
        // Product product = Product::fromJson(responseBody["product"].toObject());
        // setImage(product.imageUrl());
        // setName(product.name());
        // setPrice(product.price());
        // setStock(product.stock());
        // setDescription(product.description());
        emit paid();
    } else {
        qDebug() << "PaymentDialog::tryAddToCart:" << "error:"
                 << TcpResponse::statusTypeToString(
                        response.statusType())
                 << response.statusDetail();
    }
}
