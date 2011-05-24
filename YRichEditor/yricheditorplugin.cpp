#include "yricheditor.h"
#include "yricheditorplugin.h"

#include <QtCore/QtPlugin>

YRichEditorPlugin::YRichEditorPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void YRichEditorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool YRichEditorPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *YRichEditorPlugin::createWidget(QWidget *parent)
{
    return new YRichEditor(parent);
}

QString YRichEditorPlugin::name() const
{
    return QLatin1String("YRichEditor");
}

QString YRichEditorPlugin::group() const
{
    return QLatin1String("YQtDesignerPlugin");
}

QIcon YRichEditorPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon_texteditor.png"));
}

QString YRichEditorPlugin::toolTip() const
{
    return QLatin1String("富文本编辑器控件");
}

QString YRichEditorPlugin::whatsThis() const
{
    return QLatin1String("富文本编辑器控件");
}

bool YRichEditorPlugin::isContainer() const
{
    return false;
}

QString YRichEditorPlugin::domXml() const
{
    return QLatin1String("<widget class=\"YRichEditor\" name=\"yRichEditor\">\n</widget>\n");
}

QString YRichEditorPlugin::includeFile() const
{
    return QLatin1String("yricheditor.h");
}

Q_EXPORT_PLUGIN2(YRichEditorPlugin, YRichEditorPlugin)
