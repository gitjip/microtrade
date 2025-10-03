#include "shopwidget.h"
#include "paymentdialog.h"
#include "tcpproductlistclient.h"
#include "ui_shopwidget.h"
#include <QJsonArray>
#include <QLabel>

ShopWidget::ShopWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ShopWidget) {
    ui->setupUi(this);

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
}

ShopWidget::~ShopWidget() { delete ui; }

void ShopWidget::update() {
    TcpProductListClient *tcpProductListClient = new TcpProductListClient(this);
    tcpProductListClient->sendAsync();
    connect(tcpProductListClient, &TcpProductListClient::readyRead, this, &ShopWidget::tryUpdate);
}

void ShopWidget::tryUpdate(const TcpResponse &tcpResponse){
    qDebug() << "ShopWidget::update:" << "response fetched:"
             << tcpResponse.toJson();
    if (tcpResponse.success()) {
        QJsonObject responseBody = tcpResponse.body();
        QJsonArray productList = responseBody["productList"].toArray();
        ui->tableWidget->setRowCount(productList.count());
        for (qsizetype i = 0; i < productList.count(); ++i) {
            setProduct(i, Product::fromJson(productList[i].toObject()));
        }
    } else {
        qDebug() << "ShopWidget::update:" << "error:"
                 << TcpResponse::statusTypeToString(
                        tcpResponse.statusType())
                 << tcpResponse.statusDetail();
    }
}

void ShopWidget::setProduct(int row, const Product &product) {
    setImage(row, product.imageUrl());
    setName(row, product.name());
    setPrice(row, product.price());
    setStock(row, product.stock());
    setView(row, product.id());
}

void ShopWidget::setImage(int row, const QUrl &imageUrl) {
    QPixmap pixmap;
    if (!pixmap.load(imageUrl.toString())) {
        ui->tableWidget->setItem(row, int(ColomnName::Image),
                                 new QTableWidgetItem("image"));
        qDebug() << "ShopWidget::addProduct:" << "failed to load image"
                 << imageUrl.toString();
    } else {
        ui->tableWidget->setItem(row, int(ColomnName::Image),
                                 new QTableWidgetItem(pixmap, ""));
    }
}

void ShopWidget::setName(int row, const QString &productName) {
    ui->tableWidget->setItem(row, int(ColomnName::Name),
                             new QTableWidgetItem(productName));
}

void ShopWidget::setPrice(int row, double price) {
    ui->tableWidget->setItem(row, int(ColomnName::Price),
                             new QTableWidgetItem(QString::number(price)));
}

void ShopWidget::setStock(int row, qint64 stock) {
    ui->tableWidget->setItem(row, int(ColomnName::Stock),
                             new QTableWidgetItem(QString::number(stock)));
}

void ShopWidget::setView(int row, qint64 productId) {
    QLabel *viewLink =
        new QLabel("<a href='#' style='color: green;'>view details</a>");
    viewLink->setOpenExternalLinks(false);
    ui->tableWidget->setCellWidget(row, int(ColomnName::View), viewLink);
    connect(viewLink, &QLabel::linkActivated, this, [=]() {
        qDebug() << "ShopWidget::addView:" << "QLabel::linkActivated";
        PaymentDialog *paymentDialog = new PaymentDialog(this);
        paymentDialog->setProductId(productId);
        paymentDialog->setRow(row);
        paymentDialog->update();
        connect(paymentDialog, &PaymentDialog::paid, this, [=]() {
            qDebug() << "ShopWidget::addView:" << "onPaid";
            update();
        });
        paymentDialog->show();
    });
}
