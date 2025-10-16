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
    static bool isSystemDarkTheme();
    bool isDarkTheme() const;

signals:
    void loggedin();
    void loggedout();
    void privateUpdated();
    void publicUpdated();
    void synchronoused();
    // void readySetAutoTheme();
    void readySetLightTheme();
    void readySetDarkTheme();

public slots:
    void privateUpdate();
    void publicUpdate();
    void synchronous();
    // void setAutoTheme();
    void setLightTheme(bool checked);
    void setDarkTheme(bool checked);
    void setAutoTheme(bool checked);

private:
    explicit Commander(QObject *parent = nullptr);
    Commander(const Commander &authorizationManager) = delete;
    Commander &operator=(const Commander &authorizationManager) = delete;

private:
    QString m_token;    // Empty if not login
    bool m_isDarkTheme = false;
};

#endif // COMMANDER_H
