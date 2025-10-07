#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#include "tcpresponse.h"
#include "user.h"
#include <QWidget>

namespace Ui {
class ProfileWidget;
}

class ProfileWidget : public QWidget {
    Q_OBJECT

public:
    explicit ProfileWidget(QWidget *parent = nullptr);
    ~ProfileWidget();

public slots:
    void update();

private slots:
    void onUserClientReadyRead(const TcpResponse &response);
    void clear();

private:
    void setUser(const User &user);
    void setUserAvatar(const QUrl &avatarUrl);
    void setUserName(const QString &username);

private:
    Ui::ProfileWidget *ui;
};

#endif // PROFILEWIDGET_H
