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
    void tryLogin();
    void tryRegister();
    void tryLogout();
    void onLogin();
    void onLogout();

private:
    Ui::WelcomeWidget *ui;
};

#endif // WELCOMEWIDGET_H
