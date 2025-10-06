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
    void update();

private slots:
    void onCartProductListClientReadyRead(const TcpResponse &response);
    void onPayPushButtonClicked();
    void onCartSyncClientReadyRead(const TcpResponse &response);
    void sendPaymentRequest(const TcpResponse &);
    void onPaymentClientReadyRead(const TcpResponse &response);
    void onCommanderSynchronoused();

private:
    enum class ColomnName { Id, Image, Name, Price, Stock, Quantity, Remove };

private:
    void setProduct(int row, const Product &product, qint64 quantity);
    void setProductId(int row, qint64 productId);
    void setImage(int row, const QUrl &imageUrl);
    void setName(int row, const QString &productName);
    void setPrice(int row, double price);
    void setStock(int row, qint64 stock);
    void setQuantity(int row, qint64 quantity);
    void setRemove(int row, qint64 productId);

private:
    Ui::CartWidget *ui;
};

#endif // CARTWIDGET_H
