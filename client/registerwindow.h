#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QCloseEvent>
#include <QMainWindow>

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();
    void closeEvent(QCloseEvent *e);

signals:
    void closed();

private slots:
    void on_pushButton_register_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::RegisterWindow *ui;
};

#endif // REGISTERWINDOW_H
