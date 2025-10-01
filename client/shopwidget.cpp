#include "shopwidget.h"
#include "configure.h"
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
    ui->tableWidget->setColumnWidth(int(ColomnName::View), 120);
}

ShopWidget::~ShopWidget() { delete ui; }

void ShopWidget::update() {
    TcpProductListClient *tcpProductListClient = new TcpProductListClient(this);
    tcpProductListClient->sendAsync(Configure::instance()->timeout());
    connect(tcpProductListClient, &TcpProductListClient::readyRead, this,
            [=](const TcpResponse &tcpResponse) {
                qDebug() << "ShopWidget::update:" << "response fetched:"
                 << QJsonObject(tcpResponse);
        if (tcpResponse.success()) {
                    QJsonObject responseBody = tcpResponse.body();
            QJsonArray productList = responseBody["product_list"].toArray();
                    for (qsizetype i = 0; i < productList.count(); ++i) {
                addProduct(productList[i].toObject());
                    }
        } else {
            qDebug() << "ShopWidget::update:" << "error:"
                     << TcpResponse::statusTypeToString(
                            tcpResponse.statusType())
                     << tcpResponse.statusDetail();
        }
    });
}

void ShopWidget::addProduct(const Product &product) {
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    addImage(row, product.imageUrl());
    addName(row, product.name());
    addPrice(row, product.price());
    addStock(row, product.stock());
    addView(row, product.id());
}

void ShopWidget::addImage(int row, const QUrl &imageUrl) {
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

void ShopWidget::addName(int row, const QString &productName) {
    ui->tableWidget->setItem(row, int(ColomnName::Name),
                             new QTableWidgetItem(productName));
}

void ShopWidget::addPrice(int row, double price) {
    ui->tableWidget->setItem(row, int(ColomnName::Price),
                             new QTableWidgetItem(QString::number(price)));
}

void ShopWidget::addStock(int row, qint64 stock) {
    ui->tableWidget->setItem(row, int(ColomnName::Stock),
                             new QTableWidgetItem(QString::number(stock)));
}

void ShopWidget::addView(int row, const QString &productId) {
    QLabel *viewLink =
        new QLabel("<a href='#' style='color: green;'>view details</a>");
    viewLink->setOpenExternalLinks(false);
    ui->tableWidget->setCellWidget(row, int(ColomnName::View), viewLink);
    connect(viewLink, &QLabel::linkActivated, this, [=]() {
        qDebug() << "ShopWidget::addView:" << "QLabel::linkActivated";
        PaymentDialog *paymentDialog = new PaymentDialog(this);
        paymentDialog->setProductId(productId);
        paymentDialog->update();
        paymentDialog->open();
    });
}
