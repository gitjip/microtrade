#ifndef COMMANDER_H
#define COMMANDER_H

#include <QObject>

class Commander : public QObject
{
    Q_OBJECT
public:
    static Commander *instance(); // single instance
    void login(const QString &token);
    void logout();
    QString token() const;
    bool isLoggedin() const;

signals:
    void loggedin();
    void loggedout();
    void privateUpdated();
    void publicUpdated();
    void synchronoused();

public slots:
    void privateUpdate();
    void publicUpdate();
    void synchronous();

private:
    explicit Commander(QObject *parent = nullptr);
    Commander(const Commander &authorizationManager) = delete;
    Commander &operator=(const Commander &authorizationManager) = delete;

private:
    QString m_token;    // Empty if not login
};

#endif // COMMANDER_H
