#ifndef YRICHEDITOR_H
#define YRICHEDITOR_H

#include <QTextEdit>

/*!
 \brief 富文本编辑控件

*/
class YRichEditor : public QTextEdit
{
    Q_OBJECT

public:
    YRichEditor(QWidget *parent = 0);

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
     \brief 给选中的文本设置加粗，如果没选中则设置光标所在位置的文本。

     \param b true是加粗，false是不加粗
    */
    void wordBold(bool b);

    /*!
     \brief 文本是否加粗

     \return 加粗返回true，否则返回false
    */
    const bool getWordBold();

    /*!
     \brief 给选中的文本设置倾斜，如果没选中则设置光标所在位置的文本。

     \param b true是倾斜，false是不倾斜
     \sa const bool getWordItalic()
    */
    void wordItalic(bool b);

    /*!
     \brief 文本是否倾斜

     \return 倾斜返回true，否则返回false
     \sa void wordItalic(bool b)
    */
    const bool getWordItalic();

    /*!
     \brief 给选中的文本设置下划线，如果没选中则设置光标所在位置的文本。

     \param b true是加下划线，false是不加下划线
     \sa const bool getWordUnderline()
    */
    void wordUnderline(bool b);

    /*!
     \brief 获取文本是否加下划线

     \return 加下划线返回true，否则返回false
     \sa void wordUnderline(bool b)
    */
    const bool getWordUnderline();

    /*!
     \brief 给选中的文本设置字体，如果没有选中则设置光标所在处得文本。

     \param f 字体名称
     \sa const QString getWordFamily()
    */
    void wordFamily(const QString &f);

    /*!
     \brief 获取文本字体

     \return 字体
     \sa void wordFamily(const QString &f)
    */
    const QString getWordFamily();

    /*!
     \brief 给选中的文本设置字体大小，如果没有选中则设置光标所在处的文本。

     \param s 字体大小值
     \sa const int getWordSize()
    */
    void wordSize(const int &s);

    /*!
     \brief 获取文本字体大小

     \return 字体大小
     \sa void wordSize(const int &s)
    */
    const int getWordSize();

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
     \sa const YRichEditor::align getTextAlign()
    */
    void textAlign(const align a);

    /*!
     \brief 获取光标处的文本对齐方式

     \return 文本对齐方式
     \sa void textAlign(const align a)
    */
    const YRichEditor::align getTextAlign();

    /*!
     \brief 设置文本列表样式Qt

     \param f 样式
     \sa const QTextListFormat::Style getTextStyle()
    */
    void textStyle(const QTextListFormat::Style &f);

    /*!
     \brief 获取文本列表样式

     \return 样式
     \sa void textStyle(const QTextListFormat::Style &f)
    */
    const QTextListFormat::Style getTextStyle();

    /*!
     \brief 插入表格

     \param r 表格行数
     \param c 表格列数
     \param cs 表格那边距，默认值是1
     \param cp 表格外边距，默认值是1
     \param a 对其方式，默认是剧中
     \param backGroundColor 背景颜色
     \sa QTextTable * getTalbe()
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
    QTextTable * getTalbe();
private:
    /*!
     \brief 合并选中的文本样式，如果没有选中，则合并光标所在位置的文本样式。

     \param format 要合并的文本样式
    */
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
};

#endif
