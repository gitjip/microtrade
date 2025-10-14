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
    promotionListClient->sendAsync();
}

void PromotionWidget::onPromotionListClientReadyRead(
    const TcpResponse &response) {
    if (response.success()) {
        QJsonObject responseBody = response.body();
        QJsonArray promotionJsonArray = responseBody["promotionList"].toArray();
        ui->tableWidget->setRowCount(promotionJsonArray.count());
        for (qsizetype i = 0; i < promotionJsonArray.count(); ++i) {
            Promotion promotion =
                Promotion::fromJson(promotionJsonArray[i].toObject());
            setPromotion(i, promotion);
        }
    }
}

void PromotionWidget::setPromotion(int row, const Promotion &promotion) {
    setPromotionId(row, promotion.id());
    setDescription(row, promotion.description());
    setStartAt(row, promotion.startAt());
    setEndAt(row, promotion.endAt());
}

void PromotionWidget::setPromotionId(int row, qint64 promotionId) {
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(promotionId));
    ui->tableWidget->setItem(row, int(ColomnName::Id), item);
}

void PromotionWidget::setDescription(int row, const QString &description) {
    QTableWidgetItem *item = new QTableWidgetItem(description);
    ui->tableWidget->setItem(row, int(ColomnName::Text), item);
}

void PromotionWidget::setStartAt(int row, const QDateTime &startAt) {
    QTableWidgetItem *item = new QTableWidgetItem(startAt.toString());
    ui->tableWidget->setItem(row, int(ColomnName::Start), item);
}

void PromotionWidget::setEndAt(int row, const QDateTime &endAt) {
    QTableWidgetItem *item = new QTableWidgetItem(endAt.toString());
    ui->tableWidget->setItem(row, int(ColomnName::End), item);
}
