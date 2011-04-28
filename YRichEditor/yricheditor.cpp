#include "yricheditor.h"

YRichEditor::YRichEditor(QWidget *parent) :
    QTextEdit(parent)
{
}

void YRichEditor::wordBold(bool b)
{
    QTextCharFormat fmt;
    fmt.setFontWeight(b ? QFont::Bold : QFont::Normal);
    this->mergeFormatOnWordOrSelection(fmt);
}

void YRichEditor::wordItalic(bool b)
{
    QTextCharFormat fmt;
    fmt.setFontItalic(b);
    this->mergeFormatOnWordOrSelection(fmt);
}

void YRichEditor::wordUnderline(bool b)
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(b);
    this->mergeFormatOnWordOrSelection(fmt);
}

void YRichEditor::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = this->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    this->mergeCurrentCharFormat(format);
}

void YRichEditor::wordFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    this->mergeFormatOnWordOrSelection(fmt);
}

void YRichEditor::wordSize(const int &s)
{
    if (s > 0)
    {
        QTextCharFormat fmt;
        fmt.setFontPointSize(s);
        this->mergeFormatOnWordOrSelection(fmt);
    }
}

void YRichEditor::wordColor(const QColor &c)
{
    if (!c.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(c);
    this->mergeFormatOnWordOrSelection(fmt);
}

void YRichEditor::wordBackgroundColor(const QColor &c)
{
    if (!c.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setBackground(c);
    this->mergeFormatOnWordOrSelection(fmt);
}
