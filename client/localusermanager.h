#ifndef LOCALUSERMANAGER_H
#define LOCALUSERMANAGER_H

#include <QObject>

class LocalUserManager : public QObject {
    Q_OBJECT
public:
    static LocalUserManager *getInstance();
    void login(int userId);
    void logout();
    bool isLoggedin() const;
    int getUserId() const;

private:
    explicit LocalUserManager(QObject *parent = nullptr);
    LocalUserManager(const LocalUserManager &other) = delete;
    LocalUserManager &operator=(const LocalUserManager &other) = delete;

signals:
    void loggedin();
    void loggedout();
    void updated();

private:
    int userId;
};

#endif // LOCALUSERMANAGER_H
