#include "yricheditor.h"

YRichEditor::YRichEditor(QWidget *parent) :
    QTextEdit(parent)
{
}

void YRichEditor::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = this->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    this->mergeCurrentCharFormat(format);
}
