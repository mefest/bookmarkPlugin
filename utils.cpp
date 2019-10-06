#include "coreplugin/icore.h"

#include "mefestpluginconstants.h"
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QSettings>

namespace mefestPlugin {
namespace Internal {
namespace Utils {

QVector<QKeySequence> getFromSettingKeySeqSetMarks()
{
    QVector<QKeySequence> listSetMarksSeqKey;
    listSetMarksSeqKey.reserve(Constants::NUMBER_MARKS);
    QSettings *settings = Core::ICore::instance()->settings();
    settings->beginGroup(Constants::PLUGIN_NAME);
    settings->beginGroup(Constants::OPTION_NAME);
    for (int i = 0; i < Constants::NUMBER_MARKS; ++i) {
        QString valueName = "setPosition_" + QString::number(i);
        QKeySequence keySeq = QKeySequence::fromString(settings->value(valueName).toString());
        listSetMarksSeqKey.append(keySeq);
    }
    settings->endGroup();
    settings->endGroup();
    return listSetMarksSeqKey;
}

QVector<QKeySequence> getFromSettingKeySeqGetMarks()
{
    QVector<QKeySequence> listGetMarksSeqKey;
    listGetMarksSeqKey.reserve(Constants::NUMBER_MARKS);
    QSettings *settings = Core::ICore::instance()->settings();
    settings->beginGroup(Constants::PLUGIN_NAME);
    settings->beginGroup(Constants::OPTION_NAME);
    for (int i = 0; i < Constants::NUMBER_MARKS; ++i) {
        QString valueName = "getPosition_" + QString::number(i);
        QKeySequence keySeq = QKeySequence::fromString(settings->value(valueName).toString());
        listGetMarksSeqKey.append(keySeq);
    }
    settings->endGroup();
    settings->endGroup();
    return listGetMarksSeqKey;
}

QIcon getBookmarkIcon(int num, int size)
{
    QIcon result;
    auto pix = new QPixmap(size, size);
    auto paint = new QPainter(pix);

    paint->setRenderHint(QPainter::Antialiasing, false);

    paint->fillRect(0, 0, size, size, QColor(100, 100, 100));
    paint->setPen(QColor(255, 255, 255));
    paint->setBrush(Qt::NoBrush);
    QFont sansFont("Helvetica [Cronyx]", size - 20);
    paint->setFont(sansFont);
    paint->drawRect(0, 0, size - 1, size - 1);
    paint->drawText(0, 0, size - 1, size - 1, Qt::AlignCenter, QString::number(num));

    result.addPixmap(*pix);

    return result;
}

} // namespace Utils
} // namespace Internal
} // namespace mefestPlugin
#include "utils.h"
