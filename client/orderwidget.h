#ifndef ORDERWIDGET_H
#define ORDERWIDGET_H

#include "tcpcancelorderclient.h"
#include "tcpresponse.h"
#include <QAction>
#include <QMenu>
#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
class OrderWidget;
}

class OrderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWidget(QWidget *parent = nullptr);
    ~OrderWidget();

public slots:
    void update();
    void onOrderClientReadyRead(const TcpResponse &response);

private slots:
    void onTreeWidgetItemDoubleClicked(QTreeWidgetItem *item, int);
    void clear();
    void onTreeWidgetCustomContextMenuRequested(const QPoint &pos);
    void onCancelOrderTriggered();
    void onCancelOrderClientReadyRead(const TcpResponse &response);

private:
    enum class OrderColomn { Id, Cost, Status, CreatedAt };
    enum class OrderItemColomn { Id, Cost, Quantity, CreatedAt, ProductId };

private:
    void initFrontEnd();

private:
    Ui::OrderWidget *ui;
    QMap<QTreeWidgetItem *, qint64> productIdMap;
    QMap<QTreeWidgetItem *, qint64> orderIdMap;
    QTreeWidgetItem *currentOrderItem;
};

#endif // ORDERWIDGET_H
