#ifndef GAMEMAINWINDOW_H
#define GAMEMAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QWidget>

namespace Ui {
class gameMainWindow;
}

class gameMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit gameMainWindow(QWidget *parent = 0);
    ~gameMainWindow();

private:
    Ui::gameMainWindow *ui;
    void setbackground();
    void setpainter(QPainter& pat,QPen& pen,QBrush& brush);   //设置画棋盘工具
    void setmap(QPainter& pat,QPen& pen,QBrush& brush);   // 画棋盘
    void paintEvent(QPaintEvent *event);
};

#endif // GAMEMAINWINDOW_H
