#include "commander.h"
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
        emit readySetLightTheme();
    }
}

void Commander::setDarkTheme(bool checked) {
    if (checked) {
        qDebug() << Q_FUNC_INFO << "dark";
        emit readySetDarkTheme();
    }
}
