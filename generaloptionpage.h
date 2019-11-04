#ifndef GENERALOPTIONPAGE_H
#define GENERALOPTIONPAGE_H

#include <coreplugin/dialogs/ioptionspage.h>

#include "generaloptionpagewidget.h"

namespace mefestPlugin {
namespace Internal {
class GeneralOptionPage : public Core::IOptionsPage
{
public:
    GeneralOptionPage();

    // IOptionsPage interface
public:
    QWidget *widget();
    void apply() override;
    void finish() override;
    GeneralOptionPageWidget *_settingsWidget = nullptr;

private:
    void saveSettings();
    void restoreSettings();
};

} // namespace Internal
} // namespace mefestPlugin
#endif // GENERALOPTIONPAGE_H
