#include "authorizationmanager.h"
#include <QDebug>

AuthorizationManager::AuthorizationManager(QObject *parent) : QObject(parent) {}

AuthorizationManager *AuthorizationManager::instance() {
    static AuthorizationManager authorizationManager;
    return &authorizationManager;
}

void AuthorizationManager::login(const QString &token) {
    if (m_token.isEmpty()) {
        m_token = token;
        emit loggedin();
        emit updated();
        qDebug() << "AuthorizationManager::login:" << m_token;
    } else {
        qDebug() << "AuthorizationManager::login:" << "already login" << token;
    }
}

void AuthorizationManager::logout() {
    if (!m_token.isEmpty()) {
        m_token = "";
        emit loggedout();
        qDebug() << "AuthorizationManager::logout:" << "successfully logout";
    } else {
        qDebug() << "AuthorizationManager::logout:" << "not login";
    }
}

QString AuthorizationManager::token() const { return m_token; }

bool AuthorizationManager::isLoggedin() const { return !m_token.isEmpty(); }

void AuthorizationManager::update() { emit updated(); }
