#include "CEPlugin.h"


CEPlugin::CEPlugin()
{
    fprintf(stderr, "\n%s::%s(%d) called - ctor()!!!!!!!!!!!!!!!\n\n", __FILE__, __FUNCTION__, __LINE__);
    m_text = "initial value for private member named 'm_text'";
}

QString CEPlugin::text() const
{
    fprintf(stderr, "\n%s::%s(%d) called: returning %s\n", __FILE__, __FUNCTION__, __LINE__, m_text.toUtf8().data());
    return m_text;
}

void CEPlugin::setText(const QString &text)
{
    fprintf(stderr, "\n%s::%s(%d) called with argument = %s\n", __FILE__, __FUNCTION__, __LINE__, text.toUtf8().data());
    m_text = text;
}

#include "moc_CEPlugin.cpp"


QTNPFACTORY_BEGIN("NonWidget Qt-based Plugin", "A Qt-based browser plug-in that does interacts with javascript")
    QTNPCLASS(CEPlugin)
QTNPFACTORY_END()
