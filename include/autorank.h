#pragma once

#include<string>
#include<ctime>
#include<vector>
#include<fstream>
#include <algorithm>
#include <iostream>

//�÷����ݿ�
class scoreblock
{
friend class scoredealer;

public:

    //���ش�������� �Է���Ϊ��׼
    bool operator > (const scoreblock& obj) const;
    //����С������� �Է���Ϊ��׼
    bool operator < (const scoreblock& obj) const;
    //���ص�������� �Է���Ϊ��׼
    bool operator == (const scoreblock& obj) const;

    //һ�㹹�캯��
    scoreblock(const std::string &Name, time_t PlayTime, unsigned long Score);
    //Ĭ�Ϲ��캯��
    scoreblock();

    //���ַ�����ʽ���������Ϣ
    const char* GetStrInf() const;

private:

    //�������
    std::string m_strName;
    //��¼ʱ��
    time_t m_ttPlayTime;
    //��ҵ÷�
    unsigned long m_ulScore;

    //��¼������Ϣ����ʱ�ַ���
    static char s_lpTmpStr[256];

};

//����÷����ݿ�
class scoredealer
{
public:

    //��������ļ�
    //path :    ����ļ���ַ
    //����ֵ:   �ļ��쳣ʱ����false
    static bool WriteFile(const char* path);
    //д������ļ�
    //path :    ����ļ���ַ
    //����ֵ:   �ļ��쳣ʱ����false
    static bool ReadFile(const char* path);

    //�����������
    //layer:    ���ʱ����Ԥ������Ʊ����
    static void PrintList(int layer);
    //���������
    static void Insert(const scoreblock& obj);

    //�������벢����ļ����������
    static void FastIOScore(unsigned long score, const char* path);

private:

    //���ع��캯��
    scoredealer();

    //�洢���ݿ�����飨������
    static std::vector<scoreblock> s_vScoreList;
    //���������ļ�
    static std::fstream s_fFile;

    //д��һ�����ݿ�
    static void WriteData(const scoreblock&);
    //����һ�����ݿ�
    static void ReadData(scoreblock&);

};