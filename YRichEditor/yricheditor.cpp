#include "yricheditor.h"

#include <QTextList>

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

const bool YRichEditor::getWordBold()
{
    QTextCursor cursor = this->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    const int f = cursor.charFormat().fontWeight();

    if(f == QFont::Bold)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void YRichEditor::wordItalic(bool b)
{
    QTextCharFormat fmt;
    fmt.setFontItalic(b);
    this->mergeFormatOnWordOrSelection(fmt);
}

const bool YRichEditor::getWordItalic()
{
    QTextCursor cursor = this->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    return cursor.charFormat().fontItalic();
}

void YRichEditor::wordUnderline(bool b)
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(b);
    this->mergeFormatOnWordOrSelection(fmt);
}

const bool YRichEditor::getWordUnderline()
{
    QTextCursor cursor = this->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    return cursor.charFormat().fontUnderline();
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

const QString YRichEditor::getWordFamily()
{
    QTextCursor cursor = this->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    return cursor.charFormat().fontFamily();
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

const int YRichEditor::getWordSize()
{
    QTextCursor cursor = this->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    return cursor.charFormat().font().pointSize();
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

const QColor & YRichEditor::getWordBackgroundColor()
{
    QTextCursor cursor = this->textCursor();
    return cursor.charFormat().background().color();
}

void YRichEditor::textAlign(const align a)
{
    if (a == Left)
        this->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == Center)
        this->setAlignment(Qt::AlignHCenter);
    else if (a == Right)
        this->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
}

const YRichEditor::align YRichEditor::getTextAlign()
{
    Qt::Alignment al = this->alignment();
    if (al & Qt::AlignLeft)
    {
        return Left;
    }
    else if (al & Qt::AlignHCenter)
    {
        return Center;
    }
    else
    {
        return Right;
    }
}

const QColor & YRichEditor::getWordColor()
{
    QTextCursor cursor = this->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    return cursor.charFormat().foreground().color();
}

void YRichEditor::textStyle(const QTextListFormat::Style &f)
{
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();

    QTextListFormat listFmt;

    if (cursor.currentList())
    {
        listFmt = cursor.currentList()->format();
    }
    else
    {
        listFmt.setIndent(blockFmt.indent() + 1);
        blockFmt.setIndent(0);
        cursor.setBlockFormat(blockFmt);
    }

    listFmt.setStyle(f);

    cursor.createList(listFmt);

    cursor.endEditBlock();
}

const QTextListFormat::Style YRichEditor::getTextStyle()
{
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();

    if (cursor.currentList())
    {
        return cursor.currentList()->format().style();
    }
    else
    {
        return QTextListFormat::ListStyleUndefined;
    }
}

void YRichEditor::insertTable(const int &r, const int &c, const int &cs, const int &cp,
                               const YRichEditor::align &a,
                               const QColor &backGroundColor)
{
    //获取光标
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();

    //设置默认格式
    QTextTableFormat tableFormat;
    if(a == YRichEditor::Left)
    {
        tableFormat.setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    }
    else if(a == YRichEditor::Center)
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

QTextTable * YRichEditor::getTalbe()
{
    QTextCursor cursor = this->textCursor();
    return cursor.currentTable();
}

