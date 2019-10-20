#include "bookmark.h"
#include "utils.h"

#include <QPainter>
#include <QPixmap>

namespace mefestPlugin {
namespace Internal {

Bookmark::Bookmark(int num,
                   const ::Utils::FilePath &fileName,
                   int lineNumber,
                   Core::Id category,
                   double widthFactor)
    : TextEditor::TextMark(fileName, lineNumber, category, widthFactor)
    , _number(num)
{
    setIcon(drawIcon());
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

QIcon Bookmark::drawIcon() const
{
    QIcon result;
    auto pix = new QPixmap(ICON_SIZE, ICON_SIZE);
    auto paint = new QPainter(pix);

    paint->setRenderHint(QPainter::Antialiasing, false);

    paint->fillRect(0, 0, ICON_SIZE, ICON_SIZE, Qt::darkGray);
    paint->setPen(Qt::white);
    paint->setBrush(Qt::NoBrush);
    QFont sansFont("Helvetica [Cronyx]", FONT_SIZE);
    paint->setFont(sansFont);
    paint->drawRect(0, 0, ICON_SIZE - 1, ICON_SIZE - 1);
    paint->drawText(0,
                    0,
                    ICON_SIZE - 1,
                    ICON_SIZE - 1,
                    Qt::AlignCenter,
                    QString::number(_number + 1));

    result.addPixmap(*pix);

    return result;
}

} // namespace Internal
} // namespace mefestPlugin
