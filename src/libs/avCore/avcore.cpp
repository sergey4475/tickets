#include "avcore.h"


AvCore::AvCore()
{
}

QString AvCore::md5(const QString &value)
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(value.toLatin1());
    return hash.result().toHex();
}
