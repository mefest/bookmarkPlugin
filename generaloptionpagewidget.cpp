#include "generaloptionpagewidget.h"

#include "mefestpluginconstants.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
namespace mefestPlugin {
GeneralOptionPageWidget::GeneralOptionPageWidget(QWidget *parent)
    : QWidget(parent)
{
    generateUi();
}

void GeneralOptionPageWidget::generateUi()
{
    auto mainLayout = new QHBoxLayout(this);
    auto leftLayout = new QVBoxLayout();
    auto rightLayout = new QVBoxLayout();
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    this->setLayout(mainLayout);

    _listSetSeqEditor.reserve(Constants::NUMBER_MARKS);
    _listGetSeqEditor.reserve(Constants::NUMBER_MARKS);

    for (int i = 0; i < Constants::NUMBER_MARKS; ++i) {
        auto row = new QHBoxLayout();
        auto label = new QLabel("Установить метку " + QString::number(i + 1), this);
        auto editor = new QKeySequenceEdit(this);
        connect(editor,
                &QKeySequenceEdit::keySequenceChanged,
                this,
                [this]([[maybe_unused]] const QKeySequence &seq) {
                    this->_changed = true;
                });
        row->addWidget(label);
        row->addWidget(editor);
        leftLayout->addLayout(row);

        _listSetSeqEditor.append(editor);
    }

    for (int i = 0; i < Constants::NUMBER_MARKS; ++i) {
        auto row = new QHBoxLayout();
        auto label = new QLabel("Перейти к метке " + QString::number(i + 1), this);
        auto editor = new QKeySequenceEdit(this);
        connect(editor,
                &QKeySequenceEdit::keySequenceChanged,
                this,
                [this]([[maybe_unused]] const QKeySequence &seq) {
                    this->_changed = true;
                });
        row->addWidget(label);
        row->addWidget(editor);
        rightLayout->addLayout(row);

        _listGetSeqEditor.append(editor);
    }
}

bool GeneralOptionPageWidget::isChanged() const
{
    return _changed;
}

void GeneralOptionPageWidget::setSeqSetMark(const QVector<QKeySequence> &keySeq)
{
    for (int i = 0; i < keySeq.size(); ++i) {
        _listSetSeqEditor[i]->setKeySequence(keySeq[i]);
    }
}

void GeneralOptionPageWidget::setSeqGetMark(const QVector<QKeySequence> &keySeq)
{
    for (int i = 0; i < keySeq.size(); ++i) {
        _listGetSeqEditor[i]->setKeySequence(keySeq[i]);
    }
}

void GeneralOptionPageWidget::reset()
{
    _changed = false;
}

QVector<QKeySequence> GeneralOptionPageWidget::getSeqSetMark() const
{
    QVector<QKeySequence> result;
    result.reserve(Constants::NUMBER_MARKS);
    for (auto &seq : _listSetSeqEditor) {
        result.push_back(seq->keySequence());
    }
    return result;
}

QVector<QKeySequence> GeneralOptionPageWidget::getSeqGetMark() const
{
    QVector<QKeySequence> result;
    result.reserve(Constants::NUMBER_MARKS);
    for (auto &seq : _listGetSeqEditor) {
        result.push_back(seq->keySequence());
    }
    return result;
}
GeneralOptionPageWidget::~GeneralOptionPageWidget()
{
}
} // namespace mefestPlugin
