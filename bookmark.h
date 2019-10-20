#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QImage>

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
    const int ICON_SIZE = 64;
    const int FONT_SIZE = ICON_SIZE - 10;
    BookmarkManager *_manager;

    QIcon drawIcon() const;
};

} // namespace Internal
} // namespace mefestPlugin

#endif // BOOKMARK_H
