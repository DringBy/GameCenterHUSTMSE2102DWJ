#include<iostream>
#include<iomanip>
#include<conio.h>
#include"autorank.h"
using namespace std;
int Play2048()
{
	int a[4][4]={{0},{0},{0},{0}},flag1=0,point=0,againflag=1;//point���ڼƷ�
	int b[4][4]={{0},{0},{0},{1}};//���ڼ��ĳ�β���֮���Ƿ���Ч�ı������ݵ�λ��
	int first=1;//first�������ý�����Ϸ���ܲ��������
	cout<<"��Ϸ��ʼ��"<<endl<<endl;
	//������Ϸ
	while(againflag)
	{
		//ĳһ�ֿ�ʼ
		while(1)
		{
			//����2��4
			int k=0,i,j;char c;
			int flag3=0;
			//���ڼ��ĳ�β����Ƿ���ʵ�ı������ݵ�λ�ã����ʱ��b��¼���ǲ���ǰ������
			for(i=0;i<4;i++)
			{
				for(j=0;j<4;j++)
				{
					if(a[i][j]!=b[i][j])flag3=1;
				}
			}
			if(flag3&&(first||c=='w'||c=='s'||c=='a'||c=='d'))//��ֹ��Ч����
			{
				for(i=0;i<4;i++)
					for(j=0;j<4;j++)
						if(a[i][j]==0)k++;
				int pro1,pro2;//�������pro1�������ѡ���λ��pro2��������2��4
				if(k!=0)
				{
					pro1=rand()%k+1;
					pro2=(rand()%2+1)*2;
					for(i=0;i<4;i++)
					{	
						int word=0;
						for(j=0;j<4;j++)
						{
							if(a[i][j]==0)pro1--;
							if(pro1==0){a[i][j]=pro2;word=1;break;}//�����ɣ��������ѭ��
						}
						if(word==1)break;//���������ɣ��������ѭ��
					}
					k=0;//k����
				}
				first=0;
			}
			//aԪ�ص�ֵ����bԪ�أ��Ա���һ�μ���
			for(i=0;i<4;i++)
			{
				for(j=0;j<4;j++)
				{
					b[i][j]=a[i][j];
				}
			}

			//����÷�
			cout<<"�÷�"<<point<<endl<<endl;

			//�������
			for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
				cout<<setw(5)<<a[i][j];
			cout<<endl<<endl;
		}

			//��������е��ƶ�
			cout<<"������ w(��)�� s (��) �� a (��) �� d(��)"<<endl;
			cout<<"��������˳���������b�����ˣ�"<<endl;
			cout<<"����������¿�ʼ��������1"<<endl;
			c=_getch();

			//���Ʋ���
			if(c=='w')
				//�������е�����
			{	for(j=0;j<4;j++)
					for(i=3;i>=0;i--)
						if(a[i][j]==0)
							for(int s=i;s<3;s++)
							{
								int temp=a[s][j];
								a[s][j]=a[s+1][j];
								a[s+1][j]=temp;
							}
				//�ϲ�����
				for(j=0;j<4;j++)
					for(i=0;i<3;i++)
						if(a[i][j]==a[i+1][j]&&a[i][j]!=2048)
					{
						a[i][j]*=2;point+=a[i][j];
						for(int s=i+1;s<3;s++)
						{
							int temp=a[s][j];
								a[s][j]=a[s+1][j];
								a[s+1][j]=temp;
						}
						a[3][j]=0;
					}
			}

			//���Ʋ���
			else if(c=='s')
			{
				//������������
				for(j=0;j<4;j++)
					for(i=0;i<4;i++)
						if(a[i][j]==0)
							for(int s=i;s>0;s--)
							{
								int temp=a[s][j];
								a[s][j]=a[s-1][j];
								a[s-1][j]=temp;
							}
				//�ϲ�����
				for(j=0;j<4;j++)
					for(i=3;i>0;i--)
						if(a[i][j]==a[i-1][j]&&a[i][j]!=2048)
					{
						a[i][j]*=2;point+=a[i][j];
						for(int s=i-1;s>0;s--)
						{
							int temp=a[s][j];
								a[s][j]=a[s-1][j];
								a[s-1][j]=temp;
						}
						a[0][j]=0;
					}
			}

			//���Ʋ���
			else if(c=='a')
			{
				//������������
				for(i=0;i<4;i++)
					for(j=3;j>=0;j--)
						if(a[i][j]==0)
							for(int s=j;s<3;s++)
							{
								int temp=a[i][s];
								a[i][s]=a[i][s+1];
								a[i][s+1]=temp;
							}
				//�ϲ�����
				for(i=0;i<4;i++)
					for(j=0;j<3;j++)
						if(a[i][j]==a[i][j+1]&&a[i][j]!=2048)
					{
						a[i][j]*=2;point+=a[i][j];
						for(int s=j+1;s<3;s++)
						{
							int temp=a[i][s];
								a[i][s]=a[i][s+1];
								a[i][s+1]=temp;
						}
						a[i][3]=0;
					}
			}

			//���Ʋ���
			else if(c=='d')
			{
				//������������
				for(i=0;i<4;i++)
					for(j=0;j<4;j++)
						if(a[i][j]==0)
							for(int s=j;s>0;s--)
							{
								int temp=a[i][s];
								a[i][s]=a[i][s-1];
								a[i][s-1]=temp;
							}
				//�ϲ�����
				for(i=0;i<4;i++)
					for(j=3;j>0;j--)
						if(a[i][j]==a[i][j-1]&&a[i][j]!=2048)
					{
						a[i][j]*=2;point+=a[i][j];
						for(int s=j-1;s>0;s--)
						{
							int temp=a[i][s];
								a[i][s]=a[i][s-1];
								a[i][s-1]=temp;
						}
						a[i][0]=0;
					}
			}

			//���Ҫ�˳���Ϸ
			else if(c=='b')
			{
				char x;
				cout<<"��ȷ��Ҫ�˳������ᶪʧ��ǰ�Ľ���"<<endl;
				cout<<"������y��ȷ�������߰������ȡ��"<<endl;
				x=_getch();
				if(x=='y')return 0;
			}

			//���Ҫ�ؿ�
			else if(c=='1')
			{
				char x;
				cout<<"��ȷ��Ҫ���¿�ʼ��"<<endl;
				cout<<"������y��ȷ�������߰������ȡ��"<<endl;
				x=_getch();
				if(x=='y')
				{
					//������ֵ��ʼ��
					for(i=0;i<4;i++)
					{
						for(j=0;j<4;j++)
						{
							a[i][j]=0;
						}
					}
					for(i=0;i<4;i++)
					{
						for(j=0;j<4;j++)
						{
							b[i][j]=0;
						}
					}
					b[3][0]=1;
					first=1;
					point=0;
					flag1=0;
				}
			}

			//�ж���Ϸ�Ƿ����
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					if(a[i][j]==0)k++;
			if(k==0)
			{
				int flag2=1;
				for(j=0;j<4;j++)
					if(a[0][j]==a[1][j]||a[2][j]==a[3][j])flag2=0;
				for(i=0;i<4;i++)
					if(a[i][0]==a[i][1]||a[i][2]==a[i][3])flag2=0;
				if(flag2)flag1=1;//�������ˣ�Ҳ�����ƶ�����Ϸ����
			}
			if(flag1)break;//����whileѭ��
			system("cls");
		}
	if(flag1==1||flag1==2)
	{
		cout<<"��Ϸ��������ĵ÷���"<<point<<endl;
		scoredealer::FastIOScore(point, "2048.dat");
	}
	//����һ��
	cout<<"������a��again������һ�֣���,���߰�������˳�"<<endl;
	char again;
	again=_getch();
	if(again=='a')
	{
		//������ֵ��ʼ��
		int i,j;
		for(i=0;i<4;i++)
				{
					for(j=0;j<4;j++)
					{
						a[i][j]=0;
					}
				}
				for(i=0;i<4;i++)
				{
					for(j=0;j<4;j++)
					{
						b[i][j]=0;
					}
				}
				b[3][0]=1;
				first=1;
				point=0;
				flag1=0;
	}
	else againflag=0;
	system("cls");
	}
	return 0;
}