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

//�ƶ����
void gotoxy(int x, int y);    
//������ͼ      
void setmap(int width, int height); 
//��ӡ����
void printBlock(int x, int y);  
//��ӡʳ��    
void printFood(int x, int y);      
//��ӡ�ո� 
void printSpace(int x, int y);      
//�������ʳ��
void creatFood();      

//��ӭ����
void welcome();                    

//�����ƶ��ٶ�
void setspeed();                   
//��Ϸ��ʼ�� 
void GameInit();                    

//����ѭ��
void MainLoop();                    

//�ж���ͷǰ����ʲô
void HeadJudge();                   
//ִ�м��������ָ��,ͬʱ����һ��boolֵ��ʾ��ָ���Ƿ��ִ��
bool Reaction(char kbin);           
//�ж�xy������ʲô
int XYJudge(int x, int y);          

//�ƶ�����
void Moving();
//ɾ����β
void DeleteEnd();
//�Ե�ʳ��
void Eating();

//��Ϸ����
void GameOver();                    

//��Ϸ���
int snakemain();
}