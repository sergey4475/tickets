#ifndef TICKETS_GLOBAL_H
#define TICKETS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TICKETS_LIBRARY)
#  define TICKETSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TICKETSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TICKETS_GLOBAL_H
