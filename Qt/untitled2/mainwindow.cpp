#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
/*
    ui->label->setText("push the key :z");
    ui->pushButton->setText("try");
    QImage *img=new QImage;
    img->load("D:/bite/bite_pratice/pratice/Qt/untitled2/Debug/zhezhi.jpg");
    ui->picture->setPixmap(QPixmap::fromImage(*img));
   */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_2_clicked(bool checked)
{
    QFont font=ui->label->font();
    font.setUnderline(checked);
    ui->label->setFont(font);
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    QFont font=ui->lineEdit->font();
    font.setUnderline(checked);
    font.setItalic(checked);
    ui->lineEdit->setFont(font);
}

void MainWindow::on_color_clicked()
{
    QPalette plet=ui->label->palette();
    if(ui->color->isChecked())
        plet.setColor(QPalette::Text,Qt::blue);
    else
        plet.setColor(QPalette::Text,Qt::red);
    ui->label->setPalette(plet);
}

