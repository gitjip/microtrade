#ifndef CARTWIDGET_H
#define CARTWIDGET_H

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

private:
    Ui::CartWidget *ui;
};

#endif // CARTWIDGET_H
