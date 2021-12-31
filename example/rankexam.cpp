#include "../include/autorank.h"

int rankmain()
{
    //写入数据示例
    scoredealer::Insert(scoreblock{"n123", time(NULL) - 100, 100ul});
    scoredealer::Insert(scoreblock{"n123456", time(NULL) + 200, 100000000ul});
    scoredealer::Insert(scoreblock{"n123456789", time(NULL) + 300, 1000000ul});
    scoredealer::Insert(scoreblock{"中文字符", time(NULL) - 500, 10000ul});
    scoredealer::Insert(scoreblock{"123中文abc{_?", time(NULL) + 50, 114514ul});

    scoredealer::PrintList(1);
    scoredealer::WriteFile("test.dat");

    // //输出数据示例
    scoredealer::ReadFile("test.dat");
    scoredealer::PrintList(1);

    //使用说明
    /*
    0.复制autorank.h与autorank.cpp到需要的地方!!!!
    1.include"autorank.h"
    2.使用scoredealer::ReadFile读取相应的分数文件 文件名字随意但要固定 推荐：[小项目名].dat
    3.使用scoredealer::Insert(scoreblock{玩家名称,当前时间(time(NULL)),得分(unsigned long型数据)})
    4.使用scoredealer::WriteFile保存
    */

   //报告
   /*
   关键的数据结构；
   使用scoreblock保存数据块
   使用vector保存数据列表

    模块间接口描述:
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

    算法和程序流程:
    作为一个代码库
    无

    系统实现:
    将数据以字符串的形式读取实现对其二进制形式的读取

    需求分析：
    实现游戏程序需要的排行榜
    以二进制形式存储减少空间占用
    增加读取速度与效率
    防止玩家篡改排名数据
   */

    return 0;
}
