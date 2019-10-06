#include "bookmarkmanager.h"
#include "mefestpluginconstants.h"

#include <QtDebug>

namespace mefestPlugin {
namespace Internal {
BookmarkManager::BookmarkManager()
{
    _listBookmark.fill(nullptr, Constants::NUMBER_MARKS);
}

bool BookmarkManager::removeBookmark(int num)
{
    if (_listBookmark[num] != nullptr) {
        delete _listBookmark[num];
        _listBookmark[num] = nullptr;
        return true;
    }
    return false;
}

bool BookmarkManager::addBookmark(int num, Bookmark *mark)
{
    qDebug() << "add bookmark num:" << num;
    if (_listBookmark[num] == nullptr) {
        _listBookmark[num] = mark;
        return true;
    }
    return false;
}

Bookmark *BookmarkManager::createBookmark(int num, Utils::FilePath path, int line)
{
    qDebug() << "create bookmark num:" << num;
    auto mark = new Bookmark(num, path, line, Core::Id("Bookmark"));
    mark->setManager(this);
    if (addBookmark(num, mark)) {
        return mark;
    }
    return nullptr;
}

bool BookmarkManager::isExistBookmark(int num) const
{
    qDebug() << "exist bookmark num:" << num << (_listBookmark[num] != nullptr);
    return _listBookmark[num] != nullptr;
}

Bookmark *BookmarkManager::getBookmark(int num) const
{
    if (isExistBookmark(num)) {
        return _listBookmark[num];
    }
    return nullptr;
}

void BookmarkManager::toogleBookmark(int num, Utils::FilePath path, int line)
{
    qDebug() << "size marks" << _listBookmark.size();
    for (int i = 0; i < _listBookmark.size(); ++i) {
        if (isExistBookmark(i)) {
            qDebug() << "match mark" << _listBookmark[i]->fileName()
                     << _listBookmark[i]->lineNumber();

            if (_listBookmark[i]->fileName() == path && _listBookmark[i]->lineNumber() == line) {
                removeBookmark(i);
            }
        }
    }

    if (isExistBookmark(num)) {
        removeBookmark(num);
    }

    createBookmark(num, path, line);
}

} // namespace Internal
} // namespace mefestPlugin
