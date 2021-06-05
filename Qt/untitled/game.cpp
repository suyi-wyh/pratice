#include "game.h"
/*
game::game():
    player(1)
{
    robot=true;
    for(int i =0;i < max;++i)
        for(int j=0;j < max;++j)
            game_chess[i][j]=0;
}
*/

game::game(int numbers):
    player(1)
{
    if(numbers == 1)
        robot=true;
    else{
         robot=false;
    }
    memset(game_chess,0,sizeof(game_chess));
}

bool game::isEmpty(int x, int y){
    return game_chess[x][y] == 0;
}

bool game::chessPut(int x, int y){
    if(player % 2 == 1){   //p1  黑子
        if(isEmpty(x,y)){
            game_chess[x][y]=player1_chess;
            return true;
        }
        else
            std::cout<<"game_chess: "<<game_chess[x][y]<<std::endl;
    }
    else{     //p2  白子
        if(isEmpty(x,y)){
            game_chess[x][y]=player2_chess;
            return true;
        }
        else
            std::cout<<"game_chess: "<<game_chess[x][y]<<std::endl;
    }
    return false;
}


bool game::checkWin(int x, int y){

    int curX=x;
    int curY=y;
    int flag=1;

    // 横向
            //向左
    x-=1;
    while(x >= min){
        if( game_chess[x][y]  ==  game_chess[curX][curY]){
            x--;
            flag++;
        }
        else
            break;
    }
            //向右
    x=curX+1;
    while(x < max){
        if( game_chess[x][y] == game_chess[curX][curY] ){
            x++;
            flag++;
        }
        else
            break;
    }
    //std::cout<<"chess::  "<<game_chess[curX][curY]<<std::endl;
    //std::cout<<"flag::  "<<flag<<std::endl;
    if(flag >= 5)
        return true;
    flag=1;

    //竖向
        //向上
    x=curX;
    y=curY-1;
    while(y >= min){
        if(game_chess[x][y] == game_chess[curX][curY]){
            y--;
            flag++;
        }
        else
            break;
    }

        // 向下
    y=curY+1;
    while(y < max){
        if(game_chess[x][y]==game_chess[curX][curY]){
            y++;
            flag++;
        }
        else
            break;
    }

    if(flag >= 5)
        return true;
    flag=1;

    //左右斜线（\）
        // 向左上
    y=curY-1;
    x=curX-1;
    while(x>=min && y>=min){
        if(game_chess[x][y] == game_chess[curX][curY]){
            y--;x--;
            flag++;
        }
        else
            break;
    }
        // 向右下
    y=curY+1;
    x=curX+1;

    while(x<=max && x<=max){
        if(game_chess[x][y] == game_chess[curX][curY]){
            y++;x++;
            flag++;
        }
        else
            break;
    }
    if(flag >= 5)
        return true;
    flag=1;

    y=curY+1;
    x=curX-1;
    //  右左斜线（/）
            //向右下
    while(x >=min && y < max){
        if(game_chess[x][y] == game_chess[curX][curY]){
            y++;x--;
            flag++;
        }
        else
            break;
    }
            //向左上

    y=curY-1;
    x=curX+1;
    while(x<max && y>=min){
        if(game_chess[x][y] == game_chess[curX][curY]){
            x++;y--;
            flag++;
        }
        else
            break;
    }

    if(flag>=5)
        return true;

    // 未胜

    player++;   // 换player执子
    return false;
}


bool game::isRobot(){
    return robot;
}

