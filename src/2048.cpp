#include "2048.h"
using namespace std;
int Play2048()
{
	srand((unsigned int)time(NULL));

	int a[4][4] = {{0}, {0}, {0}, {0}}, flag1 = 0;
	cout << "��Ϸ��ʼ��" << endl
		 << endl;
	while (1)
	{
		//����2��4
		int k = 0, i, j;
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				if (a[i][j] == 0)
					k++;
		int pro1, pro2; //�������pro1�������ѡ���λ��pro2��������2��4
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
					} //�����ɣ��������ѭ��
				}
				if (word == 1)
					break; //���������ɣ��������ѭ��
			}
			k = 0; // k����
		}

		//�������
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
				cout << setw(5) << a[i][j];
			cout << endl
				 << endl;
		}

		//��������е��ƶ�
		cout << "������ w(��)�� s (��) �� a (��) �� d(��) e(�˳�)" << endl;
		cout << "���������������һ�»س���" << endl;
		char c;
		cin >> c;

		//���Ʋ���
		if (c == 'w')
		//�������е�����
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
			//�ϲ�����
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

		//���Ʋ���
		else if (c == 's')
		{
			//������������
			for (j = 0; j < 4; j++)
				for (i = 0; i < 4; i++)
					if (a[i][j] == 0)
						for (int s = i; s > 0; s--)
						{
							int temp = a[s][j];
							a[s][j] = a[s - 1][j];
							a[s - 1][j] = temp;
						}
			//�ϲ�����
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

		//���Ʋ���
		else if (c == 'a')
		{
			//������������
			for (i = 0; i < 4; i++)
				for (j = 3; j >= 0; j--)
					if (a[i][j] == 0)
						for (int s = j; s < 3; s++)
						{
							int temp = a[i][s];
							a[i][s] = a[i][s + 1];
							a[i][s + 1] = temp;
						}
			//�ϲ�����
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

		//���Ʋ���
		else if (c == 'd')
		{
			//������������
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
					if (a[i][j] == 0)
						for (int s = j; s > 0; s--)
						{
							int temp = a[i][s];
							a[i][s] = a[i][s - 1];
							a[i][s - 1] = temp;
						}
			//�ϲ�����
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

		//�ж���Ϸ�Ƿ����
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				if (a[i][j] == 0)
					k++;
				else if (a[i][j] == 2048)
					flag1 = 1; //�Ѻϳ�2048����Ϸ�ɹ�
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
				flag1 = 2; //û������2048��Ҳ�����ƶ�����Ϸʧ��
		}
		if (flag1 == 1 || flag1 == 2)
			break; //����whileѭ��
		system("cls");
	}
	if (flag1 == 1)
		cout << "YOU WIN!";
	if (flag1 == 2)
		cout << "YOU LOSE!";

	return 0;
}