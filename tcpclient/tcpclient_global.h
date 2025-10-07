#ifndef TCPCLIENT_GLOBAL_H
#define TCPCLIENT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TCPCLIENT_LIBRARY)
#define TCPCLIENT_EXPORT Q_DECL_EXPORT
#else
#define TCPCLIENT_EXPORT Q_DECL_IMPORT
#endif

#endif // TCPCLIENT_GLOBAL_H
