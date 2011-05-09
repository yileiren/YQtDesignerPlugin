#include "testrichedit.h"

#include <QTextFrame>

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

void TestRichEdit::insertTable(const int &r, const int &c)
{
    //获取光标
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();

    //设置默认格式
    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignHCenter);
    //tableFormat.setBackground(QColor("#e0e0e0"));
    tableFormat.setCellPadding(2);
    tableFormat.setCellSpacing(4);
    tableFormat.setHeaderRowCount(1);

    //设置默认列宽
    QVector<QTextLength> constraints;
    for(int i = 0;i < c;i++)
    {
        constraints << QTextLength(QTextLength::PercentageLength, 100.0 / c);
    }

    tableFormat.setColumnWidthConstraints(constraints);

    //插入表格
    cursor.insertTable(r, c, tableFormat);

    cursor.endEditBlock();
}

void TestRichEdit::insertTable(const int &r, const int &c, const int &cs, const int &cp,
                               const TestRichEdit::align &a,
                               const QColor &backGroundColor)
{
    //获取光标
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();

    //设置默认格式
    QTextTableFormat tableFormat;
    if(a == TestRichEdit::Left)
    {
        tableFormat.setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    }
    else if(a == TestRichEdit::Center)
    {
        tableFormat.setAlignment(Qt::AlignHCenter);
    }
    else
    {
        tableFormat.setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    }
    tableFormat.setBackground(backGroundColor);
    tableFormat.setCellPadding(cp);
    tableFormat.setCellSpacing(cs);

    //设置默认列宽
    QVector<QTextLength> constraints;
    for(int i = 0;i < c;i++)
    {
        constraints << QTextLength(QTextLength::PercentageLength, 100.0 / c);
    }

    tableFormat.setColumnWidthConstraints(constraints);

    //插入表格
    cursor.insertTable(r, c, tableFormat);

    cursor.endEditBlock();
}
