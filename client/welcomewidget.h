#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>

namespace Ui {
class WelcomeWidget;
}

class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWidget(QWidget *parent = nullptr);
    ~WelcomeWidget();

private slots:
    void on_loginPushButton_clicked();

    void on_registerPushButton_clicked();

    void on_logoutPushButton_clicked();

private:
    Ui::WelcomeWidget *ui;
};

#endif // WELCOMEWIDGET_H
