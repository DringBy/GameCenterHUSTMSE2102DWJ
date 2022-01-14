#include "2048.h"
using namespace std;
int Play2048()
{
	srand((unsigned int)time(NULL));

	int a[4][4] = {{0}, {0}, {0}, {0}}, flag1 = 0;
	cout << "游戏开始！" << endl
		 << endl;
	while (1)
	{
		//生成2或4
		int k = 0, i, j;
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				if (a[i][j] == 0)
					k++;
		int pro1, pro2; //随机数，pro1用于随机选择空位，pro2用于生成2或4
		if (k != 0)
		{
			pro1 = rand() % k + 1;
			pro2 = (rand() % 2 + 1) * 2;
			for (i = 0; i < 4; i++)
			{
				int word = 0;
				for (j = 0; j < 4; j++)
				{
					if (a[i][j] == 0)
						pro1--;
					if (pro1 == 0)
					{
						a[i][j] = pro2;
						word = 1;
						break;
					} //填空完成，跳出里层循环
				}
				if (word == 1)
					break; //随机生成完成，跳出外层循环
			}
			k = 0; // k归零
		}

		//输出数组
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
				cout << setw(5) << a[i][j];
			cout << endl
				 << endl;
		}

		//输入想进行的移动
		cout << "请输入 w(上)或 s (下) 或 a (左) 或 d(右) e(退出)" << endl;
		cout << "（输入完操作后摁一下回车）" << endl;
		char c;
		cin >> c;

		//上移操作
		if (c == 'w')
		//上移整列的数据
		{
			for (j = 0; j < 4; j++)
				for (i = 3; i >= 0; i--)
					if (a[i][j] == 0)
						for (int s = i; s < 3; s++)
						{
							int temp = a[s][j];
							a[s][j] = a[s + 1][j];
							a[s + 1][j] = temp;
						}
			//合并数据
			for (j = 0; j < 4; j++)
				for (i = 0; i < 3; i++)
					if (a[i][j] == a[i + 1][j])
					{
						a[i][j] *= 2;
						for (int s = i + 1; s < 3; s++)
						{
							int temp = a[s][j];
							a[s][j] = a[s + 1][j];
							a[s + 1][j] = temp;
						}
						a[3][j] = 0;
						break;
					}
		}

		//下移操作
		else if (c == 's')
		{
			//下移整列数组
			for (j = 0; j < 4; j++)
				for (i = 0; i < 4; i++)
					if (a[i][j] == 0)
						for (int s = i; s > 0; s--)
						{
							int temp = a[s][j];
							a[s][j] = a[s - 1][j];
							a[s - 1][j] = temp;
						}
			//合并数据
			for (j = 0; j < 4; j++)
				for (i = 3; i > 0; i--)
					if (a[i][j] == a[i - 1][j])
					{
						a[i][j] *= 2;
						for (int s = i - 1; s > 0; s--)
						{
							int temp = a[s][j];
							a[s][j] = a[s - 1][j];
							a[s - 1][j] = temp;
						}
						a[0][j] = 0;
						break;
					}
		}

		//左移操作
		else if (c == 'a')
		{
			//左移整行数组
			for (i = 0; i < 4; i++)
				for (j = 3; j >= 0; j--)
					if (a[i][j] == 0)
						for (int s = j; s < 3; s++)
						{
							int temp = a[i][s];
							a[i][s] = a[i][s + 1];
							a[i][s + 1] = temp;
						}
			//合并数据
			for (i = 0; i < 4; i++)
				for (j = 0; j < 3; j++)
					if (a[i][j] == a[i][j + 1])
					{
						a[i][j] *= 2;
						for (int s = j + 1; s < 3; s++)
						{
							int temp = a[i][s];
							a[i][s] = a[i][s + 1];
							a[i][s + 1] = temp;
						}
						a[i][3] = 0;
						break;
					}
		}

		//右移操作
		else if (c == 'd')
		{
			//右移整列数组
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
					if (a[i][j] == 0)
						for (int s = j; s > 0; s--)
						{
							int temp = a[i][s];
							a[i][s] = a[i][s - 1];
							a[i][s - 1] = temp;
						}
			//合并数据
			for (i = 0; i < 4; i++)
				for (j = 3; j > 0; j--)
					if (a[i][j] == a[i][j - 1])
					{
						a[i][j] *= 2;
						for (int s = j - 1; s > 0; s--)
						{
							int temp = a[i][s];
							a[i][s] = a[i][s - 1];
							a[i][s - 1] = temp;
						}
						a[i][0] = 0;
						break;
					}
		}

		//判断游戏是否结束
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				if (a[i][j] == 0)
					k++;
				else if (a[i][j] == 2048)
					flag1 = 1; //已合成2048，游戏成功
		if (k == 0 && flag1 != 1)
		{
			int flag2 = 0;
			for (j = 0; j < 4; j++)
				if (a[0][j] == a[1][j] || a[2][j] == a[3][j])
					flag2 = 1;
			for (i = 0; i < 4; i++)
				if (a[i][0] == a[i][1] || a[i][2] == a[i][3])
					flag2 = 1;
			if (flag2 == 0)
				flag1 = 2; //没有生成2048，也不能移动，游戏失败
		}
		if (flag1 == 1 || flag1 == 2)
			break; //跳出while循环
		system("cls");
	}
	if (flag1 == 1)
		cout << "YOU WIN!";
	if (flag1 == 2)
		cout << "YOU LOSE!";

	return 0;
}