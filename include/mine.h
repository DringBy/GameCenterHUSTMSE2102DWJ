#pragma once
#include<vector>
#include"timer.h"

//���׵�ͼ�ϵĵ���
const int om_MINE =	-1;
//���׵�ͼ�ϵı�Ե
const int om_BLANK = -2;

//״̬��ͼ�ϵı�Ե
const int sm_BLANK = 4;
//���ʱ�ʶ
const int sm_QUEST = 3;
//���ı�ʶ
const int sm_FLAG = 2;
//��ʾ��ʶ
const int sm_SHOWN = 1;
//δ֪��ʶ
const int sm_UNKNOWN = 0;

//�е�ɨ����Ϸ����
class MineMap
{
public:

	//���캯��
	MineMap(int wide, int heigh, int mine_num);

	//���Ƶ���״̬��ͼ
	void Print_Original();
	//���Ƶ�ͼ״̬��ͼ
	void Print_State();

	//�ж�����Ƿ�ʧ��
	bool IsDead();
	//�ж�����Ƿ�ʤ��
	bool IsWin();
	//���п���������˳���Ϸ

	//��ʼ��Ϸ
	bool Play();

private:

	//��һ���ǵ��׵�λ��
	void FindNoneMine(int& x, int& y);

	//������Χ�ĵ�����Ŀ
	void CountMine();

	//��������
	bool Touch(int x,int y);
	//�������ʱ�ʶ
	bool PutQuest(int x, int y);
	//���õ��ױ�ʶ
	bool PutFlag(int x, int y);
	//���ñ�־
	bool PutReset(int x, int y);

	//����÷�
	void CountScore();

	//ԭʼ��ͼ����¼ ���׼��յ���Χ�ĵ�����
	std::vector<std::vector<int>> vOriginalMap;
	//״̬��ͼ�����ָ���ҵ�ͼ
	std::vector<std::vector<char>> vStateMap;

	//��ͼ���
	int iWide;
	//��ͼ����
	int iHeigh;

	//�Ƿ�����
	bool blIsDead;
	//�Ƿ��ǵ�һ�δ�����ͼ
	bool bIsFirst;

	//���õ�������
	int iPutFlag;
	//��ʾ�ĵؿ���
	int iShowPlace;
	//��Ϸ��ʱ��
	timer tmGameTime;
	//�÷�
	unsigned long iScore;
	//������Ŀ
	int iMineNum;
	//��ͼ��С
	int iBlankSize;
};

//�Ƿ�ɼƷ�
bool IsCountable(int w, int h, int num);

//��ȡ�Զ���ģʽ����
void GetArgs(int&x, int&y, int&num);

//ͨ����Ϸ���
void PlayMine();