#include "tcpserverthreadpool.h"
#include "tcprequest.h"
#include "tcpresponse.h"
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>

TcpServerThreadPool::TcpServerThreadPool(QObject *parent)
    : QObject{parent}, m_threadPool(QThreadPool::globalInstance())
{}

void TcpServerThreadPool::setMaxThreadCount(int maxThreadCount) {
    m_threadPool->setMaxThreadCount(maxThreadCount);
}

TcpResponse TcpServerThreadPool::start(TcpServerHandler *handler, const TcpRequest &tcpRequest) {
    qDebug() << "TcpServerThreadPool::start";
    if(!handler){
        qDebug() << "TcpServerThreadPool::start" << "handler is null";
        return TcpResponse();
    }
    QFuture<TcpResponse> future =
        QtConcurrent::run(m_threadPool, [handler, tcpRequest]() {
        return handler->handle(tcpRequest);
    });
    bool done = tcpRequest.timeout() != -1
                    ? m_threadPool->waitForDone(tcpRequest.timeout())
                    : m_threadPool->waitForDone(QDeadlineTimer::Forever);
    if (!done) {
        qDebug() << "TcpServerThreadPool::start: timeout";
        return TcpResponse();
    }
    qDebug() << "TcpServerThreadPool::start: finished";
    return future.result();
}
