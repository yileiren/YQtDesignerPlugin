#ifndef YRICHEDITOR_H
#define YRICHEDITOR_H

#include <QTextEdit>
#include <QtDesigner/QDesignerExportWidget>

/*!
 \brief 富文本编辑控件

*/
class QDESIGNER_WIDGET_EXPORT YRichEditor : public QTextEdit
{
    Q_OBJECT

public:
    explicit YRichEditor(QWidget *parent = 0);

    /*!
     \brief 文本对齐方式

    */
    enum align
    {
        Left, /*!< 左对齐 */
        Right, /*!< 右对齐 */
        Center /*!< 居中对齐 */
    };

    /*!
     \brief 光标所在的单元格行号和列号

    */
    struct positionCell
    {
        int row;  /*!< 行号 */
        int column; /*!< 列号 */
    };

    /*!
     \brief 选中的单元格

    */
    struct selectedCells
    {
        int firstRow; /*!< 选中的单元格第一行行号 */
        int numRows; /*!< 选中的行数 */
        int firstColumn; /*!< 选中的单元格第一列列号 */
        int numColumns; /*!< 选中的列数 */
    };

    /*!
     \brief 给选中的文本设置加粗，如果没选中则设置光标所在位置的文本。

     \param b true是加粗，false是不加粗
     \sa bool getWordBold()
    */
    void wordBold(const bool &b);

    /*!
     \brief 文本是否加粗

     \return 加粗返回true，否则返回false
     \sa void wordBold(const bool &b)
    */
    bool getWordBold();

    /*!
     \brief 给选中的文本设置倾斜，如果没选中则设置光标所在位置的文本。

     \param b true是倾斜，false是不倾斜
     \sa bool getWordItalic()
    */
    void wordItalic(const bool &b);

    /*!
     \brief 文本是否倾斜

     \return 倾斜返回true，否则返回false
     \sa void wordItalic(const bool &b)
    */
    bool getWordItalic();

    /*!
     \brief 给选中的文本设置下划线，如果没选中则设置光标所在位置的文本。

     \param b true是加下划线，false是不加下划线
     \sa const bool getWordUnderline()
    */
    void wordUnderline(const bool &b);

    /*!
     \brief 获取文本是否加下划线

     \return 加下划线返回true，否则返回false
     \sa void wordUnderline(bool b)
    */
    bool getWordUnderline();

    /*!
     \brief 给选中的文本设置字体，如果没有选中则设置光标所在处得文本。

     \param f 字体名称
     \sa QString getWordFamily()
    */
    void wordFamily(const QString &f);

    /*!
     \brief 获取文本字体

     \return 字体
     \sa void wordFamily(const QString &f)
    */
    QString getWordFamily();

    /*!
     \brief 给选中的文本设置字体大小，如果没有选中则设置光标所在处的文本。

     \param s 字体大小值
     \sa int getWordSize()
    */
    void wordSize(const int &s);

    /*!
     \brief 获取文本字体大小

     \return 字体大小
     \sa void wordSize(const int &s)
    */
    int getWordSize();

    /*!
     \brief 给选中的字体设置前景色，如果没有选中则设置光标所在处得文本。

     \param c 颜色
     \sa const QColor & getWordColor()
    */
    void wordColor(const QColor &c);

    /*!
     \brief 获取文本前景色

     \return 前景色
     \sa void wordColor(const QColor &c)
    */
    const QColor & getWordColor();

    /*!
     \brief 给选中的字体设置背景色，如果没有选中则设置光标所在处的文本。

     \param c 背景色
     \sa const QColor & getWordBackgroundColor()
    */
    void wordBackgroundColor(const QColor &c);

    /*!
     \brief 获取文字背景色

     \return 背景色
     \sa void wordBackgroundColor(const QColor &c)
    */
    const QColor & getWordBackgroundColor();

    /*!
     \brief 设置段落的对齐方式

     \param a 对齐方式
     \sa YRichEditor::align getTextAlign()
    */
    void textAlign(const align &a);

    /*!
     \brief 获取光标处的文本对齐方式

     \return 文本对齐方式
     \sa void textAlign(const align &a)
    */
    YRichEditor::align getTextAlign();

    /*!
     \brief 设置文本列表样式Qt

     \param f 样式
     \sa QTextListFormat::Style getTextStyle()
    */
    void textStyle(const QTextListFormat::Style &f);

    /*!
     \brief 获取文本列表样式

     \return 样式
     \sa void textStyle(const QTextListFormat::Style &f)
    */
    QTextListFormat::Style getTextStyle();

    /*!
     \brief 插入表格

     \param r 表格行数
     \param c 表格列数
     \param cs 表格那边距，默认值是1
     \param cp 表格外边距，默认值是1
     \param a 对其方式，默认是剧中
     \param backGroundColor 背景颜色
     \sa QTextTable * getTable()
    */
    void insertTable(const int &r, const int &c,const int &cs = 1,const int &cp = 1,
                     const YRichEditor::align &a = YRichEditor::Center,
                     const QColor &backGroundColor = QColor(0, 0, 0, 0));

    /*!
     \brief 获取光标所在位置的表格对象

     \return 表格对象
     \sa void insertTable(const int &r, const int &c,const int &cs = 1,const int &cp = 1,
                     const YRichEditor::align &a = YRichEditor::Center,
                     const QColor &backGroundColor = QColor(0, 0, 0, 0))
    */
    QTextTable * getTable();

    /*!
     \brief 获取光标所在处单元格的行号和列号，-1表式光标所在处不存在单元格

     \return 指向的单元格对象
    */
    YRichEditor::positionCell getPositionCell();

    /*!
     \brief 获取选中的单元格

     \return 选中的单元格行列，-1表式没有选中
    */
    YRichEditor::selectedCells getSelectedCells();

    /*!
     \brief 移除光标所在处或选中的行

     \sa void removeRows(const int &r,const int &num)
    */
    void removeRows();

    /*!
     \brief 移除光标所在处表格的指定行

     \param r 开始的行号（从0开始）
     \param num 行数
     \sa void removeRows()
    */
    void removeRows(const int &r,const int &num);

    /*!
     \brief 在表格中插入行

     \param r 行号
     \param num 行数
     \param back 是否在行后插入，true是再后面插，false是在前面插
     \sa void removeRows(),void removeRows(const int &r,const int &num),
         void insertColumns(const int &c,const int &num,const bool &back = true)
    */
    void insertRows(const int &r,const int &num,const bool &back = true);

    /*!
     \brief 移除光标所在处或选中的列

     \sa void removeColumns(const int &c,const int &num),void removeRows(),void removeRows(const int &r,const int &num)
    */
    void removeColumns();

    /*!
     \brief 移除光标所在处表格的指定列

     \param c 开始的列号（从0开始）
     \param num 列数
     \sa void removeColumns(),void removeRows(),void removeRows(const int &r,const int &num)
    */
    void removeColumns(const int &c,const int &num);

    /*!
     \brief 在表格中插入列

     \param c 列号
     \param num 列数
     \param back 是否在后面插入，true是在后面，false是在前面
     \sa void removeColumns(),void removeColumns(const int &c,const int &num),
         void insertRows(const int &r,const int &num,const bool &back = true)
    */
    void insertColumns(const int &c,const int &num,const bool &back = true);

    /*!
     \brief 设置选中列的列宽

     \param width 宽度值
     \param type 数值类型
     \sa QVector<QTextLength> getColumnsWidth()
    */
    void setColumnsWidth(const int &width,const QTextLength::Type &type);

    /*!
     \brief 获取列宽

     \return 列宽向量
     \sa void setColumnsWidth(const int &width,const QTextLength::Type &type)
    */
    QVector<QTextLength> getColumnsWidth();

    /*!
     \brief 合并选中的单元格

     \sa void splitCell(const int &r,const int &c,const int &nr,const int &nc)
    */
    void mergeCells();

    /*!
     \brief 拆分指定的单元格，被拆分的单元格应当是合并过的单元格

     \param r 起始行号
     \param c 起始列号
     \param nr 拆分行数
     \param nc 拆分列数
     \sa void mergeCells()
    */
    void splitCell(const int &r,const int &c,const int &nr,const int &nc);

    /*!
     \brief 设置单元格内间距

     \param p 间距
     \sa int getTableCellsPadding(),void setTableCellsSpacing(const int &s),int getTableCellsSpacing()
    */
    void setTableCellsPadding(const int &p);

    /*!
     \brief 获取单元格内间距，如果没有选中表格返回-1

     \return 间距
     \sa void setTableCellsPadding(const int &p),void setTableCellsSpacing(const int &s),int getTableCellsSpacing()
    */
    int getTableCellsPadding();

    /*!
     \brief 设置单元格外间距

     \param s 间距
     \sa int getTableCellsSpacing(),int getTableCellsPadding(),void setTableCellsPadding(const int &p)
    */
    void setTableCellsSpacing(const int &s);

    /*!
     \brief 获取单元格外间距，如果没有选中表格返回-1

     \return 间距
     \sa void setTableCellsSpacing(const int &s),int getTableCellsPadding(),void setTableCellsPadding(const int &p)
    */
    int getTableCellsSpacing();

    /*!
     \brief 设置表格背景色

     \param c 背景色
     \sa const QColor & getTableBackGroundColor()
    */
    void setTableBackGroundColor(const QColor &c);

    /*!
     \brief 获取表格背景色

     \return 背景色
     \sa void setTableBackGroundColor(const QColor &c)
    */
    const QColor & getTableBackGroundColor();

    /*!
     \brief 设置选中单元格的背景色，如果没有选中的单元格，设置光标所在位置

     \param c 颜色
     \sa const QColor & getTableCellBackGroundColor()
    */
    void setTableCellsBackGroundColor(const QColor &c);

    /*!
     \brief 获取光标所在位置的单元格背景色

     \return 颜色
     \sa void setTableCellsBackGroundColor(const QColor &c)
    */
    const QColor & getTableCellBackGroundColor();

    /*!
     \brief 设置表格对齐方式

     \param a 对齐方式
     \sa align getTableAlign()
    */
    void setTableAlign(const align &a);

    /*!
     \brief 获取表格对齐方式

     \return 对齐方式
     \sa void setTableAlign(const align &a)
    */
    align getTableAlign();

    /*!
     \brief 在光标位置插入图片

     \param image 图片路径
    */
    void insertImage(const QString &image);
private:
    /*!
     \brief 合并选中的文本样式，如果没有选中，则合并光标所在位置的文本样式。

     \param format 要合并的文本样式
    */
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
};

#endif
