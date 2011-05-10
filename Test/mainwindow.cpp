#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextTable>
#include <QMessageBox>

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

void MainWindow::on_fontComboBox_textChanged(QString f)
{
    this->ui->textEdit->textFamily(f);
}

void MainWindow::on_pushButton_3_clicked(bool checked)
{
    this->ui->textEdit->textSize(50);
}

void MainWindow::on_pushButton_4_clicked(bool checked)
{
    this->ui->textEdit->textColor(QColor(255, 0, 0, 127));
}

void MainWindow::on_pushButton_5_clicked(bool checked)
{
    this->ui->textEdit->wordBackgroundColor(QColor(0, 0, 255, 127));
}

void MainWindow::on_pushButton_6_clicked(bool checked)
{
    this->ui->textEdit->alignText(TestRichEdit::Center);
}

void MainWindow::on_pushButton_7_clicked(bool checked)
{
    this->ui->textEdit->insertTable(6,3);
}

void MainWindow::on_pushButton_8_clicked(bool checked)
{
    this->ui->textEdit->insertTable(3,4,1,1);
}

void MainWindow::on_pushButton_9_clicked(bool checked)
{
    QMessageBox::information(this,tr("test"),QString("%1").arg(this->ui->textEdit->getPositionCell().row),QMessageBox::Ok);
}
