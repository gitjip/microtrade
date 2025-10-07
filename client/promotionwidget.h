#ifndef PROMOTIONWIDGET_H
#define PROMOTIONWIDGET_H

#include "promotion.h"
#include "tcpresponse.h"
#include <QWidget>

namespace Ui {
class PromotionWidget;
}

class PromotionWidget : public QWidget {
    Q_OBJECT

public:
    explicit PromotionWidget(QWidget *parent = nullptr);
    ~PromotionWidget();

public slots:
    void update();

private slots:
    void onPromotionListClientReadyRead(const TcpResponse &response);

private:
    enum class ColomnName { Id, Text, Start, End };

private:
    void setPromotion(int row, const Promotion &promotion);
    void setPromotionId(int row, qint64 promotionId);
    void setDescription(int row, const QString &description);
    void setStartAt(int row, const QDateTime &startAt);
    void setEndAt(int row, const QDateTime &endAt);

private:
    Ui::PromotionWidget *ui;
};

#endif // PROMOTIONWIDGET_H
