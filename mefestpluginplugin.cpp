#include "mefestpluginplugin.h"
#include "mefestpluginconstants.h"

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>
#include <extensionsystem/pluginmanager.h>
#include <texteditor/textdocument.h>

#include <QAction>
#include <QDebug>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>

#include "generaloptionpage.h"
#include "utils.h"

namespace mefestPlugin {
namespace Internal {

mefestPluginPlugin::mefestPluginPlugin()
{
    // Create your members
}

mefestPluginPlugin::~mefestPluginPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
    for (auto object : _listObjects) {
        ExtensionSystem::PluginManager::removeObject(object);
        object->deleteLater();
    }
    _listObjects.clear();
}

bool mefestPluginPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    _initActions();

    return true;
}

void mefestPluginPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.

    _listObjects.push_back(new GeneralOptionPage());

    for (auto object : _listObjects) {
        ExtensionSystem::PluginManager::addObject(object);
    }
}

ExtensionSystem::IPlugin::ShutdownFlag mefestPluginPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

void mefestPluginPlugin::_initActions()
{
    QVector<QKeySequence> setMarkSeqKey = Utils::getFromSettingKeySeqSetMarks();

    for (int i = 0; i < Constants::NUMBER_MARKS; ++i) {
        QString actionId = QString(Constants::ACTION_BOOKMARK_TOGGLE) + QString::number(i);

        auto action = new QAction(actionId, this);
        action->setData(i);
        Core::Command *cmd
            = Core::ActionManager::registerAction(action,
                                                  actionId.toStdString().c_str(),
                                                  Core::Context(Core::Constants::C_EDITORMANAGER));
        cmd->setKeySequence(setMarkSeqKey[i]);
        connect(action, &QAction::triggered, this, &mefestPluginPlugin::toggleBookmark);
    }

    QVector<QKeySequence> getMarkSeqKey = Utils::getFromSettingKeySeqGetMarks();
    for (int i = 0; i < Constants::NUMBER_MARKS; ++i) {
        QString actionId = QString(Constants::ACTION_BOOKMARK_GO) + QString::number(i);

        auto action = new QAction(actionId, this);
        action->setData(i);
        Core::Command *cmd
            = Core::ActionManager::registerAction(action,
                                                  actionId.toStdString().c_str(),
                                                  Core::Context(Core::Constants::C_EDITORMANAGER));
        cmd->setKeySequence(getMarkSeqKey[i]);
        connect(action, &QAction::triggered, this, &mefestPluginPlugin::goBookmark);
    }
}

void mefestPluginPlugin::toggleBookmark()
{
    auto *action = qobject_cast<QAction *>(QObject::sender());
    qDebug() << action->text() << action->data();
    int numBookmark = action->data().toInt();
    if (numBookmark < 0 || numBookmark >= Constants::NUMBER_MARKS) {
        return;
    }
    auto editorManager = Core::EditorManager::instance();
    auto currentEditor = editorManager->currentEditor();
    auto *textDocument = qobject_cast<TextEditor::TextDocument *>(editorManager->currentDocument());
    if (!textDocument) {
        qDebug() << "incorrect document";
        return;
    }

    _bookManager.toogleBookmark(numBookmark, textDocument->filePath(), currentEditor->currentLine());
    if (_bookManager.isExistBookmark(numBookmark)) {
        auto mark = _bookManager.getBookmark(numBookmark);
        textDocument->addMark(mark);
    }
}

void mefestPluginPlugin::goBookmark()
{
    auto *action = qobject_cast<QAction *>(QObject::sender());
    int numBookmark = action->data().toInt();
    if (_bookManager.isExistBookmark(numBookmark)) {
        auto editorManager = Core::EditorManager::instance();
        auto mark = _bookManager.getBookmark(numBookmark);
        Core::EditorManager::openEditorAt(mark->fileName().toString(), mark->lineNumber());
    }
}

} // namespace Internal
} // namespace mefestPlugin
