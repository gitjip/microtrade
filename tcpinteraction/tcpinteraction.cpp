#include "tcpinteraction.h"

TcpInteraction::TcpInteraction() {}

TcpInteraction::TcpInteraction(qint64 contentLength, const QDateTime &dateTime,
                               const QHostAddress &hostAddress, quint64 port,
                               const QJsonObject &body)
    : m_contentLength(contentLength), m_dateTime(dateTime),
    m_hostAddress(hostAddress), m_port(port), m_body(body) {}

TcpInteraction::~TcpInteraction() {}

QString TcpInteraction::toString(Item data)
{
    switch (data) {
    case Item::ContentLength:
        return "content_length";
    case Item::DateTime:
        return "date_time";
    case Item::Body:
        return "body";
    case Item::HostAddress:
        return "host_address";
    case Item::Port:
        return "port";
    case Item::AuthorizedToken:
        return "AuthorizedToken";
    case Item::Route:
        return "route";
    case Item::Timeout:
        return "timeout";
    case Item::Success:
        return "success";
    case Item::StatusType:
        return "status_type";
    case Item::StatusDetail:
        return "status_detail";
    default:
        return "";
    }
}
