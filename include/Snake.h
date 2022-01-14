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

//移动光标
void gotoxy(int x, int y);    
//创建地图      
void setmap(int width, int height); 
//打印方块
void printBlock(int x, int y);  
//打印食物    
void printFood(int x, int y);      
//打印空格 
void printSpace(int x, int y);      
//随机生成食物
void creatFood();      

//欢迎界面
void welcome();                    

//设置移动速度
void setspeed();                   
//游戏初始化 
void GameInit();                    

//主体循环
void MainLoop();                    

//判断蛇头前方是什么
void HeadJudge();                   
//执行键盘输入的指令,同时返回一个bool值表示该指令是否可执行
bool Reaction(char kbin);           
//判断xy格内有什么
int XYJudge(int x, int y);          

//移动蛇身
void Moving();
//删除蛇尾
void DeleteEnd();
//吃到食物
void Eating();

//游戏结束
void GameOver();                    

//游戏入口
int snakemain();
}