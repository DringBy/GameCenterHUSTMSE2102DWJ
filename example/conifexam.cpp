#include <iostream>
#include "../include/conif.h"

char on[][MAXOPTLEN] = {"EASY", "困难", "HARD", "中文测试", "EXIT"/*, "额外测试", "外部文字"*/};
char t[] = "控制台下的用户交互选择界面测试";

int main() 
{
    conif a(5, on, t, 48);

    std::cout << a.Display() << std::endl;

    system("pause");
}
