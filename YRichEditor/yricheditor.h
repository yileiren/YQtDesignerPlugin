#ifndef YRICHEDITOR_H
#define YRICHEDITOR_H

#include <QTextEdit>

class YRichEditor : public QTextEdit
{
    Q_OBJECT

public:
    YRichEditor(QWidget *parent = 0);

private:
    /*!
     \brief 合并选中的单词样式，如果没有选中，则合并光标所在位置的单词样式。

     \param format 要合并的单词样式
    */
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
};

#endif
