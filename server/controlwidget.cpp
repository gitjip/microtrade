#include "controlwidget.h"
#include "mylib_constants.h"
#include "ui_controlwidget.h"
#include <QMessageBox>

ControlWidget::ControlWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ControlWidget),
    server(new My::TcpServer(this)),
    controllerFactory(new My::ControllerFactory(server, this)) {
    ui->setupUi(this);
}

ControlWidget::~ControlWidget() { delete ui; }

void ControlWidget::on_checkBoxListen_checkStateChanged(
    const Qt::CheckState &state) {
    if (state == Qt::Checked) {
        if (!server->listen(My::ServerHostAddress, My::ServerPort)) {
            ui->checkBoxListen->setCheckState(Qt::Unchecked);
            QMessageBox::critical(this, "cannot listen", "");
        } else {
            qDebug() << "ControlWidget::on_checkBoxListen_checkStateChanged:"
                     << "listen";
        }
    } else if (state == Qt::Unchecked) {
        server->close();
        qDebug() << "ControlWidget::on_checkBoxListen_checkStateChanged:"
                 << "close";
    }
}
