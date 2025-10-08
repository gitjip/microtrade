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
    void setProductId(qint64 productId);

signals:
    void addedToCart();

public slots:
    void update();
    void onAddToCartPushButtonClicked();

private:
    void onProductClientReadyRead(const TcpResponse &response);
    void onAddToCartClientReadyRead(const TcpResponse &response);
    void onTcpProductPromotionListClientReadyRead(const TcpResponse &response);

private:
    enum class InfoRowName { Image, Name, Price, Stock, Description };
    enum class PromColomnName { Id, Text, Start, End };

private:
    void setImage(const QUrl &imageUrl);
    void setName(const QString &name);
    void setPrice(double price);
    void setStock(qint64 stock);
    void setDescription(const QString &description);

private:
    void setPromId(int row, qint64 id);
    void setPromText(int row, const QString &text);
    void setPromStart(int row, const QDateTime &startAt);
    void setPromEndAt(int row, const QDateTime &endAt);

private:
    Ui::ProductDialog *ui;
    qint64 m_productId;
};

#endif // PRODUCTDIALOG_H
