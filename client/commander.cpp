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
        qDebug() << Q_FUNC_INFO << m_token;
    } else {
        qDebug() << Q_FUNC_INFO << "already login" << token;
    }
}

void Commander::logout() {
    if (!m_token.isEmpty()) {
        m_token = "";
        emit loggedout();
        // emit synchronoused();
        qDebug() << Q_FUNC_INFO << "successfully logout";
    } else {
        qDebug() << Q_FUNC_INFO << "not login";
    }
}

QString Commander::token() const { return m_token; }

bool Commander::isLoggedin() const { return !m_token.isEmpty(); }

void Commander::privateUpdate() { emit privateUpdated(); }

void Commander::publicUpdate() { emit publicUpdated(); }

void Commander::synchronous() { emit synchronoused(); }
