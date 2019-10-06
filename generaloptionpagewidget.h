#ifndef GENERALOPTIONPAGEWIDGET_H
#define GENERALOPTIONPAGEWIDGET_H

#include <QKeySequenceEdit>
#include <QVector>
#include <QWidget>
namespace mefestPlugin {

class GeneralOptionPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralOptionPageWidget(QWidget *parent = nullptr);
    ~GeneralOptionPageWidget();

    bool isChanged() const;
    QVector<QKeySequence> getSeqSetMark() const;
    QVector<QKeySequence> getSeqGetMark() const;

    void setSeqSetMark(const QVector<QKeySequence> &keySeq);
    void setSeqGetMark(const QVector<QKeySequence> &keySeq);
    void reset();
signals:
    void changed();

private:
    QVector<QKeySequenceEdit *> _listSetSeqEditor;
    QVector<QKeySequenceEdit *> _listGetSeqEditor;
    void generateUi();
    bool _changed = false;
};
} // namespace mefestPlugin
#endif // GENERALOPTIONPAGEWIDGET_H
