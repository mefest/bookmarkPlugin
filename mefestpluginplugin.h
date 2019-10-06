#ifndef MEFESTPLUGIN_H
#define MEFESTPLUGIN_H

#include <QVector>

#include "mefestplugin_global.h"

#include <extensionsystem/iplugin.h>
#include <texteditor/texteditor.h>
#include <texteditor/textmark.h>

#include "bookmark.h"
#include "bookmarkmanager.h"

namespace mefestPlugin {
namespace Internal {

class mefestPluginPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "mefestPlugin.json")

public:
    mefestPluginPlugin();
    ~mefestPluginPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private:
    void triggerAction();
    void _initActions();
    QVector<QObject *> _listObjects;
    void toggleBookmark();
    void goBookmark();
    BookmarkManager _bookManager;
};

} // namespace Internal
} // namespace mefestPlugin

#endif // MEFESTPLUGIN_H
