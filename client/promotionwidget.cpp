#include "promotionwidget.h"
#include "commander.h"
#include "tcppromotionlistclient.h"
#include "ui_promotionwidget.h"
#include <QJsonArray>

PromotionWidget::PromotionWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::PromotionWidget) {
    ui->setupUi(this);
    connect(Commander::instance(), &Commander::publicUpdated, this,
            &PromotionWidget::update);
}

PromotionWidget::~PromotionWidget() { delete ui; }

void PromotionWidget::update() {
    TcpPromotionListClient *promotionListClient =
        new TcpPromotionListClient(this);
    connect(promotionListClient, &TcpPromotionListClient::readyRead, this,
            &PromotionWidget::onPromotionListClientReadyRead);
}

void PromotionWidget::onPromotionListClientReadyRead(
    const TcpResponse &response) {
    qDebug() << Q_FUNC_INFO << response.toJson();
    if (response.success()) {
        QJsonObject responseBody = response.body();
        QJsonArray promotionJsonArray = responseBody["promotionList"].toArray();
        ui->tableWidget->setRowCount(promotionJsonArray.count());
        for(qsizetype i=0;i<promotionJsonArray.count();++i){

        }
    }
}

void PromotionWidget::setPromotion(int row, const Promotion &promotion){

}

void PromotionWidget::setPromotionId(int row, qint64 promotionId){

}

void PromotionWidget::setDescription(int row, const QString &description){

}
void PromotionWidget::setStartAt(int row, const QDateTime &startAt){

}

void PromotionWidget::setEndAt(int row, const QDateTime &endAt){

}
