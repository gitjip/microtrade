#include "window.h"

namespace My {
Window::Window(QWidget *parent) : QMainWindow{parent} {}

void Window::closeEvent(QCloseEvent *e) {
    e->accept();
    emit closed();
}

void Window::switchTo(Window *window) {
    window->setGeometry(geometry());
    hide();
    window->show();
    connect(window, &Window::closed, this, [=]() {
        delete window;
        show();
    });
}
} // namespace My
