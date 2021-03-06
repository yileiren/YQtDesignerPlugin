#include "testrichedit.h"

#include <QTextFrame>
#include <QTextTableCell>
#include <QTextImageFormat>

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

QTextTable * TestRichEdit::getTable()
{
    QTextCursor cursor = this->textCursor();
    return cursor.currentTable();
}

const std::vector<int> TestRichEdit::getSelectedRowNums()
{
    std::vector<int> selectedRowNums;

    return selectedRowNums;
}

const TestRichEdit::positionCell TestRichEdit::getPositionCell()
{
    //设置单元格默认值为-1行-1列
    TestRichEdit::positionCell pc;
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


TestRichEdit::selectedCells TestRichEdit::getSelectedCells()
{
    TestRichEdit::selectedCells cells;

    //获取选中的单元格
    QTextCursor c = this->textCursor();
    c.selectedTableCells(&cells.firstRow,&cells.numRows,&cells.firstColumn,&cells.numColumns);
    return cells;
}

void TestRichEdit::removeRows()
{
    if(this->getTable() != NULL)
    {
        QTextCursor cursor = this->textCursor();
        if(cursor.hasSelection())
        {
            //选中的行
            TestRichEdit::selectedCells cells = this->getSelectedCells();
            if(cells.firstRow >= 0 && cells.numRows > 0)
            {
                this->getTable()->removeRows(cells.firstRow,cells.numRows);
            }
        }
        else
        {
            //光标所在行
            TestRichEdit::positionCell cell = this->getPositionCell();
            if(cell.row >= 0)
            {
                this->getTable()->removeRows(cell.row,1);
            }
        }
    }
}

void TestRichEdit::removeRows(const int &r, const int &num)
{
    if(this->getTable() != NULL)
    {
        this->getTable()->removeRows(r,num);
    }
}

void TestRichEdit::removeColumns()
{
    if(this->getTable() != NULL)
    {
        QTextCursor cursor = this->textCursor();
        if(cursor.hasSelection())
        {
            //选中的行
            TestRichEdit::selectedCells cells = this->getSelectedCells();
            if(cells.firstColumn >= 0 && cells.numColumns > 0)
            {
                this->getTable()->removeColumns(cells.firstColumn,cells.numColumns);
            }
        }
        else
        {
            //光标所在行
            TestRichEdit::positionCell cell = this->getPositionCell();
            if(cell.column >= 0)
            {
                this->getTable()->removeColumns(cell.column,1);
            }
        }
    }
}

void TestRichEdit::removeColumns(const int &c, const int &num)
{
    if(this->getTable() != NULL)
    {
        this->getTable()->removeColumns(c,num);
    }
}

void TestRichEdit::insertRows(const int &r, const int &num, const bool &back)
{
    if(this->getTable() != NULL)
    {
        TestRichEdit::positionCell cell = this->getPositionCell();
        if(cell.row >= 0 && r >= 0 && r <= cell.row && r > 0)
        {
            if(back)
            {
                this->getTable()->insertRows(r + 1,num);
            }
            else
            {
                this->getTable()->insertRows(r,num);
            }
        }
    }
}

void TestRichEdit::insertColumns(const int &c, const int &num, const bool &back)
{
    if(this->getTable() != NULL)
    {
        TestRichEdit::positionCell cell = this->getPositionCell();
        if(cell.column >= 0 && c >= 0 && c <= cell.column && num > 0)
        {
            //重新设置列宽
            QTextTableFormat f = this->getTable()->format();
            QVector<QTextLength> v = f.columnWidthConstraints();
            QVector<QTextLength> nv;
            for(int i = 0;i < v.count();i++)
            {
                //重新计算列宽
                if(v.at(i).type() == QTextLength::PercentageLength)
                {
                    QTextLength l(QTextLength::PercentageLength,v[i].rawValue() * (100.0 / (v.count() + num) / v[i].rawValue()));
                    nv.push_back(l);
                }
                else
                {
                    nv.push_back(v.at(i));
                }

                if(back && i == c)
                {
                    for(int j = 0;j < num;j++)
                    {
                        QTextLength nl(QTextLength::PercentageLength,100.0 / (v.count() + num));
                        nv.push_back(nl);
                    }
                }
                else if(!back && i + 1 == c)
                {
                    for(int j = 0;j < num;j++)
                    {
                        QTextLength nl(QTextLength::PercentageLength,100.0 / (v.count() + num));
                        nv.push_back(nl);
                    }
                }

            }

            //设置列宽
            f.setColumnWidthConstraints(nv);


            if(back)
            {
                this->getTable()->insertColumns(c + 1,num);
            }
            else
            {
                this->getTable()->insertColumns(c,num);
            }

            this->getTable()->setFormat(f);
        }
    }
}

void TestRichEdit::setColumnsWidth(const int &width, const QTextLength::Type &type)
{
    if(this->getTable() != NULL)
    {
        //获取表格列宽
        QTextTableFormat f = this->getTable()->format();
        QVector<QTextLength> v = f.columnWidthConstraints();

        //新列宽
        QVector<QTextLength> nv;

        //设置列宽
        QTextCursor cursor = this->textCursor();
        if(cursor.hasSelection())
        {
            //选中的列
            TestRichEdit::selectedCells cells = this->getSelectedCells();

            for(int i = 0;i < this->getTable()->columns();i++)
            {
                if(i >= cells.firstColumn && i < (cells.firstColumn + cells.numColumns))
                {
                    QTextLength l(type,width);
                    nv.push_back(l);
                }
                else
                {
                    nv.push_back(v.at(i));
                }
            }
        }
        else
        {
            //光标所在行
            TestRichEdit::positionCell cell = this->getPositionCell();

            for(int i = 0;i < this->getTable()->columns();i++)
            {
                if(i == cell.column)
                {
                    QTextLength l(type,width);
                    nv.push_back(l);
                }
                else
                {
                    nv.push_back(v.at(i));
                }
            }
        }

        //将列宽设置到表格
        f.setColumnWidthConstraints(nv);
        this->getTable()->setFormat(f);
    }
}

QVector<QTextLength> TestRichEdit::getColumnsWidth()
{
    if(this->getTable() != NULL)
    {
        return this->getTable()->format().columnWidthConstraints();
    }
    else
    {
        QVector<QTextLength> v;
        return v;
    }
}

void TestRichEdit::mergeCells()
{
    if(this->getTable() != NULL)
    {
        QTextCursor cursor = this->textCursor();
        if(cursor.hasSelection())
        {
            //选中的列
            TestRichEdit::selectedCells cells = this->getSelectedCells();

            this->getTable()->mergeCells(cells.firstRow,cells.firstColumn,cells.numRows,cells.numColumns);
        }
    }
}

void TestRichEdit::splitCell(const int &r, const int &c, const int &nr, const int &nc)
{
    if(this->getTable() != NULL)
    {
        this->getTable()->splitCell(r,c,nr,nc);
    }
}

void TestRichEdit::setTableCellsPadding(const int &p)
{
    if(this->getTable() != NULL)
    {
        if(p >= 0)
        {
            QTextTableFormat f = this->getTable()->format();
            f.setCellPadding(p);
            this->getTable()->setFormat(f);
        }
    }
}

void TestRichEdit::setTableCellsSpacing(const int &s)
{
    if(this->getTable() != NULL)
    {
        if(s >= 0)
        {
            QTextTableFormat f = this->getTable()->format();
            f.setCellSpacing(s);
            this->getTable()->setFormat(f);
        }
    }
}

int TestRichEdit::getTableCellsPadding()
{
    if(this->getTable() != NULL)
    {
        QTextTableFormat f = this->getTable()->format();
        return f.cellPadding();
    }
    else
    {
        return -1;
    }
}

int TestRichEdit::getTableCellsSpacing()
{
    if(this->getTable() != NULL)
    {
        QTextTableFormat f = this->getTable()->format();
        return f.cellSpacing();
    }
    else
    {
        return -1;
    }
}

void TestRichEdit::setTableBackGroundColor(const QColor &c)
{
    if(this->getTable() != NULL)
    {
        QTextTableFormat f = this->getTable()->format();
        f.setBackground(c);
        this->getTable()->setFormat(f);
    }
}

const QColor & TestRichEdit::getTableBackGroundColor()
{
    if(this->getTable() != NULL)
    {
        return this->getTable()->format().background().color();
    }
    else
    {
        QTextCursor cursor = this->textCursor();
        return cursor.charFormat().background().color();
    }
}

void TestRichEdit::setTableCellsBackGroundColor(const QColor &c)
{
    if(this->getTable() != NULL)
    {
        //设置格式
        QTextCharFormat f;
        f.setBackground(c);

        QTextCursor cursor = this->textCursor();
        if(cursor.hasSelection())
        {
            //选中的单元格
            TestRichEdit::selectedCells cells = this->getSelectedCells();
            if(cells.firstColumn >= 0 && cells.numColumns > 0 && cells.firstRow >= 0 && cells.numRows > 0)
            {
                for(int i = cells.firstColumn;i < (cells.firstColumn + cells.numColumns);i++)
                {
                    for(int j = cells.firstRow;j < (cells.firstRow + cells.numRows);j++)
                    {
                        this->getTable()->cellAt(j,i).setFormat(f);
                    }
                }
            }
        }
        else
        {
            //光标所在单元格
            TestRichEdit::positionCell cell = this->getPositionCell();
            if(cell.column >= 0 && cell.row >= 0)
            {
                this->getTable()->cellAt(cell.row,cell.column).setFormat(f);
            }
        }
    }
}

const QColor & TestRichEdit::getTableCellBackGroundColor()
{
    if(this->getTable() != NULL)
    {
        //光标所在单元格
        TestRichEdit::positionCell cell = this->getPositionCell();
        if(cell.row >= 0 && cell.column >= 0)
        {
            return this->getTable()->cellAt(cell.row,cell.column).format().background().color();
        }
        else
        {
            QTextCursor cursor = this->textCursor();
            return cursor.charFormat().background().color();
        }
    }
    else
    {
        QTextCursor cursor = this->textCursor();
        return cursor.charFormat().background().color();
    }
}

void TestRichEdit::setTableAlign(const align &a)
{
    if(this->getTable() != NULL)
    {
        //获取表格当前格式
        QTextTableFormat f = this->getTable()->format();

        //设置对其方式
        if (a == Left)
            f.setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
        else if (a == Center)
            f.setAlignment(Qt::AlignHCenter);
        else
            f.setAlignment(Qt::AlignRight | Qt::AlignAbsolute);

        //将格式设置到表格
        this->getTable()->setFormat(f);
    }
}

TestRichEdit::align TestRichEdit::getTableAlign()
{
    if(this->getTable() != NULL)
    {
        //获取表格当前对齐方式
        Qt::Alignment al = this->getTable()->format().alignment();

        //设置对其方式
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
    else
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
}

void TestRichEdit::insertImage(const QString &image)
{
    this->textCursor().insertImage(image);
}
