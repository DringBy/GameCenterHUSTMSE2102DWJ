#pragma once
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>

namespace snake{

struct SnakeBody //蛇的躯干，用链表存储
{
    COORD pos;
    SnakeBody *next;
};

struct FoodInfo
{
    COORD pos;
};

void gotoxy(int x, int y);          //移动光标
void setmap(int width, int height); //创建地图
void printBlock(int x, int y);      //打印方块
void printFood(int x, int y);       //打印食物
void printSpace(int x, int y);      //打印空格
void creatFood();                   //随机生成食物
void welcome();                     //欢迎界面(未完成)
void GameInit();                    //游戏初始化
void MainLoop();                    //主体循环
void HeadJudge();                   //判断蛇头前方是什么
bool Reaction(char kbin);           //执行键盘输入的指令,同时返回一个bool值表示该指令是否可执行
int XYJudge(int x, int y);          //判断xy格内有什么
void Moving();
void DeleteEnd();
void Eating();
void GameOver();                    //游戏结束(未完成)

int snakemain();
}