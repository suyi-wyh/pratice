#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<string.h>
// 横向右x增加  竖向下y增加
class game
{
private:
    bool robot;   //是否人机对战
    int game_chess[15][15];   // 棋盘

    static const int min=0;
    static const int max=15;

public:
    int player;     //奇数偶数区分玩家
    static const int player1_chess=5;
    static const int player2_chess=4;
    static const int robotchess=4;

    //game();
    game(int numbers);
    bool isEmpty(int x,int y); //判断能否落子
    bool chessPut(int x,int y); //落子   5 玩家1    4  玩家2(电脑)
    bool checkWin(int x, int y);   //判断胜利
    bool isRobot();//判断是否有人机
};

#endif // GAME_H
