#include "authorizationmanager.h"
#include <QDebug>

AuthorizationManager::AuthorizationManager(QObject *parent) : QObject(parent) {}

AuthorizationManager *AuthorizationManager::instance() {
    static AuthorizationManager authorizationManager;
    return &authorizationManager;
}

void AuthorizationManager::login(const Authorization &authorization) {
    if (m_authorization.isNull()) {
        m_authorization = authorization;
        emit loggedin();
        qDebug() << "AuthorizationManager::login:" << m_authorization.token();
    } else {
        qDebug() << "AuthorizationManager::login:" << "already login";
    }
}

void AuthorizationManager::login(const QString &token) {
    if (token.isEmpty()) {
        m_authorization = Authorization(-1, {}, {}, -1, token);
        emit loggedin();
        qDebug() << "AuthorizationManager::login:" << m_authorization.token();
    } else {
        qDebug() << "AuthorizationManager::login:" << "already login";
    }
}

void AuthorizationManager::logout() {
    if (!m_authorization.isNull()) {
        m_authorization = {};
        emit loggedout();
        qDebug() << "AuthorizationManager::logout:" << "successfully logout";
    } else {
        qDebug() << "AuthorizationManager::logout:" << "not login";
    }
}

Authorization AuthorizationManager::authorization() const {
    return m_authorization;
}

QString AuthorizationManager::token() const { return m_authorization.token(); }

bool AuthorizationManager::isLoggedin() const {
    return !m_authorization.isNull();
}

void AuthorizationManager::update() { emit updated(); }
