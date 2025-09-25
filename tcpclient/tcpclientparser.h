#ifndef TCPCLIENTPARSER_H
#define TCPCLIENTPARSER_H

#include <QObject>

class TcpClientParser : public QObject
{
    Q_OBJECT
public:
    explicit TcpClientParser(QObject *parent = nullptr);

signals:
};

#endif // TCPCLIENTPARSER_H
