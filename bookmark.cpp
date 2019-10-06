#include "bookmark.h"
#include "utils.h"

namespace mefestPlugin {
namespace Internal {

Bookmark::Bookmark(int num,
                   const ::Utils::FilePath &fileName,
                   int lineNumber,
                   Core::Id category,
                   double widthFactor)
    : _number(num)
    , TextEditor::TextMark(fileName, lineNumber, category, widthFactor)
{
    setIcon(Utils::getBookmarkIcon(num + 1));
}

void Bookmark::removedFromEditor()
{
    if (_manager->isExistBookmark(_number)) {
        _manager->removeBookmark(_number);
    }
}

void Bookmark::setManager(BookmarkManager *manager)
{
    _manager = manager;
}

} // namespace Internal
} // namespace mefestPlugin
