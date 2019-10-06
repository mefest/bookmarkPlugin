#ifndef MEFESTPLUGIN_CONSTANTS_H
#define MEFESTPLUGIN_CONSTANTS_H

namespace mefestPlugin {
namespace Constants {

const char ACTION_ID[] = "mefestPlugin.Action";
const char ACTION_BOOKMARK_TOGGLE[] = "mefestPlugin.Mark.Toggle";
const char ACTION_BOOKMARK_GO[] = "mefestPlugin.Mark.Go";
const char MENU_ID[] = "mefestPlugin.Menu";

const char PLUGIN_NAME[] = "MefPlugin";

const char OPTION_NAME[] = "Marks";
const char OPTION_NAME_TR[] = QT_TRANSLATE_NOOP("Marks", "Метки");
const size_t NUMBER_MARKS = 9;

const char OPTIONSPAGE_CATEGORY[] = "C.TextEditor";
const char OPTIONSPAGE_CATEGORY_TR_CATEGORY[] = QT_TRANSLATE_NOOP("Text Editor", "Text Editor");

} // namespace mefestPlugin
} // namespace Constants

#endif // MEFESTPLUGIN_CONSTANTS_H
