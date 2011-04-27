#ifndef YRICHEDITOR_H
#define YRICHEDITOR_H

#include <QTextEdit>

class YRichEditor : public QTextEdit
{
    Q_OBJECT

public:
    YRichEditor(QWidget *parent = 0);

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
private:
    /*!
     \brief 合并选中的单词样式，如果没有选中，则合并光标所在位置的单词样式。

     \param format 要合并的单词样式
    */
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
};

#endif
