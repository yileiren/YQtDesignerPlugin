#ifndef YRICHEDITOR_H
#define YRICHEDITOR_H

#include <QTextEdit>

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
    void wordFamily(const QString &f);

    /*!
     \brief 给选中的文本设置字体大小，如果没有选中则设置光标所在处的文本。

     \param s 字体大小值
    */
    void wordSize(const int &s);

    /*!
     \brief 给选中的字体设置前景色，如果没有选中则设置光标所在处得文本。

     \param c 颜色
    */
    void wordColor(const QColor &c);

    /*!
     \brief 给选中的字体设置背景色，如果没有选中则设置光标所在处的文本。

     \param c
    */
    void wordBackgroundColor(const QColor &c);

    /*!
     \brief 设置段落的对齐方式

     \param a 对齐方式
    */
    void alignText(align a);
private:
    /*!
     \brief 合并选中的单词样式，如果没有选中，则合并光标所在位置的单词样式。

     \param format 要合并的单词样式
    */
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
};

#endif
