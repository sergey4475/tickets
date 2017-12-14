#ifndef AVCORE_H
#define AVCORE_H

#include "avcore_global.h"
#include <QCryptographicHash>
#include <QString>

class AVCORESHARED_EXPORT AvCore
{

public:
    AvCore();
    static QString md5(const QString &value);
};

#endif // AVCORE_H
