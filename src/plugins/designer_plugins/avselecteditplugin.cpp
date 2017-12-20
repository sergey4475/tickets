#include "../../libs/avWidgets/avSelectEdit/avselectedit.h"
#include "avselecteditplugin.h"

#include <QtPlugin>

avSelectEditPlugin::avSelectEditPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void avSelectEditPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool avSelectEditPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *avSelectEditPlugin::createWidget(QWidget *parent)
{
    return new avSelectEdit(parent);
}

QString avSelectEditPlugin::name() const
{
    return QLatin1String("avSelectEdit");
}

QString avSelectEditPlugin::group() const
{
    return QLatin1String("Avega-sift");
}

QIcon avSelectEditPlugin::icon() const
{
    return QIcon();
}

QString avSelectEditPlugin::toolTip() const
{
    return QLatin1String("");
}

QString avSelectEditPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool avSelectEditPlugin::isContainer() const
{
    return false;
}

QString avSelectEditPlugin::domXml() const
{
    return QLatin1String("<widget class=\"avSelectEdit\" name=\"avSelectEdit1\">\n</widget>\n");
}

QString avSelectEditPlugin::includeFile() const
{
    return QLatin1String("../../libs/avWidgets/avSelectEdit/avselectedit.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(avselecteditplugin, avSelectEditPlugin)
#endif // QT_VERSION < 0x050000
