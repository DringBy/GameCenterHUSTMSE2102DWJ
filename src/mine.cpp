#include"mine.h"
#include"autorank.h"
#include<cstdlib>
#include <cstdio>
#include<iostream>
#include<cmath>
#include<conio.h>

//��һ��������Χ�ĸ���������㷽ʽ�����������У����������д
int lpCheckRange[2][8] = {
	{1,0,0,-1, 1,1,-1,-1},
	{0,1,-1,0, 1,-1,1,-1}
};

MineMap::MineMap(int wide, int heigh, int mine_num) :
	iWide(std::max(wide, 1)),
	iHeigh(std::max(heigh, 1)),
	vOriginalMap(std::max(wide, 1) + 2),
	vStateMap(std::max(wide, 1) + 2),
	blIsDead(false),
	bIsFirst(true),
	iPutFlag(0),
	iShowPlace(0),
	iScore(0),
	iMineNum(std::min(iHeigh * iWide - 1, mine_num)),
	iBlankSize(iWide * iHeigh)
{
	iBlankSize -= iMineNum;

	srand((unsigned int)time(NULL));

	//��ʼ����ͼ�����ö�άvector
	for (int i = 0; i < iWide + 2; i++)
	{
		vOriginalMap[i].resize(iHeigh + 2);
		vStateMap[i].resize(iHeigh + 2);

		for (int j = 1; j < iHeigh + 1; j++)
		{
			vOriginalMap[i][j] = 0;
			vStateMap[i][j] = sm_UNKNOWN;
		}
	}

	//����Ե�������ã��������д����Ķ����ж�
	for (int j = 1; j < iHeigh + 1; j++)
	{
		vOriginalMap[0][j] = om_BLANK;
		vStateMap[0][j] = sm_BLANK;
		vOriginalMap[iWide + 1][j] = om_BLANK;
		vStateMap[iWide + 1][j] = sm_BLANK;
	}

	for (int i = 0; i < iWide + 2; i++)
	{
		vOriginalMap[i][0] = om_BLANK;
		vOriginalMap[i][iHeigh + 1] = om_BLANK;
		vStateMap[i][0] = sm_BLANK;
		vStateMap[i][iHeigh + 1] = sm_BLANK;
	}

	//���õ���
	//�Ȱ�˳���ֹ����
	for (int i = 0; i < iMineNum; i++)
	{
		vOriginalMap[i / iHeigh + 1][i % iHeigh + 1] = om_MINE;
	}
	
	//����ͼ�еĸ��Ӵ��ң�ʵ���������λ�õ�Ч��
	int iTmpSwap;
	int iRandX, iRandY;
	for (int i = 1; i <= iHeigh; i++)
	{
		for (int j = 1; j <= iWide; j++)
		{
			iRandX = rand() % iWide + 1;
			iRandY = rand() % iHeigh + 1;
			iTmpSwap = vOriginalMap[j][i];
			vOriginalMap[j][i] = vOriginalMap[iRandX][iRandY];
			vOriginalMap[iRandX][iRandY] = iTmpSwap;
		}
	}
}

void MineMap::CountMine()
{
	for (int i = 1; i <= iWide; i++)
	{
		for (int j = 1; j <= iHeigh; j++)
		{
			if (vOriginalMap[i][j] == om_MINE)continue;
			for (int k = 0; k < 8; k++)
			{
				if (vOriginalMap[i + lpCheckRange[0][k]][j + lpCheckRange[1][k]] == om_MINE) vOriginalMap[i][j]++;
			}
		}
	}
}

void MineMap::Print_Original()
{

	for (int i = 0; i < iWide + 2; i++)
	{
		for (int j = 0; j < iHeigh + 2; j++)
		{
			if(vOriginalMap[i][j] >= 0)printf("%-3d", vOriginalMap[i][j]);
			else if (vOriginalMap[i][j] == om_MINE)printf("*  ");
			else if (vOriginalMap[i][j] == om_BLANK)printf("$  ");
		}
		printf("\n");
	}

}

void MineMap::Print_State()
{
	printf("   ");

	for (int i = 0; i < iHeigh + 2; i++)
	{
		printf("%-3d", i);
	}
	printf("\n");

	for (int i = 0; i < iWide + 2; i++)
	{
		printf("%-3d", i);
		for (int j = 0; j < iHeigh + 2; j++)
		{
			if (vStateMap[i][j] == sm_SHOWN)
			{
				printf("%-3d", vOriginalMap[i][j]);
			}
			else if (vStateMap[i][j] == sm_UNKNOWN)printf("@  ");
			else if (vStateMap[i][j] == sm_QUEST)printf("?  ");
			else if (vStateMap[i][j] == sm_FLAG)printf("#  ");
			else if (vStateMap[i][j] == sm_BLANK)printf("$  ");
		}

		if(i == 1)
		{
			printf("\t��\t%dx%dɨ����Ϸ\n", iWide, iHeigh);
		}
		else if(i == 2)
		{
			printf("\t��\tɨ�׽���:%d/%d\n", iPutFlag, iMineNum);
		}
		else if(i == 3)
		{
			printf("\t��\t̽������:%d/%d\n", iShowPlace, iBlankSize);
		}
		else printf("\t��\t\n");
	}

}

void MineMap::FindNoneMine(int& x, int& y)
{
	for (int i = 1; i < iWide + 1; i++)
	{
		for (int j = 1; j < iHeigh + 1; j++)
		{
			if(vOriginalMap[i][j] != om_MINE)
			{
				x = i;
				y = j;
				return;
			}
		}
	}
}

bool MineMap::Touch(int x, int y)
{

	if (!(x > 0 && x <= iWide && y > 0 && y <= iHeigh))
	{
		return false;
	}

	//��ֹ��һ����ǵ���
	if(bIsFirst)
	{
		bIsFirst = false;

		vStateMap[x][y] = sm_SHOWN;
		iShowPlace++;

		if (vOriginalMap[x][y] == om_MINE)
		{
			int fx,fy;
			FindNoneMine(fx, fy);
			vOriginalMap[fx][fy] = om_MINE;
			vOriginalMap[x][y] = 0;
		}

		CountMine();

		//�Զ������Χû�е��׵ĸ���
		if(vOriginalMap[x][y] == 0)
		{
			for (int i = 0; i < 8; i++)
			{
				Touch(x + lpCheckRange[0][i], y + lpCheckRange[1][i]);
			}
		}

		tmGameTime.Start();

		return true;
	}

	if (vStateMap[x][y] == sm_UNKNOWN)
	{
		vStateMap[x][y] = sm_SHOWN;
		iShowPlace++;

		if (vOriginalMap[x][y] == om_MINE)
		{
			blIsDead = true;
			return true;
		}

		//�Զ������Χû�е��׵ĸ���
		if(vOriginalMap[x][y] == 0)
		{
			for (int i = 0; i < 8; i++)
			{
				Touch(x + lpCheckRange[0][i], y + lpCheckRange[1][i]);
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool MineMap::PutQuest(int x, int y)
{
	if (x > 0 && x <= iWide && y > 0 && y <= iHeigh && (vStateMap[x][y] == sm_UNKNOWN || vStateMap[x][y] == sm_FLAG))
	{
		vStateMap[x][y] = sm_QUEST;

		return true;
	}
	else return false;
}

bool MineMap::PutFlag(int x, int y)
{
	if (x > 0 && x <= iWide && y > 0 && y <= iHeigh && (vStateMap[x][y] == sm_UNKNOWN || vStateMap[x][y] == sm_QUEST))
	{
		vStateMap[x][y] = sm_FLAG;
		iPutFlag++;

		return true;
	}
	else return false;
}

bool MineMap::PutReset(int x, int y)
{
	if (x > 0 && x <= iWide && y > 0 && y <= iHeigh && (vStateMap[x][y] == sm_FLAG || vStateMap[x][y] == sm_QUEST))
	{
		if(vStateMap[x][y] == sm_FLAG)
		{
			iPutFlag--;
		}

		vStateMap[x][y] = sm_UNKNOWN;

		return true;
	}
	else return false;
}

bool MineMap::IsDead()
{
	return blIsDead;
}

bool MineMap::IsWin()
{
	return iShowPlace == iBlankSize && !blIsDead;
}

bool MineMap::Play()
{
	bool is = true;
	bool ps = true;
	char c = 0;
	int x = 0, y;

	while (c != 'e' && !IsDead() && !IsWin())
	{
		if (!ps)
		{
			printf("��Ч������\n");
		}
		else if (!is)
		{
			printf("��Ч������:%c\n", c);
			is = true;
		}

		printf("e �˳�\tt ����\tr �ָ�\tq ����\tf ���\n");
		Print_State();

		std::cin >> c;

		if (c != 'e')
		{
			scanf("%d %d", &y, &x);
			if (c == 't')
			{			
				ps = Touch(x, y);
			}
			else if (c == 'r')
			{
				ps = PutReset(x, y);
			}
			else if (c == 'q')
			{
				ps = PutQuest(x, y);
			}
			else if (c == 'f')
			{
				ps = PutFlag(x, y);
			}
			else is = false;
		}

		system("cls");
	}
	tmGameTime.Stop();

	Print_State();
	printf("\n");
	Print_Original();

	clock_t ctGameTime = -tmGameTime.Read();
	printf("��Ϸ����ʱ��%d.%ds\n", ctGameTime / 1000, ctGameTime % 1000);

	if (c == 'e')
	{
		printf("�˳���Ϸ\n");
		return false;
	}
	else if(IsDead())
	{
		printf("��Ϸʧ��\n");
		return false;
	}
	else
	{
		printf("��Ϸʤ��\n");
		if(IsCountable(iWide, iHeigh, iMineNum))
		{
			CountScore();
			printf("��Ϸ�÷�:%u\n", iScore);

			scoredealer::FastIOScore(iScore, "mine.dat");
		}
		return true;
	}
}

bool IsCountable(int w, int h, int num)
{
	int iMineNum = std::min(w * h - 1, num);
	int iBlankSize = w * h - iMineNum;
	bool ans = true;
	ans &= !(w < 8 || h < 8);
	ans &= !(w > 45 || h > 45);
	ans &= !((iMineNum * 1.0) / iBlankSize < 0.02 || (iMineNum * 1.0) / iBlankSize > 5);
	ans &= !((w * 1.0) / h < 0.2 || (w * 1.0) / h > 5);
	return ans;
}

void MineMap::CountScore()
{
	clock_t cCurTime = - tmGameTime.Read();
	double ulSizeBase = 45 * 45 + 1 - std::min(45.0 * 45.0, iWide * iHeigh * 1.0);
	ulSizeBase = pow(1.006, ulSizeBase * (1 + fabs(log10(iMineNum * 1.0) / iBlankSize)));
	unsigned long ulFullScore = 4000000000ul / (unsigned long)ulSizeBase;

	double TimeRate = std::min((3000.0 / cCurTime), 1.0);
	iScore = ulFullScore * TimeRate;
}

void GetArgs(int&x, int&y, int&num)
{
	char c = 0;

	while(true)
	{
		system("cls");
		printf("�������ͼ�Ŀ�� �߶� ������Ŀ\n");
		scanf("%d %d %d", &x, &y, &num);

		if(x > 0 && y > 0 && num > 0)
		{
			if(IsCountable(x, y, num))
			{
				break;
			}
			else
			{
				printf("�˵�ͼ����Ϊ���Ƽ��Ĳ������������¼����!\n");
				printf("����yȷ�����������棬��������������ѡ��\n");
				std::cin >> c;

				if(c == 'y')break;
			}
		}

		scanf("%*[^\n]%*c");//������뻺����
	}
	system("cls");
}

void PlayMine()
{
		bool bIsChoosed = true;
	int x = 0, y = 0, num = 0;
	char c = 0;

	while (true)
	{
		bIsChoosed = true;
		x = 0, y = 0, num = 0;
		c = 0;

		while (bIsChoosed)
		{
			printf("��ѡ����Ϸģʽ:\nq\t��(9x9+10)\nw\t��ͨ(16x16+40)\ne\t����(16x30+99)\nr\t�Զ���\nt\t�˳�\n");
			bIsChoosed = false;
			std::cin >> c;
			switch (c)
			{
			case 'q':
			{
				x = 9;
				y = 9;
				num = 10;
				break;
			}
			case 'w':
			{
				x = 16;
				y = 16;
				num = 40;
				break;
			}
			case 'e':
			{
				x = 16;
				y = 30;
				num = 99;
				break;
			}
			case 'r':
			{
				GetArgs(x, y, num);
				break;
			}
			case 't':
			{
				return;
			}
			default:
			{
				bIsChoosed = true;
			}
			}
		}
		system("cls");

		MineMap mm{x, y, num};
		mm.Play();

		printf("��Ϸ����������r\t�ٴ�����,�����������˳�\n");

		std::cin >> c;

		if(c != 'r')break;
		system("cls");
	}
}