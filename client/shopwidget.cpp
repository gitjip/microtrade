#include "shopwidget.h"
#include "response.h"
#include "ui_shopwidget.h"
#include <QImage>

ShopWidget::ShopWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ShopWidget) {
    ui->setupUi(this);
}

void ShopWidget::setClient(My::TcpClient *client) { this->client = client; }

void ShopWidget::refresh() {
    int index = 1;
    client->postAsync("/shop", My::Headers(), My::Body(index));
    connect(client, &My::TcpClient::readyRead, this, [&](const My::Response &res) {
        if (res.status == 200) {
            ui->tableWidget->clearContents();
            QPixmap image;
            QTableWidgetItem *imageItem = new QTableWidgetItem;
            QTableWidgetItem *nameItem = new QTableWidgetItem;
            QTableWidgetItem *priceItem = new QTableWidgetItem;
            QTableWidgetItem *stockItem = new QTableWidgetItem;
            QTableWidgetItem *descriptionItem = new QTableWidgetItem;
            if(image.loadFromData(QByteArray::fromBase64(res.body["image"].toString().toUtf8()))) {
                imageItem->setIcon(image);
            } else {
                imageItem->setText("图片加载失败");
            }
            nameItem->setText(res.body["name"].toString());
            priceItem->setText(QString::number(res.body["price"].toDouble()));
            stockItem->setText(QString::number(res.body["stock"].toInt()));
            descriptionItem->setText(res.body["description"].toString());
            ui->tableWidget->setItem(index - 1, 0, imageItem);
            ui->tableWidget->setItem(index - 1, 1, nameItem);
            ui->tableWidget->setItem(index - 1, 2, priceItem);
            ui->tableWidget->setItem(index - 1, 3, stockItem);
            ui->tableWidget->setItem(index - 1, 4, descriptionItem);
            client->postAsync("shop", My::Headers(), My::Body(++index));
        }
    });
}

ShopWidget::~ShopWidget() { delete ui; }
