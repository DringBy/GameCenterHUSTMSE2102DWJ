#include"control.h"
#include<conio.h>
#include<iostream>

const int MAXOPTLEN = 32;

//����̨�µ��û�����ѡ�����
class conif
{
private:
    //�ϼ�
    DWORD dwUpVk;
    //�¼�
    DWORD dwDownVk;
    //ѡ���
    DWORD dwEnterVk;
    //ѡ������
    int iTotalOpt;
    //ѡ������
    char (*lpOptName)[MAXOPTLEN];
    //��Ļ���
    int iScreenW;
    //����
    char* lpTitle;
    //�߿��ַ�
    char cBoardCh;
    //ѡ���ַ�
    char cSelectCh;

    //ѡ���ַ���ƫ��
    int iChoseOffset;

    //��ʱ��������С
    int iTmpSize;
    //ָ��ѡ��
    int iPointAt;

    //���пո��б�
    int* lpCenterBlank;
    //���пո�ƫ���б�
    bool* lpCenterOffset;
    

    //�������� l = -4 �߿��� l = -3 ���� l = -2 ���ַ��� l = -1 ������
    void FlushWord(int l, char *(&str), char c = ' ');

    //���������
    void Clean();

    //���»���
    void Flush();

    //��ʱ������
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

//�ظ����뵥���ַ�
int PrintLine(int n, char c, char* str);

//������뻺���� ����Ч
void clean();