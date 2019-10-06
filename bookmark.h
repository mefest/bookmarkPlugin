#ifndef BOOKMARK_H
#define BOOKMARK_H

#include "bookmarkmanager.h"
#include <texteditor/textmark.h>
#include <utils/fileutils.h>

namespace mefestPlugin {
namespace Internal {
class BookmarkManager;
class Bookmark : public TextEditor::TextMark
{
public:
    Bookmark(int num,
             const ::Utils::FilePath &fileName,
             int lineNumber,
             Core::Id category,
             double widthFactor = 1.0);

    void removedFromEditor() override;
    void setManager(BookmarkManager *manager);

private:
    int _number = 0;
    BookmarkManager *_manager;
};

} // namespace Internal
} // namespace mefestPlugin

#endif // BOOKMARK_H
