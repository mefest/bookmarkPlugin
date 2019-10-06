#include "generaloptionpage.h"

#include <coreplugin/icore.h>

#include "mefestpluginconstants.h"
#include "utils.h"

#include <QDebug>
#include <QKeySequence>
#include <QSettings>

namespace mefestPlugin {
namespace Internal {
GeneralOptionPage::GeneralOptionPage()
{
    setId(Core::Id("MefestPluginGeneralOptionsPage"));
    setDisplayName(Constants::OPTION_NAME_TR);

    setCategory(Constants::OPTIONSPAGE_CATEGORY);
    setDisplayCategory(QLatin1String(Constants::OPTIONSPAGE_CATEGORY_TR_CATEGORY));
}

QWidget *GeneralOptionPage::widget()
{
    _settingsWidget = new GeneralOptionPageWidget();
    restoreSettings();
    return _settingsWidget;
}

void GeneralOptionPage::saveSettings()
{
    if (_settingsWidget->isChanged()) {
        QSettings *settings = Core::ICore::instance()->settings();
        QVector<QKeySequence> keySeq = _settingsWidget->getSeqSetMark();
        settings->beginGroup(Constants::PLUGIN_NAME);
        settings->beginGroup(Constants::OPTION_NAME);
        qDebug() << settings->group();
        for (int i = 0; i < Constants::NUMBER_MARKS; ++i) {
            auto key = keySeq[i];
            settings->setValue("setPosition_" + QString::number(i), key.toString());
        }
        keySeq = _settingsWidget->getSeqGetMark();
        for (int i = 0; i < Constants::NUMBER_MARKS; ++i) {
            auto key = keySeq[i];
            settings->setValue("getPosition_" + QString::number(i), key.toString());
        }
        settings->endGroup();
        settings->endGroup();
    }
    _settingsWidget->reset();
}

void GeneralOptionPage::restoreSettings()
{
    QVector<QKeySequence> setMarkSeqKey = Utils::getFromSettingKeySeqSetMarks();
    QVector<QKeySequence> getMarkSeqKey = Utils::getFromSettingKeySeqGetMarks();

    _settingsWidget->setSeqSetMark(setMarkSeqKey);
    _settingsWidget->setSeqGetMark(getMarkSeqKey);
    _settingsWidget->reset();
}

void GeneralOptionPage::apply()
{
    saveSettings();
    qDebug() << "apply";
}

void GeneralOptionPage::finish()
{
    saveSettings();
    qDebug() << "finish";
}

} // namespace Internal
} // namespace mefestPlugin
