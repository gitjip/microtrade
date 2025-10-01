#ifndef PRODUCTITEMWIDGET_H
#define PRODUCTITEMWIDGET_H

#include <QWidget>
#include "product.h"

namespace Ui {
class ProductItemWidget;
}

class ProductItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductItemWidget(QWidget *parent = nullptr);
    ~ProductItemWidget();
    void setProduct(const Product &product);

private:
    Ui::ProductItemWidget *ui;
    Product m_product;
};

#endif // PRODUCTITEMWIDGET_H
