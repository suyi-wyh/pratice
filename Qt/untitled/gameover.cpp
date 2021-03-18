#include "gameover.h"
#include "ui_gameover.h"

gameover::gameover(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::gameover)
{
    ui->setupUi(this);
}

gameover::~gameover()
{
    delete ui;
}

void gameover::on_chosse_clicked()
{
    this->close();
    Dialog *GW=new Dialog;
    GW->show();
}

void gameover::on_again_clicked()
{
    this->close();
    gameMainWindow* GW=new gameMainWindow(0,1);
    GW->show();
}
