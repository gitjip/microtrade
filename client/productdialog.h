#ifndef PRODUCTDIALOG_H
#define PRODUCTDIALOG_H

#include "tcpresponse.h"
#include <QDialog>

namespace Ui {
class ProductDialog;
}

class ProductDialog : public QDialog {
    Q_OBJECT

public:
    explicit ProductDialog(QWidget *parent = nullptr);
    ~ProductDialog();
    // void setRow(int row);
    void setProductId(qint64 productId);

signals:
    void addedToCart();

public slots:
    void update();
    void onAddToCartPushButtonClicked();

private:
    void onProductClientReadyRead(const TcpResponse &tcpResponse);
    void onAddToCartClientReadyRead(const TcpResponse &tcpResponse);

private:
    enum class InfoRowName { Image, Name, Price, Stock, Description };
    enum class PromRowName { Id, Text, Start, End };

private:
    void setImage(const QUrl &imageUrl);
    void setName(const QString &name);
    void setPrice(double price);
    void setStock(qint64 stock);
    void setDescription(const QString &description);

private:
    Ui::ProductDialog *ui;
    qint64 m_productId;
};

#endif // PRODUCTDIALOG_H
