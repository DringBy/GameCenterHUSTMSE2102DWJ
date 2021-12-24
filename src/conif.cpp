#include "conif.h"

conif::conif(int TotalOpt,
             char (*OptName)[MAXOPTLEN],
             char *Title,
             int ScreenW,
             char SelectCh,
             char BoardCh,
             DWORD UpVk,
             DWORD DownVk,
             DWORD EnterVk) : iTotalOpt(TotalOpt),
                              lpOptName(OptName),
                              lpTitle(Title),
                              iScreenW(ScreenW),
                              dwUpVk(UpVk),
                              dwDownVk(DownVk),
                              dwEnterVk(EnterVk),
                              iPointAt(0),
                              cSelectCh(SelectCh),
                              cBoardCh(BoardCh),
                              iTmpSize((ScreenW + 1) * (TotalOpt * 2 + 6)),
                              lpTmpStr(nullptr),
                              lpCenterBlank(nullptr),
                              lpCenterOffset(nullptr),
                              iChoseOffset(ScreenW)
{
    lpCenterBlank = new int[TotalOpt + 2];
    lpCenterOffset = new bool[TotalOpt + 2];

    if(lpTitle != nullptr)
    {
        lpCenterBlank[0] = (ScreenW - strlen(Title) - 2) / 2;//标题
        lpCenterOffset[0] = (ScreenW - strlen(Title) - 2) % 2;
    }

    lpCenterBlank[1] = (ScreenW - 3) / 2;//单字符行
    lpCenterOffset[1] = (ScreenW - 3) % 2;//单字符行

    for(int i = 2; i <= TotalOpt + 1; i++)
    {
        lpCenterBlank[i] = (ScreenW - strlen(OptName[i - 2]) - 2) / 2;
        lpCenterOffset[i] = (ScreenW - strlen(OptName[i - 2]) - 2) % 2;

        if(lpCenterBlank[i] < iChoseOffset)iChoseOffset = lpCenterBlank[i];
    }

    iChoseOffset--;

    lpTmpStr = new char[iTmpSize];
}

conif::~conif()
{
    delete[] lpCenterBlank;
    delete[] lpCenterOffset;
    delete[] lpTmpStr;
}

int conif::Display()
{
    keycheck ku(dwUpVk);
    keycheck kd(dwDownVk);
    keycheck ke(dwEnterVk);
    iPointAt = 0;
    bool blIsExit = false;
    bool bIsFlush = true;

    while(!blIsExit)
    {
        if(bIsFlush)
        {
            system("cls");
            Flush();
            printf(lpTmpStr);

            bIsFlush = false;
        }

        Sleep(20);

        if(ku.getstat() == 1 || ku.getstat() == 3)
        {
            iPointAt = (iPointAt + iTotalOpt - 1) % iTotalOpt;
            bIsFlush = true;
        }

        if(kd.getstat() == 1 || kd.getstat() == 3)
        {
            iPointAt = (iPointAt + 1) % iTotalOpt;
            bIsFlush = true;
        }

        if(ke.getstat() == 1)
        {
            blIsExit = true;
        }
    }

    system("cls");
    clean(); //清除输入缓冲区
    return iPointAt;
}

void conif::Flush()
{
    Clean();

    char* lpStrP = lpTmpStr;

    FlushWord(-4, lpStrP);
    FlushWord(-3, lpStrP);
    if(lpTitle == nullptr)FlushWord(-3, lpStrP);
    else FlushWord(-1, lpStrP);
    FlushWord(-3, lpStrP);
    FlushWord(-3, lpStrP);

    for(int i = 0; i < iTotalOpt; i++)
    {
        FlushWord(i, lpStrP);
        FlushWord(-3, lpStrP);
    }

    FlushWord(-4, lpStrP);

    *(lpStrP++) = '\0';
}

void conif::Clean()
{
    for(int i = 0; i < iTmpSize; i++)
    {
        lpTmpStr[i] = 0;
    }
}

void conif::FlushWord(int l, char *(&str), char c)
{
    if(l == -4)
    {
        str += PrintLine(iScreenW, cBoardCh, str);
        *(str++) = '\n';
    }
    else if(l == -3)
    {
        *(str++) = cBoardCh;
        str += PrintLine(iScreenW - 2, ' ', str);
        *(str++) = cBoardCh;
        *(str++) = '\n';
    }
    else if(l == -2)
    {
        *(str++) = cBoardCh;
        str += PrintLine(lpCenterBlank[1], ' ', str);
        *(str++) = c;
        str += PrintLine(lpCenterBlank[1] + lpCenterOffset[1], ' ', str);
        *(str++) = cBoardCh;
        *(str++) = '\n';
    }
    else if(l == -1)
    {
        *(str++) = cBoardCh;
        str += PrintLine(lpCenterBlank[0], ' ', str);
        str += sprintf(str, lpTitle);
        str += PrintLine(lpCenterBlank[0] + lpCenterOffset[0], ' ', str);
        *(str++) = cBoardCh;
        *(str++) = '\n';
    }
    else if(l == iPointAt)
    {
        *(str++) = cBoardCh;
        str += PrintLine(iChoseOffset - 1, ' ', str);
        *(str++) = cSelectCh;
        str += PrintLine(lpCenterBlank[l + 2] - iChoseOffset, ' ', str);
        str += sprintf(str, lpOptName[l]);
        str += PrintLine(lpCenterBlank[l + 2] - iChoseOffset + lpCenterOffset[l + 2], ' ', str);
        *(str++) = cSelectCh;
        str += PrintLine(iChoseOffset - 1, ' ', str);
        *(str++) = cBoardCh;
        *(str++) = '\n';
    }
    else if(l >= 0)
    {
        *(str++) = cBoardCh;
        str += PrintLine(lpCenterBlank[l + 2], ' ', str);
        str += sprintf(str, lpOptName[l]);
        str += PrintLine(lpCenterBlank[l + 2] + lpCenterOffset[l + 2], ' ', str);
        *(str++) = cBoardCh;
        *(str++) = '\n';
    }
}

int PrintLine(int n, char c, char* str)
{
    for(int i = 0; i < n; i++)
    {
        str[i] = c;
    }
    str[n] = '\0';

    return n;
}

void clean()
{
	int k;
	while (1) {
		if (_kbhit()) {
			k = _getch();
			if (0 == k || 0xE0 == k) k = _getch();
		}
		else break;
	}
}