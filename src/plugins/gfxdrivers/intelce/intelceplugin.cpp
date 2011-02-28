#include "intelcescreen.h"

#include <QScreenDriverPlugin>
#include <QStringList>

class IntelCEPlugin : public QScreenDriverPlugin
{
public:
    IntelCEPlugin();

    QStringList keys() const;
    QScreen *create(const QString&, int displayId);
};

IntelCEPlugin::IntelCEPlugin()
    : QScreenDriverPlugin()
{
}

QStringList IntelCEPlugin::keys() const
{
    return (QStringList() << "intelce");
}

QScreen* IntelCEPlugin::create(const QString &driver, int displayId)
{
    if (driver.toLower() != "intelce")
        return 0;

    return new IntelCEScreen(displayId);
}

Q_EXPORT_STATIC_PLUGIN(IntelCE)
Q_EXPORT_PLUGIN2(intelcescreendriver, IntelCEPlugin)
