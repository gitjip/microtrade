#include "paymentdialog.h"
#include "config.h"
#include "product.h"
#include "tcpproductclient.h"
#include "ui_paymentdialog.h"
#include "tcpaddtocartclient.h"

PaymentDialog::PaymentDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::PaymentDialog) {
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
}

PaymentDialog::~PaymentDialog() { delete ui; }

void PaymentDialog::setProductId(const QString &productId) {
    m_productId = productId;
    qDebug() << "PaymentDialog::setProductId:" << productId;
}

void PaymentDialog::setRow(int row){
    ui->tableWidget->setItem(int(RowName::Row), 0,
                             new QTableWidgetItem(QString::number(row + 1)));
}

void PaymentDialog::update() {
    TcpProductClient *tcpProductClient = new TcpProductClient(this);
    tcpProductClient->sendAsync(m_productId, Config::instance()->timeout());
    connect(tcpProductClient, &TcpProductClient::readyRead, this,
            [=](const TcpResponse &tcpResponse) {
                qDebug() << "PaymentDialog::update:" << "response fetched:"
                 << QJsonObject(tcpResponse);
        if (tcpResponse.success()) {
                    QJsonObject responseBody = tcpResponse.body();
            Product product = responseBody["product"].toObject();
                    setImage(product.imageUrl());
            setName(product.name());
                    setPrice(product.price());
            setStock(product.stock());
                    setDescription(product.description());
        } else {
            qDebug() << "PaymentDialog::update:" << "error:"
                     << TcpResponse::statusTypeToString(
                            tcpResponse.statusType())
                     << tcpResponse.statusDetail();
        }
    });
}

void PaymentDialog::setImage(const QUrl &imageUrl) {
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

void PaymentDialog::setName(const QString &name) {
    ui->tableWidget->setItem(int(RowName::Name), 0, new QTableWidgetItem(name));
}

void PaymentDialog::setPrice(double price) {
    ui->tableWidget->setItem(int(RowName::Price), 0, new QTableWidgetItem(QString::number(price)));
}

void PaymentDialog::setStock(qint64 stock) {
    ui->tableWidget->setItem(int(RowName::Stock), 0, new QTableWidgetItem(QString::number(stock)));
}

void PaymentDialog::setDescription(const QString &description) {
    ui->tableWidget->setItem(int(RowName::Description), 0,
                             new QTableWidgetItem(description));
}

void PaymentDialog::on_payPushButton_clicked()
{
    qDebug()<<"PaymentDialog::on_payPushButton_clicked";
    TcpAddToCartClient *paymentClient = new TcpAddToCartClient(this);
    paymentClient->sendAsync(m_productId, Config::instance()->timeout());
    connect(paymentClient, &TcpProductClient::readyRead, this,
            [=](const TcpResponse &tcpResponse) {
                qDebug() << "PaymentDialog::on_payPushButton_clicked:" << "response fetched:"
                         << QJsonObject(tcpResponse);
                if (tcpResponse.success()) {
                    QJsonObject responseBody = tcpResponse.body();
                    Product product = responseBody["product"].toObject();
                    setImage(product.imageUrl());
                    setName(product.name());
                    setPrice(product.price());
                    setStock(product.stock());
                    setDescription(product.description());
                } else {
                    qDebug() << "PaymentDialog::on_payPushButton_clicked:" << "error:"
                             << TcpResponse::statusTypeToString(
                                    tcpResponse.statusType())
                             << tcpResponse.statusDetail();
                }
            });
    emit paid();
}

