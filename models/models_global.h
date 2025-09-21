#ifndef MODELS_GLOBAL_H
#define MODELS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MODELS_LIBRARY)
#define MODELS_EXPORT Q_DECL_EXPORT
#else
#define MODELS_EXPORT Q_DECL_IMPORT
#endif

#endif // MODELS_GLOBAL_H
