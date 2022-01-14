#include "Snake.h"
#include "conif.h"
#include "autorank.h"

using namespace std;

snake::SnakeBody *SnakeHead, *Node, *SnakeEnd;
snake::FoodInfo Food;

const int MapWidth = 68;
const int MapHeight = 26;
const char Block[] = "■";
const char FoodGraph[] = "⊙";
int SPEED = 80, sprank = 5, SScore = 0;
int Direction = 4; //蛇的朝向,1234分别对应上左下右
bool StartFlag, FirstTime;
bool LoopFlag, RestartFlag;

int snake::snakemain()
{
    StartFlag = true;
    FirstTime = true;
    LoopFlag=true;
    RestartFlag=true;
    StartP:
    welcome();
    while (StartFlag)
    {
        GameInit();
        MainLoop();
        if(!RestartFlag)goto StartP;
    }
    return 0;
}

void snake::gotoxy(int x, int y)
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

void snake::printBlock(int x, int y)
{
    gotoxy(x, y);
    cout << Block;
    return;
}

void snake::printFood(int x, int y)
{
    gotoxy(x, y);
    cout << FoodGraph;
    return;
}

void snake::printSpace(int x, int y)
{
    gotoxy(x, y);
    cout << "　";
    return;
}

void snake::creatFood()
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

void snake::welcome()
{
    if (FirstTime)
    {
        int OpeningXY[][2] = {
            {18, 5}, {16, 5}, {14, 5}, {12, 5}, {10, 5}, {10, 6}, {10, 7}, {12, 7}, {14, 7}, {16, 7}, {18, 7}, {18, 8}, {18, 9}, {16, 9}, {14, 9}, {12, 9}, {10, 9}, // S
            {22, 5},
            {22, 6},
            {22, 7},
            {22, 8},
            {22, 9},
            {24, 6},
            {26, 7},
            {28, 8},
            {30, 9},
            {30, 8},
            {30, 7},
            {30, 6},
            {30, 5}, // N
            {38, 5},
            {36, 6},
            {34, 7},
            {34, 8},
            {34, 9},
            {40, 6},
            {42, 7},
            {42, 8},
            {42, 9},
            {36, 8},
            {38, 8},
            {40, 8}, // A
            {46, 5},
            {46, 6},
            {46, 7},
            {46, 8},
            {46, 9},
            {52, 5},
            {50, 6},
            {48, 7},
            {50, 7},
            {52, 8},
            {52, 9}, // K
            {58, 5},
            {58, 6},
            {58, 7},
            {58, 8},
            {58, 9},
            {60, 5},
            {62, 5},
            {64, 5},
            {66, 5},
            {60, 7},
            {62, 7},
            {64, 7},
            {66, 7},
            {60, 9},
            {62, 9},
            {64, 9},
            {66, 9}, // E
            {0, 0}};
        system("cls");
        int i = 0;
        while (OpeningXY[i][1] != 0)
        {
            printBlock(OpeningXY[i][0], OpeningXY[i][1]);
            Sleep(20);
            i++;
        }
        gotoxy(18, 12);
        cout << "Press any button to continue...";
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursor;
        cursor.bVisible = TRUE;
        cursor.dwSize = sizeof(cursor);
        SetConsoleCursorInfo(hOutput, &cursor);
        while (!kbhit())
        {
        }
        system("cls");
        cursor.bVisible = FALSE;
        cursor.dwSize = sizeof(cursor);
        SetConsoleCursorInfo(hOutput, &cursor);
        FirstTime=false;
    }
MenuLabel:
    char OptNameS[][MAXOPTLEN] = {"Start Game", "Set Speed", "Quit"};
    char STitle[] = {"S N A K E"};
    conif GameMenu(3, OptNameS, STitle, 64);
    switch (GameMenu.Display())
    {
    case 0:
        gotoxy(10, 8);
        cout << "请使用英文输入法，用wsad键控制上下左右！";
        Sleep(3000);
        return;
    case 1:
        setspeed();
        goto MenuLabel;
    case 2:
        StartFlag = false;
        break;
    }
    return;
}

void snake::setspeed()
{
SpeedLabel:
    gotoxy(10, 8);
    cout << "Please set the speed(1 slowest ~ 8 fastest):";
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = TRUE;
    cursor.dwSize = sizeof(cursor);
    SetConsoleCursorInfo(hOutput, &cursor);
    cin >> sprank;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    switch (sprank)
    {
    case 1:
        SPEED = 200;
        break;
    case 2:
        SPEED = 160;
        break;
    case 3:
        SPEED = 130;
        break;
    case 4:
        SPEED = 100;
        break;
    case 5:
        SPEED = 80;
        break;
    case 6:
        SPEED = 60;
        break;
    case 7:
        SPEED = 45;
        break;
    case 8:
        SPEED = 30;
        break;
    default:
        gotoxy(14, 10);
        cout << "Please enter a valid value!";
        Sleep(3000);
        system("cls");
        goto SpeedLabel;
    }
    system("cls");
    gotoxy(10, 8);
    cout << "Setting succeded!";
    Sleep(2000);
    system("cls");
    return;
}

void snake::setmap(int width, int height)
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

void snake::GameInit()
{
    SScore=0;
    LoopFlag=true;
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

void snake::DeleteEnd()
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

void snake::Moving()
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

void snake::Eating()
{
    Moving();
    SScore += sprank;
    creatFood();
    return;
}

void snake::GameOver()
{
    char ifcontinue;
    Sleep(800);
    gotoxy(72, 8);
    cout << "Game Over!";
    Sleep(800);
    gotoxy(72, 10);
    cout << "Your Score is: " << SScore;
    Sleep(400);
    getch();
    while (!kbhit)
    {
    }
    system("cls");
    scoredealer::FastIOScore(SScore, "snake.dat");
    cout << "Continue?(y/n)" << endl;
    cin >> ifcontinue;
    if (ifcontinue == 'y') RestartFlag=true;
    else RestartFlag=false;
    LoopFlag=false;
    return;
}

void snake::HeadJudge()
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

int snake::XYJudge(int x, int y)
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

bool snake::Reaction(char kbin)
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

void snake::MainLoop()
{
    DWORD Time_start, Time_delta, Time_refresh, Time_lastframe;
    bool GotCommand = false;
    char KeyboardInput;
    while (!kbhit())
    {
    }
    Time_lastframe = GetTickCount();
    while (LoopFlag)
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