#include "gamemainwindow.h"
#include "ui_gamemainwindow.h"


gameMainWindow::gameMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameMainWindow)
{
    ui->setupUi(this);

    setbackground();
}


gameMainWindow::~gameMainWindow()
{
    delete ui;
}

void gameMainWindow::setbackground(){
    this->setAutoFillBackground(true);
    QPalette plet;
    plet.setColor(QPalette::Background,QColor("#B1732C"));
    this->setPalette(plet);

}
 
void gameMainWindow::setpainter(QPainter& pat,QPen& pen,QBrush& brush){

    //QPainter pat(this);
    pat.setRenderHint(QPainter::Antialiasing,true);  //抗锯齿

    //QPen pen=pat.pen();
    pen.setColor(QColor("#8D5822"));
    pen.setJoinStyle(Qt::RoundJoin);   //线条连接状态
    pen.setWidth(7);
    pat.setPen(pen);

    //QBrush brush;
    brush.setColor(QColor("#EEC085"));
    brush.setStyle(Qt::SolidPattern);
    pat.setBrush(brush);

    pat.drawRect(20,40,600,600);


}

void gameMainWindow::setmap(QPainter& pat,QPen& pen,QBrush& brush){

    setpainter(pat,pen,brush);   //设置画笔工具
    pen.setColor(Qt::black);
    pen.setWidth(1);
    pat.setPen(pen);
    for(int i=0;i<15;++i){
        pat.drawLine(40+i*40,60,40+i*40,620);
        pat.drawLine(40,60+i*40,600,60+i*40);
    }
}

void gameMainWindow::paintEvent(QPaintEvent *event){
    QPainter pat(this);
    QPen pen;
    QBrush brush;
    setmap(pat,pen,brush);
}
