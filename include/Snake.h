#pragma once
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>

namespace snake{

struct SnakeBody //�ߵ����ɣ�������洢
{
    COORD pos;
    SnakeBody *next;
};

struct FoodInfo
{
    COORD pos;
};

void gotoxy(int x, int y);          //�ƶ����
void setmap(int width, int height); //������ͼ
void printBlock(int x, int y);      //��ӡ����
void printFood(int x, int y);       //��ӡʳ��
void printSpace(int x, int y);      //��ӡ�ո�
void creatFood();                   //�������ʳ��
void welcome();                     //��ӭ����(δ���)
void setspeed();                    //�����ƶ��ٶ�
void GameInit();                    //��Ϸ��ʼ��
void MainLoop();                    //����ѭ��
void HeadJudge();                   //�ж���ͷǰ����ʲô
bool Reaction(char kbin);           //ִ�м��������ָ��,ͬʱ����һ��boolֵ��ʾ��ָ���Ƿ��ִ��
int XYJudge(int x, int y);          //�ж�xy������ʲô
void Moving();
void DeleteEnd();
void Eating();
void GameOver();                    //��Ϸ����(δ���)

int snakemain();
}