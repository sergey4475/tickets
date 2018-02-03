#include "avsettings.h"

avSettings::avSettings(QString fileconfig, QObject *parent)
    : QObject(parent)
{
    if (fileconfig == "")
        p_fileconfig = "config.cfg";
    else
        p_fileconfig = fileconfig;


}

/**
 * @brief avSettings::saveSettings
 * @param section
 * @param params
 */
void avSettings::saveSettings(QString &section, QMap<QString, QVariant> params)
{
    QSettings setting(p_fileconfig,QSettings::IniFormat);

    QMap<QString, QVariant>::iterator it = params.begin();
    setting.beginGroup(section);
    while (it != params.end()){
        setting.setValue(it.key(),it.value());
        ++it;
    }
    setting.endGroup();
    setting.sync();

}

/**
 * @brief avSettings::loadSettings
 * @param section - из какой секции выбирать параметры
 * @param que - строка параметров разделяемых ","
 * @return
 */
QMap<QString, QVariant> avSettings::loadSettings(QString section, QString que)
{
    QMap<QString,QVariant> param;

    QSettings setting(p_fileconfig,QSettings::IniFormat);

    setting.beginGroup(section);
    QStringList lParams = que.split(",",QString::SkipEmptyParts);

    foreach (const QString &str, lParams) {
        param[str] = setting.value(str);
    }

    return param;
}
