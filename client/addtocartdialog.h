#ifndef ADDTOCARTDIALOG_H
#define ADDTOCARTDIALOG_H

#include "tcpresponse.h"
#include <QDialog>

namespace Ui {
class AddToCartDialog;
}

class AddToCartDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddToCartDialog(QWidget *parent = nullptr);
    ~AddToCartDialog();
    void setProductId(qint64 productId);
    void setRow(int row);

signals:
    void addedToCart();

public slots:
    void update();
    void onAddToCartPushButtonClicked();

private:
    void onProductClientReadyRead(const TcpResponse &tcpResponse);
    void onAddToCartClientReadyRead(const TcpResponse &tcpResponse);

private:
    enum class RowName { Row, Image, Name, Price, Stock, Description };

private:
    void setImage(const QUrl &imageUrl);
    void setName(const QString &name);
    void setPrice(double price);
    void setStock(qint64 stock);
    void setDescription(const QString &description);

private:
    Ui::AddToCartDialog *ui;
    qint64 m_productId;
};

#endif // ADDTOCARTDIALOG_H
