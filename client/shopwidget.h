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
    void addImage(int row, const QUrl &imageUrl);
    void addName(int row, const QString &productName);
    void addPrice(int row, double price);
    void addStock(int row, qint64 stock);
    void addView(int row, const QString &productId);

private:
    Ui::ShopWidget *ui;
};

#endif // SHOPWIDGET_H
