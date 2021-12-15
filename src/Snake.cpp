#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>

using namespace std;

const int MapWidth = 68;
const int MapHeight = 26;
const char Block[] = "■";
const char FoodGraph[] = "⊙";
int SPEED = 40, Direction = 4; //蛇的朝向,1234分别对应上左下右

struct SnakeBody //蛇的躯干，用链表存储
{
    COORD pos;
    SnakeBody *next;
} * SnakeHead, *Node, *SnakeEnd;

struct FoodInfo
{
    COORD pos;
} Food;

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

int main()
{
    welcome();
    GameInit();
    MainLoop();
    return 0;
}

void gotoxy(int x, int y)
{
    COORD pos;
    //移动光标
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOutput, pos);
    // 隐藏光标
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    SetConsoleCursorInfo(hOutput, &cursor);
    return;
}

void printBlock(int x, int y)
{
    gotoxy(x, y);
    cout << Block;
    return;
}

void printFood(int x, int y)
{
    gotoxy(x, y);
    cout << FoodGraph;
    return;
}

void printSpace(int x, int y)
{
    gotoxy(x, y);
    cout << "　";
    return;
}

void creatFood()
{
    bool Flag = false;
    while (!Flag)
    {
        Flag = true;
        Food.pos.X = rand() % 33 + 1;
        Food.pos.Y = rand() % 25 + 1;
        SnakeBody *judge = SnakeHead;
        while (judge->next != NULL)
        {
            if (Food.pos.X == judge->pos.X && Food.pos.Y == judge->pos.Y)
            {
                Flag = false;
                break;
            }
            judge = judge->next;
        }
    }
    printFood(Food.pos.X * 2, Food.pos.Y);
    return;
}

void welcome()
{
    system("pause");
    return;
}

void setmap(int width, int height)
{
    system("cls");
    int px, py;
    for (px = 0; px <= width; px += 2)
    {
        if (px == 0 || px == width)
            for (py = 0; py <= height; py++)
            {
                printBlock(px, py);
            }
        else
        {
            printBlock(px, 0);
            printBlock(px, height);
        }
    }
    return;
}

void GameInit()
{
    srand((int)time(NULL));
    setmap(MapWidth, MapHeight);
    SnakeHead = (SnakeBody *)malloc(sizeof(SnakeBody));
    SnakeHead->next = NULL;
    SnakeEnd = SnakeHead;
    for (int i = 1; i <= 4; i++)
    {
        Node = (SnakeBody *)malloc(sizeof(SnakeBody));
        Node->pos.X = 4 + i;
        Node->pos.Y = 13;
        Node->next = SnakeHead;
        SnakeHead = Node;
        printBlock(SnakeHead->pos.X * 2, SnakeHead->pos.Y);
    }
    creatFood();
    return;
}

void DeleteEnd()
{
    SnakeBody *jNode;
    jNode = SnakeHead;
    while (jNode->next != SnakeEnd)
        jNode = jNode->next;
    printSpace(jNode->pos.X * 2, jNode->pos.Y);
    free(SnakeEnd);
    SnakeEnd = jNode;
    SnakeEnd->next = NULL;
    return;
}

void Moving()
{
    Node = (SnakeBody *)malloc(sizeof(SnakeBody));
    Node->next = SnakeHead;
    switch (Direction)
    {
    case 1:
    {
        Node->pos.X = SnakeHead->pos.X;
        Node->pos.Y = SnakeHead->pos.Y - 1;
        break;
    }
    case 2:
    {
        Node->pos.X = SnakeHead->pos.X - 1;
        Node->pos.Y = SnakeHead->pos.Y;
        break;
    }
    case 3:
    {
        Node->pos.X = SnakeHead->pos.X;
        Node->pos.Y = SnakeHead->pos.Y + 1;
        break;
    }
    case 4:
    {
        Node->pos.X = SnakeHead->pos.X + 1;
        Node->pos.Y = SnakeHead->pos.Y;
        break;
    }
    }
    SnakeHead = Node;
    printBlock(SnakeHead->pos.X * 2, SnakeHead->pos.Y);
    return;
}

void Eating()
{
    Moving();
    creatFood();
    return;
}

void GameOver()
{
    while (1)
        ;
    return;
}

void HeadJudge()
{
    int HeadXYInfo;
    switch (Direction)
    {
    case 1:
        HeadXYInfo = XYJudge(SnakeHead->pos.X, SnakeHead->pos.Y - 1);
        break;
    case 2:
        HeadXYInfo = XYJudge(SnakeHead->pos.X - 1, SnakeHead->pos.Y);
        break;
    case 3:
        HeadXYInfo = XYJudge(SnakeHead->pos.X, SnakeHead->pos.Y + 1);
        break;
    case 4:
        HeadXYInfo = XYJudge(SnakeHead->pos.X + 1, SnakeHead->pos.Y);
        break;
    default:
        cout << "Direction Default!";
        system("pause");
        break;
    }
    switch (HeadXYInfo)
    {
    case 0:
        DeleteEnd();
        Moving();
        break;
    case 1:
        Eating();
        break;
    case 2:
        GameOver();
        break;
    default:
        cout << "XYJudge Default!";
        system("pause");
        break;
    }
    return;
}

int XYJudge(int x, int y)
{
    if (Food.pos.X == x && Food.pos.Y == y)
        return 1;
    if (x == 0 || x == 34 || y == 0 || y == 26)
        return 2;
    SnakeBody *jNode = SnakeHead;
    while (jNode->next != SnakeEnd)
    {
        if (jNode->pos.X == x && jNode->pos.Y == y)
            return 2;
        jNode = jNode->next;
    }
    return 0;
}

bool Reaction(char kbin)
{
    switch (kbin)
    {
    case 'w':
    {
        if (Direction == 1 || Direction == 3)
            return false;
        Direction = 1;
        return true;
    }
    case 'a':
    {
        if (Direction == 2 || Direction == 4)
            return false;
        Direction = 2;
        return true;
    }
    case 's':
    {
        if (Direction == 1 || Direction == 3)
            return false;
        Direction = 3;
        return true;
    }
    case 'd':
    {
        if (Direction == 2 || Direction == 4)
            return false;
        Direction = 4;
        return true;
    }
    default:
        return false;
    }
}

void MainLoop()
{
    DWORD Time_start, Time_delta, Time_refresh, Time_lastframe;
    bool GotCommand = false;
    char KeyboardInput;
    Time_lastframe = GetTickCount();
    while (1)
    {
        Time_refresh = GetTickCount();
        Time_delta = Time_refresh - Time_lastframe;
        if (Time_delta >= SPEED)
        {
            HeadJudge();
            Time_lastframe = Time_refresh;
            GotCommand = false;
        }
        if (kbhit() && !GotCommand)
        {
            KeyboardInput = getch();
            GotCommand = Reaction(KeyboardInput);
        }
    }
    return;
}