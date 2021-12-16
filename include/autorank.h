#pragma once

#include<string>
#include<ctime>
#include<vector>
#include<fstream>
#include <algorithm>
#include <iostream>

//得分数据块
class scoreblock
{
friend class scoredealer;

public:

    //重载大于运算符 以分数为基准
    bool operator > (const scoreblock& obj) const;
    //重载小于运算符 以分数为基准
    bool operator < (const scoreblock& obj) const;
    //重载等于运算符 以分数为基准
    bool operator == (const scoreblock& obj) const;

    //一般构造函数
    scoreblock(const std::string &Name, time_t PlayTime, unsigned long Score);
    //默认构造函数
    scoreblock();

    //以字符串形式输出分数信息
    const char* GetStrInf() const;

private:

    //玩家名称
    std::string m_strName;
    //计录时间
    time_t m_ttPlayTime;
    //玩家得分
    unsigned long m_ulScore;

    //记录分数信息的临时字符串
    static char s_lpTmpStr[256];

};

//处理得分数据块
class scoredealer
{
public:

    //输出分数文件
    //path :    输出文件地址
    //返回值:   文件异常时返回false
    static bool WriteFile(const char* path);
    //写入分数文件
    //path :    输出文件地址
    //返回值:   文件异常时返回false
    static bool ReadFile(const char* path);

    //输出分数排名
    //layer:    输出时各行预输出的制表符数
    static void PrintList(int layer);
    //插入分数块
    static void Insert(const scoreblock& obj);

    //快速输入并输出文件，计入分数
    static void FastIOScore(unsigned long score, const char* path);

private:

    //隐藏构造函数
    scoredealer();

    //存储数据块的数组（向量）
    static std::vector<scoreblock> s_vScoreList;
    //被操作的文件
    static std::fstream s_fFile;

    //写入一个数据块
    static void WriteData(const scoreblock&);
    //读出一个数据块
    static void ReadData(scoreblock&);

};