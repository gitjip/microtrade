#include "authorizationmanager.h"
#include <QDebug>

AuthorizationManager::AuthorizationManager(QObject *parent) : QObject(parent) {}

AuthorizationManager *AuthorizationManager::instance() {
    static AuthorizationManager authorizationManager;
    return &authorizationManager;
}

void AuthorizationManager::login(const QString &authorizedToken) {
    if(m_authorizedToken.isEmpty()) {
        m_authorizedToken = authorizedToken;
        emit loggedin();
        qDebug() << "AuthorizationManager::login:" << m_authorizedToken;
    }else{
        qDebug() << "AuthorizationManager::login:" << "already login";
    }
}

void AuthorizationManager::logout() {
    if(!m_authorizedToken.isEmpty()){
        m_authorizedToken = "";
        emit loggedout();
        qDebug() << "AuthorizationManager::logout:" << "successfully logout";
    } else{
        qDebug() << "AuthorizationManager::logout:" << "not login yet";
    }
}

QString AuthorizationManager::authorizedToken() const {
    return m_authorizedToken;
}

bool AuthorizationManager::isLoggedin() const {
    return !m_authorizedToken.isEmpty();
}

void AuthorizationManager::update() { emit updated(); }
