#include "commander.h"
#include "qsettings.h"
#include <QDebug>

Commander::Commander(QObject *parent) : QObject(parent) {}

Commander *Commander::instance() {
    static Commander commander;
    return &commander;
}

void Commander::login(const QString &token) {
    if (m_token.isEmpty()) {
        m_token = token;
        emit loggedin();
        emit privateUpdated();
    }
}

void Commander::logout() {
    if (!m_token.isEmpty()) {
        m_token = "";
        emit loggedout();
    }
}

QString Commander::token() const { return m_token; }

bool Commander::isLoggedin() const { return !m_token.isEmpty(); }

void Commander::privateUpdate() { emit privateUpdated(); }

void Commander::publicUpdate() { emit publicUpdated(); }

void Commander::synchronous() { emit synchronoused(); }

void Commander::setLightTheme(bool checked) {
    if (checked) {
        qDebug() << Q_FUNC_INFO << "light";
        m_isDarkTheme = false;
        emit readySetLightTheme();
    }
}

void Commander::setDarkTheme(bool checked) {
    if (checked) {
        qDebug() << Q_FUNC_INFO << "dark";
        m_isDarkTheme = true;
        emit readySetDarkTheme();
    }
}

bool Commander::isDarkTheme() const { return m_isDarkTheme; }

bool Commander::isSystemDarkTheme() {
    QSettings settings(
        "HKEY_CURRENT_"
        "USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        QSettings::NativeFormat);
    return settings.value("AppsUseLightTheme", 1).toInt() == 0;
}

void Commander::setAutoTheme(bool checked) {
    if (checked) {
        if (isSystemDarkTheme()) {
            Commander::instance()->setDarkTheme(true);
        } else {
            Commander::instance()->setLightTheme(true);
        }
    }
}
