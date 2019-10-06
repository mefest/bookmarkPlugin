#ifndef BOOKMARKMANAGER_H
#define BOOKMARKMANAGER_H

#include "bookmark.h"

#include <utils/fileutils.h>
#include <QVector>

namespace mefestPlugin {
namespace Internal {

class Bookmark;
class BookmarkManager
{
public:
    BookmarkManager();

    bool removeBookmark(int num);
    bool addBookmark(int num, Bookmark *mark);
    Bookmark *createBookmark(int num, Utils::FilePath path, int line);
    bool isExistBookmark(int num) const;
    Bookmark *getBookmark(int num) const;
    void toogleBookmark(int num, Utils::FilePath path, int line);

private:
    QVector<Bookmark *> _listBookmark;
};

} // namespace Internal
} // namespace mefestPlugin

#endif // BOOKMARKMANAGER_H
