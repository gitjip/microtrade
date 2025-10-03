#ifndef PAYMENTDIALOG_H
#define PAYMENTDIALOG_H

#include "tcpresponse.h"
#include <QDialog>

namespace Ui {
class PaymentDialog;
}

class PaymentDialog : public QDialog {
    Q_OBJECT

public:
    explicit PaymentDialog(QWidget *parent = nullptr);
    ~PaymentDialog();
    void setProductId(qint64 productId);
    void setRow(int row);

signals:
    void paid();

public slots:
    void update();
    void addToCart();

private:
    void tryUpdate(const TcpResponse &tcpResponse);
    void tryAddToCart(const TcpResponse &tcpResponse);

private:
    enum class RowName { Row, Image, Name, Price, Stock, Description };

private:
    void setImage(const QUrl &imageUrl);
    void setName(const QString &name);
    void setPrice(double price);
    void setStock(qint64 stock);
    void setDescription(const QString &description);

private:
    Ui::PaymentDialog *ui;
    qint64 m_productId;
};

#endif // PAYMENTDIALOG_H
