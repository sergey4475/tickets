#ifndef AVSETTINGS_H
#define AVSETTINGS_H

#include "avcore_global.h"
#include <QObject>
#include <QSettings>
#include <QByteArray>
#include <QFile>
#include <QQueue>
#include <QMap>

class AVCORESHARED_EXPORT avSettings : public QObject
{
    Q_OBJECT
public:
    explicit avSettings(QString fileconfig="", QObject *parent = nullptr);
    void saveSettings(QString &section, QMap<QString,QVariant> params);
    QMap<QString,QVariant> loadSettings(QString section, QString que);

private:
    QString p_fileconfig;

signals:

public slots:
};

#endif // AVSETTINGS_H
