#ifndef AUTHORIZATIONMANAGER_H
#define AUTHORIZATIONMANAGER_H

#include <QObject>

class AuthorizationManager : public QObject
{
    Q_OBJECT
public:
    static AuthorizationManager *instance(); // single instance
    void login(const QString &authorizedToken);
    void logout();
    QString authorizedToken() const;
    bool isLoggedin() const;

signals:
    void loggedin();
    void loggedout();
    void updated();

public slots:
    void update();

private:
    explicit AuthorizationManager(QObject *parent = nullptr);
    AuthorizationManager(const AuthorizationManager &authorizationManager) = delete;
    AuthorizationManager &operator=(const AuthorizationManager &authorizationManager) = delete;

private:
    QString m_authorizedToken; // empty if not loggedin
};

#endif // AUTHORIZATIONMANAGER_H
