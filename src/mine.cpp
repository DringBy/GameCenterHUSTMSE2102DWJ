#include "mine.h"
#include "autorank.h"
#include "conif.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <conio.h>
#include <string>

//��һ��������Χ�ĸ���������㷽ʽ�����������У����������д
int lpCheckRange[2][8] = {
	{1, 0, 0, -1, 1, 1, -1, -1},
	{0, 1, -1, 0, 1, -1, 1, -1}};

MineMap::MineMap(int wide, int heigh, int mine_num) : iWide(std::max(wide, 1)),
													  iHeigh(std::max(heigh, 1)),
													  vOriginalMap(std::max(wide, 1) + 2),
													  vStateMap(std::max(wide, 1) + 2),
													  blIsDead(false),
													  bIsFirst(false),
													  iPutFlag(0),
													  iShowPlace(0),
													  iScore(0),
													  iMineNum(std::min(iHeigh * iWide - 1, mine_num)),
													  iBlankSize(iWide * iHeigh),
													  iCursoX(5),
													  iCursoY(5)
{
	//����λ�Ҷ���
	ssTmpInput.setf(std::ios_base::left, std::ios_base::adjustfield);

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

	CountMine();

	FindStartP(iCursoX, iCursoY);
	Touch(iCursoX, iCursoY);
	bIsFirst = true;
}

void MineMap::CountMine()
{
	for (int i = 1; i <= iWide; i++)
	{
		for (int j = 1; j <= iHeigh; j++)
		{
			if (vOriginalMap[i][j] == om_MINE)
				continue;
			for (int k = 0; k < 8; k++)
			{
				if (vOriginalMap[i + lpCheckRange[0][k]][j + lpCheckRange[1][k]] == om_MINE)
					vOriginalMap[i][j]++;
			}
		}
	}
}

void MineMap::FindStartP(int &x, int &y)
{
	int iMinSur = 9;
	for (int i = 1; i <= iWide; i++)
	{
		for (int j = 1; j <= iHeigh; j++)
		{
			if (vOriginalMap[i][j] >= 0 && vOriginalMap[i][j] < iMinSur)
			{
				iMinSur = vOriginalMap[i][j];
				x = i;
				y = j;
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
			if (vOriginalMap[i][j] >= 0)
			{
				ssTmpInput.width(3);
				ssTmpInput << vOriginalMap[i][j];
			}
			else if (vOriginalMap[i][j] == om_MINE)
				ssTmpInput << "*  ";
			else if (vOriginalMap[i][j] == om_BLANK)
				ssTmpInput << "$  ";
		}
		ssTmpInput << '\n';
	}
}

void MineMap::Print_State()
{
	ssTmpInput << "   ";

	for (int i = 0; i < iHeigh + 2; i++)
	{
		ssTmpInput.width(3);
		ssTmpInput << i;
	}
	ssTmpInput << '\n';

	for (int i = 0; i < iWide + 2; i++)
	{
		ssTmpInput.width(3);
		ssTmpInput << i;
		for (int j = 0; j < iHeigh + 2; j++)
		{
			if (i == iCursoX && j == iCursoY)
			{
				SpecializeCurso();
			}
			else if (vStateMap[i][j] == sm_SHOWN)
			{
				ssTmpInput << vOriginalMap[i][j] << "  ";
			}
			else if (vStateMap[i][j] == sm_UNKNOWN)
				ssTmpInput << "�� ";
			else if (vStateMap[i][j] == sm_QUEST)
				ssTmpInput << "�� ";
			else if (vStateMap[i][j] == sm_FLAG)
				ssTmpInput << "�� ";
			else if (vStateMap[i][j] == sm_BLANK)
				ssTmpInput << "�w  ";
		}

		if (i == 1)
		{
			ssTmpInput << "\t��\t" << iWide << 'x' << iHeigh << "ɨ����Ϸ\n";
		}
		else if (i == 2)
		{
			ssTmpInput << "\t��\tɨ�׽���:" << iPutFlag << '/' << iMineNum << '\n';
		}
		else if (i == 3)
		{
			ssTmpInput << "\t��\t̽������:" << iShowPlace << '/' << iBlankSize << '\n';
		}
		else
			ssTmpInput << "\t��\t\n";
	}
}

bool MineMap::Touch(int x, int y)
{

	if (!(x > 0 && x <= iWide && y > 0 && y <= iHeigh))
	{
		return false;
	}

	if (bIsFirst)
	{
		bIsFirst = false;
		tmGameTime.Start();
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
		if (vOriginalMap[x][y] == 0)
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
		if (vStateMap[x][y] == sm_FLAG)
		{
			iPutFlag--;
		}

		vStateMap[x][y] = sm_QUEST;

		return true;
	}
	else
		return false;
}

bool MineMap::PutFlag(int x, int y)
{
	if (x > 0 && x <= iWide && y > 0 && y <= iHeigh && (vStateMap[x][y] == sm_UNKNOWN || vStateMap[x][y] == sm_QUEST))
	{
		vStateMap[x][y] = sm_FLAG;
		iPutFlag++;

		return true;
	}
	else
		return false;
}

bool MineMap::PutReset(int x, int y)
{
	if (x > 0 && x <= iWide && y > 0 && y <= iHeigh && (vStateMap[x][y] == sm_FLAG || vStateMap[x][y] == sm_QUEST))
	{
		if (vStateMap[x][y] == sm_FLAG)
		{
			iPutFlag--;
		}

		vStateMap[x][y] = sm_UNKNOWN;

		return true;
	}
	else
		return false;
}

bool MineMap::PutConfirm(int x, int y)
{
	if (x > 0 && x <= iWide && y > 0 && y <= iHeigh && (vStateMap[x][y] == sm_SHOWN))
	{
		int iFlagCount = 0;
		for (int k = 0; k < 8; k++)
		{
			if (vStateMap[x + lpCheckRange[0][k]][y + lpCheckRange[1][k]] == sm_FLAG)
			{
				iFlagCount++;
			}
		}

		if (iFlagCount >= vOriginalMap[x][y])
		{
			for (int k = 0; k < 8; k++)
			{
				Touch(x + lpCheckRange[0][k], y + lpCheckRange[1][k]);
			}
		}

		return true;
	}
	else
		return false;
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
	keycheck kcQuit('E');
	keycheck kcTouch('T');
	keycheck kcReset('R');
	keycheck kcQuest('Q');
	keycheck kcFlag('F');
	keycheck kcConfirm('C');
	keycheck kcUp(VK_UP);
	keycheck kcLeft(VK_LEFT);
	keycheck kcRight(VK_RIGHT);
	keycheck kcDown(VK_DOWN);

	int x = 0, y;
	bool bIsUpdate = true;
	;

	while (kcQuit.getstat() == 0 && !IsDead() && !IsWin())
	{
		if (bIsUpdate)
		{
			//��ͼ����
			system("cls");
			ssTmpInput << "e �˳�\tt ����\tr �ָ�\tq ����\tf ���\tc �Զ���̽\n";
			ssTmpInput << "�� �յ�\t�� ����\t�� ���\n";
			ssTmpInput << "���������ƶ����\n";
			Print_State();
			std::cout << ssTmpInput.str();

			ssTmpInput.str("");
			ssTmpInput.clear();

			bIsUpdate = false;
		}
		
		Sleep(50);

		//�߼�����
		if (kcLeft.getstat() == 1 || kcLeft.getstat() == 3)
		{
			iCursoY = (iHeigh + iCursoY - 2) % iHeigh + 1;
			bIsUpdate = true;
		}
		else if (kcRight.getstat() == 1 || kcRight.getstat() == 3)
		{
			iCursoY = (iCursoY) % iHeigh + 1;
			bIsUpdate = true;
		}
		else if (kcUp.getstat() == 1 || kcUp.getstat() == 3)
		{
			iCursoX = (iWide + iCursoX - 2) % iWide + 1;
			bIsUpdate = true;
		}
		else if (kcDown.getstat() == 1 || kcDown.getstat() == 3)
		{
			iCursoX = (iCursoX) % iWide + 1;
			bIsUpdate = true;
		}
		else if (kcTouch.getstat() == 1)
		{
			Touch(iCursoX, iCursoY);
			bIsUpdate = true;
		}
		else if (kcReset.getstat() == 1)
		{
			PutReset(iCursoX, iCursoY);
			bIsUpdate = true;
		}
		else if (kcQuest.getstat() == 1)
		{
			PutQuest(iCursoX, iCursoY);
			bIsUpdate = true;
		}
		else if (kcFlag.getstat() == 1)
		{
			PutFlag(iCursoX, iCursoY);
			bIsUpdate = true;
		}
		else if (kcConfirm.getstat() == 1)
		{
			PutConfirm(iCursoX, iCursoY);
			bIsUpdate = true;
		}
	}
	tmGameTime.Stop();

	//��Ϸ����������

	clean(); //������뻺����

	ssTmpInput.str("");
	ssTmpInput.clear();
	system("cls");
	Print_State();
	printf("\n");
	Print_Original();
	std::cout << ssTmpInput.str();
	ssTmpInput.str("");
	ssTmpInput.clear();

	clock_t ctGameTime = -tmGameTime.Read();
	printf("��Ϸ����ʱ��%d.%ds\n", ctGameTime / 1000, ctGameTime % 1000);

	if (IsDead())
	{
		printf("��Ϸʧ��\n");
		return false;
	}
	else if (IsWin())
	{
		if (IsCountable(iWide, iHeigh, iMineNum))
		{
			CountScore();
			printf("��Ϸ�÷�:%u\n", iScore);

			scoredealer::FastIOScore(iScore, "mine.dat");
		}
		printf("��Ϸʤ��\n");
		return true;
	}
	else
	{
		printf("�˳���Ϸ\n");
		return false;
	}
}

void MineMap::SpecializeCurso()
{
	switch (vStateMap[iCursoX][iCursoY])
	{
	case sm_SHOWN:
	{
		if (vOriginalMap[iCursoX][iCursoY] == om_MINE)
		{
			ssTmpInput << "*  ";
			break;
		}
		ssTmpInput << clpNumTable[vOriginalMap[iCursoX][iCursoY]];
		break;
	}
	case sm_UNKNOWN:
	{
		ssTmpInput << "�� ";
		break;
	}
	case sm_QUEST:
	{
		ssTmpInput << "�� ";
		break;
	}
	case sm_FLAG:
	{
		ssTmpInput << "�� ";
		break;
	}
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
	clock_t cCurTime = -tmGameTime.Read();
	double ulSizeBase = 45 * 45 + 1 - std::min(45.0 * 45.0, iWide * iHeigh * 1.0);
	ulSizeBase = pow(1.006, ulSizeBase * (1 + fabs(log10(iMineNum * 1.0) / iBlankSize)));
	unsigned long ulFullScore = 4000000000ul / (unsigned long)ulSizeBase;

	double TimeRate = std::min((3000.0 / cCurTime), 1.0);
	iScore = ulFullScore * TimeRate;
}

void GetArgs(int &x, int &y, int &num)
{
	char c = 0;

	while (true)
	{
		system("cls");
		printf("�������ͼ�Ŀ�� �߶� ������Ŀ\n");
		scanf("%d %d %d", &x, &y, &num);

		if (x > 0 && y > 0 && num > 0)
		{
			if (IsCountable(x, y, num))
			{
				break;
			}
			else
			{
				printf("�˵�ͼ����Ϊ���Ƽ��Ĳ������������¼����!\n");
				printf("����yȷ�����������棬��������������ѡ��\n");
				std::cin >> c;

				if (c == 'y')
					break;
			}
		}

		clean(); //������뻺����
	}
	system("cls");
}

void PlayMine()
{
	bool bIsChoosed = true;
	int x = 0, y = 0, num = 0;
	char c = 0;

	char lpDiffName[][MAXOPTLEN] = {"EASY", "NORMAL", "HARD", "LUNARTIC", "EX-STAGE", "EXIT"};
	char lpTitle[] = "MINE SWEEPER";
	conif cfDiffChose(6, lpDiffName, lpTitle, 48);

	while (true)
	{
		bIsChoosed = true;
		x = 0, y = 0, num = 0;

		c = cfDiffChose.Display();

		switch (c)
		{
		case 0:
		{
			x = 9;
			y = 9;
			num = 10;
			break;
		}
		case 1:
		{
			x = 16;
			y = 16;
			num = 40;
			break;
		}
		case 2:
		{
			x = 16;
			y = 30;
			num = 99;
			break;
		}
		case 3:
		{
			x = 30;
			y = 45;
			num = 350;
			break;
		}
		case 4:
		{
			GetArgs(x, y, num);
			break;
		}
		case 5:
		{
			return;
		}
		}

		system("cls");

		MineMap mm(x, y, num);
		mm.Play();

		printf("��Ϸ����������r\t�ٴ�����,�����������˳�\n");

		std::cin >> c;

		if (c != 'r')
			break;
		system("cls");
	}
}