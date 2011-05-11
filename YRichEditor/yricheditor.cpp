#include "yricheditor.h"

#include <QTextList>
#include <QTextTableCell>

YRichEditor::YRichEditor(QWidget *parent) :
    QTextEdit(parent)
{
}

void YRichEditor::wordBold(const bool &b)
{
    QTextCharFormat fmt;
    fmt.setFontWeight(b ? QFont::Bold : QFont::Normal);
    this->mergeFormatOnWordOrSelection(fmt);
}

bool YRichEditor::getWordBold()
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

void YRichEditor::wordItalic(const bool &b)
{
    QTextCharFormat fmt;
    fmt.setFontItalic(b);
    this->mergeFormatOnWordOrSelection(fmt);
}

bool YRichEditor::getWordItalic()
{
    QTextCursor cursor = this->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    return cursor.charFormat().fontItalic();
}

void YRichEditor::wordUnderline(const bool &b)
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(b);
    this->mergeFormatOnWordOrSelection(fmt);
}

bool YRichEditor::getWordUnderline()
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

QString YRichEditor::getWordFamily()
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

int YRichEditor::getWordSize()
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

void YRichEditor::textAlign(const align &a)
{
    if (a == Left)
        this->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == Center)
        this->setAlignment(Qt::AlignHCenter);
    else if (a == Right)
        this->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
}

YRichEditor::align YRichEditor::getTextAlign()
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

QTextListFormat::Style YRichEditor::getTextStyle()
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

YRichEditor::positionCell YRichEditor::getPositionCell()
{
    //设置单元格默认值为-1行-1列
    YRichEditor::positionCell pc;
    pc.row = -1;
    pc.column = -1;

    //获取光标所在位置的表格
    QTextCursor cursor = this->textCursor();
    QTextTable * tb = cursor.currentTable();
    if(tb != NULL)
    {
        //获取光标所在位置的单元格
        QTextTableCell tc = tb->cellAt(cursor);

        pc.row = tc.row();
        pc.column = tc.column();
    }

    return pc;
}

YRichEditor::selectedCells YRichEditor::getSelectedCells()
{
    YRichEditor::selectedCells cells;

    //获取选中的单元格
    QTextCursor c = this->textCursor();
    c.selectedTableCells(&cells.firstRow,&cells.numRows,&cells.firstColumn,&cells.numColumns);
    return cells;
}

void YRichEditor::removeRows()
{
    if(this->getTalbe() != NULL)
    {
        QTextCursor cursor = this->textCursor();
        if(cursor.hasSelection())
        {
            //选中的行
            YRichEditor::selectedCells cells = this->getSelectedCells();
            if(cells.firstRow >= 0 && cells.numRows > 0)
            {
                this->getTalbe()->removeRows(cells.firstRow,cells.numRows);
            }
        }
        else
        {
            //光标所在行
            YRichEditor::positionCell cell = this->getPositionCell();
            if(cell.row >= 0)
            {
                this->getTalbe()->removeRows(cell.row,1);
            }
        }
    }
}

void YRichEditor::removeRows(const int &r, const int &num)
{
    if(this->getTalbe() != NULL)
    {
        this->getTalbe()->removeRows(r,num);
    }
}

void YRichEditor::removeColumns()
{
    if(this->getTalbe() != NULL)
    {
        QTextCursor cursor = this->textCursor();
        if(cursor.hasSelection())
        {
            //选中的行
            YRichEditor::selectedCells cells = this->getSelectedCells();
            if(cells.firstColumn >= 0 && cells.numColumns > 0)
            {
                this->getTalbe()->removeColumns(cells.firstColumn,cells.numColumns);
            }
        }
        else
        {
            //光标所在行
            YRichEditor::positionCell cell = this->getPositionCell();
            if(cell.column >= 0)
            {
                this->getTalbe()->removeColumns(cell.column,1);
            }
        }
    }
}

void YRichEditor::removeColumns(const int &c, const int &num)
{
    if(this->getTalbe() != NULL)
    {
        this->getTalbe()->removeColumns(c,num);
    }
}

void YRichEditor::insertRows(const int &r, const int &num, const bool &back)
{
    if(this->getTalbe() != NULL)
    {
        YRichEditor::positionCell cell = this->getPositionCell();
        if(cell.row >= 0 && r >= 0 && r <= cell.row && r > 0)
        {
            if(back)
            {
                this->getTalbe()->insertRows(r + 1,num);
            }
            else
            {
                this->getTalbe()->insertRows(r,num);
            }
        }
    }
}
