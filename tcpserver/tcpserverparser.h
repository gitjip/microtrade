#ifndef TCPSERVERPARSER_H
#define TCPSERVERPARSER_H

#include <QObject>

class TcpServerParser : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerParser(QObject *parent = nullptr);

signals:
};

#endif // TCPSERVERPARSER_H
