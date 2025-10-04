#ifndef CARTWIDGET_H
#define CARTWIDGET_H

#include "product.h"
#include "tcpresponse.h"
#include <QWidget>

namespace Ui {
class CartWidget;
}

class CartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CartWidget(QWidget *parent = nullptr);
    ~CartWidget();

public slots:
    // void update();

private slots:
    // void onCartItemListClientReadyRead(const TcpResponse &response);

private:
    enum class ColomnName { Image, Name, Price, Stock, Quantity };

private:
    void setProduct(int row, const Product &product);
    void setImage(int row, const QUrl &imageUrl);
    void setName(int row, const QString &productName);
    void setPrice(int row, double price);
    void setStock(int row, qint64 stock);
    void setQuantity(int row, qint64 productId);

private:
    Ui::CartWidget *ui;
};

#endif // CARTWIDGET_H
