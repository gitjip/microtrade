#include "productitemwidget.h"
#include "ui_productitemwidget.h"

ProductItemWidget::ProductItemWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ProductItemWidget) {
    ui->setupUi(this);
}

void ProductItemWidget::setProduct(const Product &product) {
    QPixmap pixmap;
    if (pixmap.load(product.imageUrl().toString())) {
        ui->imageLabel->setPixmap(pixmap);
    } else {
        qDebug() << "failed to load image";
    }
    ui->nameLabel->setText(product.name());
    ui->priceLabel->setText(QString::number(product.price()));
    ui->stockLabel->setText(QString::number(product.stock()));
}

ProductItemWidget::~ProductItemWidget() { delete ui; }
