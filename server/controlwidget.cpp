#include "controlwidget.h"
#include "constants.h"
#include "ui_controlwidget.h"
#include <QMessageBox>

ControlWidget::ControlWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ControlWidget), server(new My::TcpServer) {
    ui->setupUi(this);
}

ControlWidget::~ControlWidget() { delete ui; }

void ControlWidget::on_checkBoxListen_checkStateChanged(
    const Qt::CheckState &state) {
    if (state == Qt::Checked) {
        bool result = server->listen(My::ServerHostAddress, My::ServerPort);
        if (!result) {
            ui->checkBoxListen->setCheckState(Qt::Unchecked);
            QMessageBox::critical(this, "无法启动监听", "");
        } else {
            qDebug() << "成功开启监听";
        }
    } else if (state == Qt::Unchecked) {
        server->close();
        qDebug() << "成功关闭监听";
    }
}
