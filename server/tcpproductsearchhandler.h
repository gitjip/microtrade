#ifndef TCPPRODUCTSEARCHHANDLER_H
#define TCPPRODUCTSEARCHHANDLER_H

#include <tcphandler.h>

class TcpProductSearchHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpProductSearchHandler(QObject *parent = nullptr);
    void extracted(QJsonArray &tokenArray, QStringList &tokens);
    TcpResponse handle(const TcpRequest &request) override;
};

#endif // TCPPRODUCTSEARCHHANDLER_H
