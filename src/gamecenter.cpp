#include <iostream>
#include "conif.h"
#include "Snake.h"
#include "mine.h"
#include "autorank.h"
#include "2048.h"

char lpMainPage[][MAXOPTLEN] = {"2 0 4 8", "Ì°³ÔÉß", "É¨À×", "ÅÅÐÐ°ñ", "ÍË³ö"};
char lpMainTitle[] = "GAMECENTER";

char lpRankPage[][MAXOPTLEN] = {"2 0 4 8", "Ì°³ÔÉß", "É¨À×", "·µ»Ø"};
char lpRankTitle[] = "Ñ¡ÔñÓÎÏ·";

void ViewRank()
{
    int cmd = 0;
    conif cfRankPage(4, lpRankPage, lpRankTitle, 48);

    while(true)
    { 
        cmd = cfRankPage.Display();

        switch (cmd)
        {
        case 0:
        {   
            //2048
            printf("COMING SOON\n");
            system("pause");
            system("cls");
            break;
        }
        case 1:
        {   
            scoredealer::ReadFile("snake.dat");
            scoredealer::PrintList(1);
            system("pause");
            system("cls");
            break;
        }
        case 2:
        {   
            scoredealer::ReadFile("mine.dat");
            scoredealer::PrintList(1);
            system("pause");
            system("cls");
            break;
        }
        case 3:
        {   
            return;
        }
        }
    }
}

int main() 
{
    int cmd = 0;

    conif cfMainPage(5, lpMainPage, lpMainTitle, 48);

    while(true)
    { 
        cmd = cfMainPage.Display();

        switch (cmd)
        {
        case 0:
        {   
            Play2048();
            break;
        }
        case 1:
        {   
            snake::welcome();
            snake::GameInit();
            snake::MainLoop();
            break;
        }
        case 2:
        {   
            PlayMine();
            break;
        }
        case 3:
        {   
            ViewRank();
            break;
        }
        case 4:
        {   
            return 0;
        }
        }
    }

    return 0;
}
