#ifndef AVSQL_GLOBAL_H
#define AVSQL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(AVSQL_LIBRARY)
#  define AVMODULESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define AVMODULESSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // AVSQL_GLOBAL_H
