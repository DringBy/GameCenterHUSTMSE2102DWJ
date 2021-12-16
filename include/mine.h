#pragma once
#include<vector>
#include"timer.h"

//地雷地图上的地雷
const int om_MINE =	-1;
//地雷地图上的边缘
const int om_BLANK = -2;

//状态地图上的边缘
const int sm_BLANK = 4;
//疑问标识
const int sm_QUEST = 3;
//旗帜标识
const int sm_FLAG = 2;
//显示标识
const int sm_SHOWN = 1;
//未知标识
const int sm_UNKNOWN = 0;

//承担扫雷游戏的类
class MineMap
{
public:

	//构造函数
	MineMap(int wide, int heigh, int mine_num);

	//绘制地雷状态地图
	void Print_Original();
	//绘制地图状态地图
	void Print_State();

	//判断玩家是否失败
	bool IsDead();
	//判断玩家是否胜利
	bool IsWin();
	//还有可能是玩家退出游戏

	//开始游戏
	bool Play();

private:

	//找一个非地雷的位置
	void FindNoneMine(int& x, int& y);

	//计算周围的地雷数目
	void CountMine();

	//触摸坐标
	bool Touch(int x,int y);
	//放置疑问标识
	bool PutQuest(int x, int y);
	//放置地雷标识
	bool PutFlag(int x, int y);
	//重置标志
	bool PutReset(int x, int y);

	//计算得分
	void CountScore();

	//原始地图，记录 地雷即空地周围的地雷数
	std::vector<std::vector<int>> vOriginalMap;
	//状态地图，呈现给玩家地图
	std::vector<std::vector<char>> vStateMap;

	//地图宽度
	int iWide;
	//地图长度
	int iHeigh;

	//是否死亡
	bool blIsDead;
	//是否是第一次触动地图
	bool bIsFirst;

	//放置的旗帜数
	int iPutFlag;
	//显示的地块数
	int iShowPlace;
	//游戏计时器
	timer tmGameTime;
	//得分
	unsigned long iScore;
	//地雷数目
	int iMineNum;
	//地图大小
	int iBlankSize;
};

//是否可计分
bool IsCountable(int w, int h, int num);

//获取自定义模式参数
void GetArgs(int&x, int&y, int&num);

//通常游戏入口
void PlayMine();