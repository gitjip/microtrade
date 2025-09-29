#include "authorizationmanager.h"
#include <QDebug>

AuthorizationManager::AuthorizationManager(QObject *parent) : QObject(parent) {}

AuthorizationManager *AuthorizationManager::instance() {
    static AuthorizationManager authorizationManager;
    return &authorizationManager;
}

void AuthorizationManager::login(const QString &authorizedToken) {
    m_authorizedToken = authorizedToken;
    qDebug() << "AuthorizationManager::login:" << m_authorizedToken;
}

void AuthorizationManager::logout() { m_authorizedToken = ""; }

QString AuthorizationManager::authorizedToken() const {
    return m_authorizedToken;
}

bool AuthorizationManager::isLoggedin() const {
    return !m_authorizedToken.isEmpty();
}

void AuthorizationManager::update() { emit updated(); }
