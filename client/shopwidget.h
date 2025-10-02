#ifndef SHOPWIDGET_H
#define SHOPWIDGET_H

#include <QWidget>
#include "product.h"

namespace Ui {
class ShopWidget;
}

class ShopWidget : public QWidget {
    Q_OBJECT

public:
    explicit ShopWidget(QWidget *parent = nullptr);
    ~ShopWidget();
    void update();

private:
    enum class ColomnName { Image, Name, Price, Stock, View };

private:
    void addProduct(const Product &product);
    void setProduct(int row, const Product &product);
    void setImage(int row, const QUrl &imageUrl);
    void setName(int row, const QString &productName);
    void setPrice(int row, double price);
    void setStock(int row, qint64 stock);
    void setView(int row, const QString &productId);

private:
    Ui::ShopWidget *ui;
};

#endif // SHOPWIDGET_H
