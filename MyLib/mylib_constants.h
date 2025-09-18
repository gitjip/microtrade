#ifndef MYLIB_CONSTANTS_H
#define MYLIB_CONSTANTS_H

#include <QHostAddress>
#include <QJsonObject>
#include <QJsonValue>

namespace My {
inline const QHostAddress ServerHostAddress("127.0.0.1");
constexpr quint64 ServerPort = 8888;

using Headers = QJsonObject;
using Body = QJsonValue;
} // namespace My

#endif // MYLIB_CONSTANTS_H
