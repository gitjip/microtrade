#ifndef ORDERITEM_H
#define ORDERITEM_H

class OrderItem
{
public:
    OrderItem();

private:
    int id;
    int orderId;
    int goodsId;
    int quantity;
    double price;
};

#endif // ORDERITEM_H
