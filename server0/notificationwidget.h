#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <QWidget>

namespace Ui {
class NotificationWidget;
}

class NotificationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NotificationWidget(QWidget *parent = nullptr);
    ~NotificationWidget();

private:
    Ui::NotificationWidget *ui;
};

#endif // NOTIFICATIONWIDGET_H
