#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //创建富文本编辑控件
//    this->richEdit = new TestRichEdit(this);
//    this->richEdit->setGeometry(QRect(20, 20, 320, 240));
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete this->richEdit;
}

void MainWindow::on_pushButton_clicked(bool checked)
{
    this->ui->textEdit->wordBold(true);
}

void MainWindow::on_pushButton_2_clicked(bool checked)
{
    this->ui->textEdit->wordBold(false);
}
