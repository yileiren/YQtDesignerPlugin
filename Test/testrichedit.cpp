#include "testrichedit.h"

TestRichEdit::TestRichEdit(QWidget *parent) :
    QTextEdit(parent)
{
}

void TestRichEdit::wordBold(bool b)
{
    QTextCharFormat fmt;
    fmt.setFontWeight(b ? QFont::Bold : QFont::Normal);
    this->mergeFormatOnWordOrSelection(fmt);
}

void TestRichEdit::wordItalic(bool b)
{
    QTextCharFormat fmt;
    fmt.setFontItalic(b);
    this->mergeFormatOnWordOrSelection(fmt);
}

void TestRichEdit::wordUnderline(bool b)
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(b);
    this->mergeFormatOnWordOrSelection(fmt);
}

void TestRichEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = this->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    this->mergeCurrentCharFormat(format);
}

void TestRichEdit::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    this->mergeFormatOnWordOrSelection(fmt);
}

void TestRichEdit::textSize(const int &s)
{
    if (s > 0)
    {
        QTextCharFormat fmt;
        fmt.setFontPointSize(s);
        this->mergeFormatOnWordOrSelection(fmt);
    }
}

void TestRichEdit::textColor(const QColor &c)
{
    if (!c.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(c);
    this->mergeFormatOnWordOrSelection(fmt);
}

void TestRichEdit::wordBackgroundColor(const QColor &c)
{
    if (!c.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setBackground(c);
    this->mergeFormatOnWordOrSelection(fmt);
}

void TestRichEdit::alignText(align a)
{
    if (a == Left)
        this->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == Center)
        this->setAlignment(Qt::AlignHCenter);
    else if (a == Right)
        this->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
}
