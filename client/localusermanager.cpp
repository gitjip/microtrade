#include "localusermanager.h"

LocalUserManager::LocalUserManager(QObject *parent)
    : QObject{parent}, loggedin(false), userId(0) {}

LocalUserManager *LocalUserManager::getInstance() {
    static LocalUserManager instance;
    return &instance;
}

void LocalUserManager::login(int userId) {
    loggedin = true;
    this->userId = userId;
}

void LocalUserManager::logout() { loggedin = false; }

bool LocalUserManager::isLoggedin() const { return loggedin; }

int LocalUserManager::getUserId() const { return loggedin ? userId : 0; }
