#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "testrichedit.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //TestRichEdit *richEdit;
private slots:
    void on_pushButton_clicked(bool checked);

    void on_pushButton_2_clicked(bool checked);

    void on_fontComboBox_textChanged(QString f);

    void on_pushButton_3_clicked(bool checked);

    void on_pushButton_4_clicked(bool checked);

    void on_pushButton_5_clicked(bool checked);

    void on_pushButton_6_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
