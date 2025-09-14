#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QHostAddress>

namespace My {
inline const QHostAddress ServerHostAddress("127.0.0.1");
constexpr quint64 ServerPort = 8888;
} // namespace My

#endif // CONSTANTS_H
