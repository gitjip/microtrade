#ifndef SHOPWIDGET_H
#define SHOPWIDGET_H

#include <QWidget>
#include "tcpclient.h"

namespace Ui {
class ShopWidget;
}

class ShopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShopWidget(QWidget *parent = nullptr);
    ~ShopWidget();
    void setClient(My::TcpClient *client);
    void refresh();

private:
    Ui::ShopWidget *ui;
    My::TcpClient *client;
};

#endif // SHOPWIDGET_H
