#ifndef GAMEMAINWINDOW_H
#define GAMEMAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QWidget>
#include<QMouseEvent>
#include<QKeyEvent>
#include"game.h"
#include<gameover.h>
namespace Ui {
class gameMainWindow;
}

class gameMainWindow : public QMainWindow
{
    Q_OBJECT

    friend class game;
public:
    explicit gameMainWindow(QWidget *parent = 0);
    gameMainWindow(QWidget *parent=0,int numbers=1);
    ~gameMainWindow();

    void setbackground();
    void setpainter(QPainter& pat,QPen& pen,QBrush& brush);   //设置画棋盘工具
    void setmap(QPainter& pat,QPen& pen,QBrush& brush);   // 画棋盘
    void setset(QPainter& pat,QBrush& brush); //画中心点
    // 在（x，y）处落子。
    void put_chess(); //1玩家   -1电脑
    void paintcur();//画取鼠标位置

    void mouseMoveEvent(QMouseEvent *event);   //捕获鼠标
    void mousePressEvent(QMouseEvent *event);  //获取点击鼠标
    void paintEvent(QPaintEvent *event);

private:
    int chess[15][15];
    int moveX;
    int moveY;
    game gaming;
    Ui::gameMainWindow *ui;

};

#endif // GAMEMAINWINDOW_H
