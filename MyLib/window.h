#ifndef WINDOW_H
#define WINDOW_H

#include "mylib_global.h"
#include <QCloseEvent>
#include <QMainWindow>

namespace My {
class Window : public QMainWindow {
    Q_OBJECT
public:
    explicit MYLIB_EXPORT Window(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *e) override;
    void switchTo(Window *window);

signals:
    void closed();
};
} // namespace My

#endif // WINDOW_H
