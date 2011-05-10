#ifndef TESTRICHEDIT_H
#define TESTRICHEDIT_H

#include <QTextEdit>
#include <vector>

class TestRichEdit : public QTextEdit
{
    Q_OBJECT
public:
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

    explicit TestRichEdit(QWidget *parent = 0);
    /*!
     \brief 给选中的单词设置加粗，如果没选中则设置光标所在位置的单词。

     \param b true是加粗，false是不加粗
    */
    void wordBold(bool b);

    /*!
     \brief 给选中的单词设置倾斜，如果没选中则设置光标所在位置的单词。

     \param b true是倾斜，false是不倾斜
    */
    void wordItalic(bool b);

    /*!
     \brief 给选中的单词设置下划线，如果没选中则设置光标所在位置的单词。

     \param b true是加下划线，false是不加下划线
    */
    void wordUnderline(bool b);

    /*!
     \brief 给选中的文本设置字体，如果没有选中则设置光标所在处得文本。

     \param f 字体名称
    */
    void textFamily(const QString &f);

    /*!
     \brief 给选中的文本设置字体大小，如果没有选中则设置光标所在处的文本。

     \param s 字体大小值
    */
    void textSize(const int &s);

    /*!
     \brief 给选中的字体设置前景色，如果没有选中则设置光标所在处得文本。

     \param c 颜色
    */
    void textColor(const QColor &c);

    /*!
     \brief 给选中的字体设置背景色，如果没有选中则设置光标所在处的文本。

     \param c
    */
    void wordBackgroundColor(const QColor &c);

    /*!
     \brief 设置段落的对齐方式YRichEditor

     \param a 对齐方式
    */
    void alignText(align a);

    /*!
     \brief 插入表格，表格样式使用默认样式

     \param r 表格行数
     \param c 表格列数
     \sa void insertTable(const int &r, const int &c,const int &cs,const int &cp,
                     const YRichEditor::align &a = YRichEditor::Center,
                     const QColor &backGroundColor = QColor(0, 0, 0, 127)),
                     QTextTable * getTalbe()
    */
    void insertTable(const int &r,const int &c);

    /*!
     \brief 插入表格

     \param r 表格行数
     \param c 表格列数
     \param cs 表格那边距
     \param cp 表格外边距
     \param a 对其方式，默认是剧中
     \param backGroundColor 背景颜色
     \sa void insertTable(const int &r,const int &c),QTextTable * getTalbe()
    */
    void insertTable(const int &r, const int &c,const int &cs,const int &cp,
                     const TestRichEdit::align &a = TestRichEdit::Center,
                     const QColor &backGroundColor = QColor(0, 0, 0, 0));

    /*!
     \brief 获取光标所在位置的表格对象

     \return 表格对象
     \sa void insertTable(const int &r,const int &c),
         void insertTable(const int &r, const int &c,const int &cs,const int &cp,
                     const YRichEditor::align &a = YRichEditor::Center,
                     const QColor &backGroundColor = QColor(0, 0, 0, 127))
    */
    QTextTable * getTalbe();

    /*!
     \brief 获取选中的行号集合

     \return 选中的行号集合
    */
    const std::vector<int> getSelectedRowNums();

    /*!
     \brief 获取光标所在处单元格的行号和列号，-1表式光标所在处不存在单元格

     \return 指向的单元格对象
    */
    const TestRichEdit::positionCell getPositionCell();

    /*!
     \brief 获取选中的单元格

     \return 选中的单元格行列，-1表式没有选中
    */
    TestRichEdit::selectedCells getSelectedCells();

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
private:
    /*!
     \brief 合并选中的单词样式，如果没有选中，则合并光标所在位置的单词样式。

     \param format 要合并的单词样式
    */
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
};

#endif // TESTRICHEDIT_H
