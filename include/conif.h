#include"control.h"
#include<conio.h>
#include<iostream>

const int MAXOPTLEN = 32;

//控制台下的用户交互选择界面
class conif
{
private:
    //上键
    DWORD dwUpVk;
    //下键
    DWORD dwDownVk;
    //选择键
    DWORD dwEnterVk;
    //选项总数
    int iTotalOpt;
    //选项名称
    char (*lpOptName)[MAXOPTLEN];
    //屏幕宽度
    int iScreenW;
    //标题
    char* lpTitle;
    //边框字符
    char cBoardCh;
    //选择字符
    char cSelectCh;

    //选中字符的偏移
    int iChoseOffset;

    //临时缓冲区大小
    int iTmpSize;
    //指向选项
    int iPointAt;

    //居中空格列表
    int* lpCenterBlank;
    //居中空格偏移列表
    bool* lpCenterOffset;
    

    //输入文字 l = -4 边框行 l = -3 空行 l = -2 单字符行 l = -1 标题行
    void FlushWord(int l, char *(&str), char c = ' ');

    //清除缓冲区
    void Clean();

    //更新画面
    void Flush();

    //临时缓冲区
    char* lpTmpStr;

public:

    conif(int TotalOpt, char (*OptName)[MAXOPTLEN],
     char* Title = NULL, 
     int ScreenW = 27, 
     char SelectCh = '*', 
     char BoardCh = '#',  
     DWORD UpVk = VK_UP, 
     DWORD DownVk = VK_DOWN, 
     DWORD EnterVk = VK_RETURN);

    int Display();   

    ~conif();
};

//重复输入单个字符
int PrintLine(int n, char c, char* str);

//清除输入缓冲区 最有效
void clean();