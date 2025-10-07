#ifndef ENTITY_GLOBAL_H
#define ENTITY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ENTITY_LIBRARY)
#define ENTITY_EXPORT Q_DECL_EXPORT
#else
#define ENTITY_EXPORT Q_DECL_IMPORT
#endif

#endif // ENTITY_GLOBAL_H
