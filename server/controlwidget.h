#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include "controllerfactory.h"
#include "tcpserver.h"
#include <QWidget>

namespace Ui {
class ControlWidget;
}

class ControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControlWidget(QWidget *parent = nullptr);
    ~ControlWidget();

private slots:
    void on_checkBoxListen_checkStateChanged(const Qt::CheckState &state);

private:
    Ui::ControlWidget *ui;
    My::TcpServer *server;
    My::ControllerFactory *controllerFactory;
};

#endif // CONTROLWIDGET_H
