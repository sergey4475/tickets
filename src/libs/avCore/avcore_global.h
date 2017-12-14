#ifndef AVCORE_GLOBAL_H
#define AVCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(AVCORE_LIBRARY)
#  define AVCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define AVCORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // AVCORE_GLOBAL_H
