#ifndef UTILS_H
#define UTILS_H
#include <QIcon>
#include <QKeySequence>
#include <QVector>

namespace mefestPlugin {
namespace Internal {
namespace Utils {
QVector<QKeySequence> getFromSettingKeySeqSetMarks();
QVector<QKeySequence> getFromSettingKeySeqGetMarks();

} // namespace Utils
} // namespace Internal
} // namespace mefestPlugin

#endif // UTILS_H
