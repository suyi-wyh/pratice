#include "dialog.h"
#include "ui_dialog.h"
#include"gamemainwindow.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->denglun->setStyleSheet(QString("background-color:white"));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_denglun_clicked()
{
    this->close();
    gameMainWindow* GW=new gameMainWindow;
    GW->show();
}
