#include "autorank.h"
#include <iostream>

const int c_iTsSize = 256;
char scoreblock::s_lpTmpStr[c_iTsSize] = {};

std::vector<scoreblock> scoredealer::s_vScoreList;
std::fstream scoredealer::s_fFile;

bool scoreblock::operator > (const scoreblock& obj) const
{
    return m_ulScore > obj.m_ulScore;
}

bool scoreblock::operator < (const scoreblock& obj) const
{
    return m_ulScore < obj.m_ulScore;
}

bool scoreblock::operator == (const scoreblock& obj) const
{
    return m_ulScore == obj.m_ulScore;
}

scoreblock::scoreblock(const std::string& Name, time_t PlayTime, unsigned long Score):
m_strName(Name),
m_ttPlayTime(PlayTime),
m_ulScore(Score)
{}

scoreblock::scoreblock():
m_strName(""),
m_ttPlayTime(0),
m_ulScore(0)
{}

const char* scoreblock::GetStrInf() const
{
    char lpTimeStr[20];

    tm *tmTimeStruct = localtime(&m_ttPlayTime);
    strftime(lpTimeStr, 20, "%Y-%m-%d %H:%M:%S", tmTimeStruct);

    sprintf(s_lpTmpStr, "%-12u%s     %s\n", m_ulScore, lpTimeStr, m_strName.c_str());
    return s_lpTmpStr;
}

scoredealer::scoredealer()
{}

void scoredealer::WriteData(const scoreblock& obj)
{
    char* ptr = (char*)&obj.m_ulScore;

    for(int i = 0; i < sizeof(unsigned long); i++)
    {
        s_fFile.put(ptr[i]);
    }

    ptr = (char*)&obj.m_ttPlayTime;

    for(int i = 0; i < sizeof(time_t); i++)
    {
        s_fFile.put(ptr[i]);
    }

    s_fFile << obj.m_strName;
    s_fFile.put('\0');
}

bool scoredealer::WriteFile(const char* path)
{
    bool is_suc = true;
    s_fFile.open(path, std::ios::out | std::ios::binary);
    size_t size = s_vScoreList.size();

    if(s_fFile.good())
    {
        char* ptr = (char*)&size;
        for(int i = 0; i < sizeof(size_t); i++)
        {
            s_fFile.put(ptr[i]);
        }

        for(std::vector<scoreblock>::iterator i = s_vScoreList.begin(); i < s_vScoreList.end();i++)
        {
            WriteData(*i);
        }
    }
    else
    {
        is_suc = false;
    }

    s_vScoreList.clear();
    s_fFile.close();
    s_fFile.clear();

    return is_suc;
}

void scoredealer::ReadData(scoreblock& obj)
{
    char ptr[sizeof(time_t)];

    //读取unsigned long 型数据
    s_fFile.read(ptr, sizeof(unsigned long));
    obj.m_ulScore = *(unsigned long*)ptr;

    s_fFile.read(ptr, sizeof(time_t));
    obj.m_ttPlayTime = *(time_t*)ptr;

    obj.m_strName.clear();
    std::getline(s_fFile, obj.m_strName, '\0');
}

bool scoredealer::ReadFile(const char* path)
{
    bool is_suc = true;
    char ptr[sizeof(time_t)];
    size_t size = 0;
    s_fFile.open(path, std::ios::in | std::ios::binary);

    s_fFile.read(ptr, sizeof(size_t));

    //判断文件读取状态
    if(!s_fFile.good())
    {
        s_vScoreList.resize(0);
    }
    else
    {
        size = *(size_t*)ptr;
        s_vScoreList.resize(size);
    }


    if(s_fFile.good())
    {
        for(int i = 0; i < size && s_fFile.good(); i++)
        {
            ReadData(s_vScoreList[i]);
        }
    }
    else
    {
        is_suc = false;
    }

    //关闭文件
    s_fFile.close();
    s_fFile.clear();

    return is_suc;
}

void scoredealer::PrintList(int layer)
{
    std::sort(s_vScoreList.rbegin(), s_vScoreList.rend());
    
    //lpLayerStr位存放缩进符的字符串
    char* lpLayerStr = new char[layer + 1];
    for(int i = 0; i < layer; i++)
    {
        lpLayerStr[i] = '\t';
    }
    lpLayerStr[layer] = '\0';

    std::cout << lpLayerStr << "RANK:     SCORE:      PLAYTIME:               NAME:" << std::endl;

    int rank = 1;
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    for(std::vector<scoreblock>::iterator i = s_vScoreList.begin(); i < s_vScoreList.end();i++)
    {
        std::cout << lpLayerStr;
        std::cout.width(10);
        std::cout << rank << i->GetStrInf() << std::endl;

        rank++;
    }

    delete[] lpLayerStr;
}

void scoredealer::Insert(const scoreblock& obj)
{
    s_vScoreList.push_back(obj);
}

void scoredealer::FastIOScore(unsigned long score, const char* path)
{
    char c;
    char str[256];

    printf("请问是否记录分数?\n输入y确定\n");
    std::cin >> c;

    if(c != 'y')return;
    printf("请输入您的名字:\n");
    std::cin >> str;

    ReadFile(path);

    Insert(scoreblock(str, time(NULL), score));

    WriteFile(path);
}