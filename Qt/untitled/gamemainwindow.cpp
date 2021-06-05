#include "gamemainwindow.h"
#include "ui_gamemainwindow.h"

/*
gameMainWindow::gameMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameMainWindow),
    gaming(1)
{
    memset(chess,0,sizeof(chess));
    ui->setupUi(this);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover,true);
    setbackground();
}
*/
gameMainWindow::gameMainWindow(QWidget *parent, int numbers):
    QMainWindow(parent),
    ui(new Ui::gameMainWindow),
    gaming(numbers)
{
    memset(chess,0,sizeof(chess));
    ui->setupUi(this);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover,true);
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

void gameMainWindow::setset(QPainter &pat, QBrush &brush){
    brush.setColor(Qt::black);
    pat.setBrush(brush);
    pat.drawEllipse(155,175,10,10);
    pat.drawEllipse(475,175,10,10);
    pat.drawEllipse(155,495,10,10);
    pat.drawEllipse(475,495,10,10);
    pat.drawEllipse(315,335,10,10);
}

void gameMainWindow::put_chess(){

    QPainter pat(this);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    pat.setPen(Qt::NoPen);

    for(int i=0;i<15;++i)
        for(int j=0;j<15;++j){
            if(chess[i][j] == 5){
                brush.setColor(Qt::black);
                pat.setBrush(brush);
                pat.drawEllipse(QPoint((j+1)*40,(i+1)*40+20),18,18);
            }
            else if(chess[i][j] == 4){
                brush.setColor(Qt::white);
                pat.setBrush(brush);
                pat.drawEllipse(QPoint((j+1)*40,(i+1)*40+20),18,18);
            }
        }
}


void gameMainWindow::paintcur(){
    QPainter pat(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    pat.setPen(pen);
    if((moveX*40+40) >= 20&&(moveX*40 <= 620)&&(moveY*40+20)>= 40&&(moveY*40+20)<=640){
        //上
        pat.drawLine((moveY+1)*40-20,(moveX+1)*40,(moveY+1)*40-10,(moveX+1)*40);
        pat.drawLine((moveY+1)*40+20,(moveX+1)*40,(moveY+1)*40+10,(moveX+1)*40);
        //下
        pat.drawLine((moveY+1)*40-20,(moveX+1)*40+40,(moveY+1)*40-10,(moveX+1)*40+40);
        pat.drawLine((moveY+1)*40+20,(moveX+1)*40+40,(moveY+1)*40+10,(moveX+1)*40+40);

        pat.drawLine((moveY+1)*40-20,(moveX+1)*40,(moveY+1)*40-20,(moveX+1)*40+10);
        pat.drawLine((moveY+1)*40+20,(moveX+1)*40,(moveY+1)*40+20,(moveX+1)*40+10);

        pat.drawLine((moveY+1)*40-20,(moveX+1)*40+40,(moveY+1)*40-20,(moveX+1)*40+30);
        pat.drawLine((moveY+1)*40+20,(moveX+1)*40+40,(moveY+1)*40+20,(moveX+1)*40+30);

    }
}

void gameMainWindow::mouseMoveEvent(QMouseEvent *event){
    moveX=(event->pos().y()-40)/40;
    moveY=(event->pos().x()-20)/40;
    update();

}

void gameMainWindow::mousePressEvent(QMouseEvent *event){

    int curX=(event->pos().x()-20)/40;
    int curY=(event->pos().y()-40)/40;
/*
    for(int i=0;i<15;++i){
        for(int j=0;j<15;++j){
            printf("chess[%d][%d]:%d  \n",i,j,gaming.game_chess[i][j]);
        }
    }
*/
    //  std::cout<<gaming.robot<<std::endl;
    if(event->button() == Qt::LeftButton &&gaming.chessPut(curX,curY)){
        chess[curY][curX]= 4 + gaming.player%2;
        std::cout<<gaming.player<<std::endl;
        //gaming.player++;
        //printf("chess[%d][%d]:%d  \n",curX,curY,gaming.game_chess[curX][curY]);
        update();
        if(gaming.checkWin(curX,curY)){
            this->close();
            gameover *GW =new gameover;
            GW->show();
        }
        //人机是否下棋
        if(gaming.isRobot()){

        }
    }
    /*
    else if(event->button() ==Qt::RightButton){
        curX=(event->pos().x()-20)/40;
        curY=(event->pos().y()-40)/40;
        chess[curY][curX]=5;
    }
    */
        update();

}

void gameMainWindow::paintEvent(QPaintEvent *event){

    QPainter pat(this);
    QPen pen;
    QBrush brush;
    setmap(pat,pen,brush);
    setset(pat,brush);
    paintcur();
    put_chess();
}
