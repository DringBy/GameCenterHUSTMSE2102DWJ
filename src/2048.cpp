#include<iostream>
#include<iomanip>
#include<conio.h>
#include"autorank.h"
using namespace std;
int Play2048()
{
	int a[4][4]={{0},{0},{0},{0}},flag1=0,point=0,againflag=1;//point用于计分
	int b[4][4]={{0},{0},{0},{1}};//用于检测某次操作之后是否有效改变了数据的位置
	int first=1;//first变量是让进入游戏便能产生随机数
	cout<<"游戏开始！"<<endl<<endl;
	//进入游戏
	while(againflag)
	{
		//某一局开始
		while(1)
		{
			//生成2或4
			int k=0,i,j;char c;
			int flag3=0;
			//用于检测某次操作是否真实改变了数据的位置，这个时候b记录的是操作前的数据
			for(i=0;i<4;i++)
			{
				for(j=0;j<4;j++)
				{
					if(a[i][j]!=b[i][j])flag3=1;
				}
			}
			if(flag3&&(first||c=='w'||c=='s'||c=='a'||c=='d'))//防止无效操作
			{
				for(i=0;i<4;i++)
					for(j=0;j<4;j++)
						if(a[i][j]==0)k++;
				int pro1,pro2;//随机数，pro1用于随机选择空位，pro2用于生成2或4
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
							if(pro1==0){a[i][j]=pro2;word=1;break;}//填空完成，跳出里层循环
						}
						if(word==1)break;//随机生成完成，跳出外层循环
					}
					k=0;//k归零
				}
				first=0;
			}
			//a元素的值赋给b元素，以便下一次检验
			for(i=0;i<4;i++)
			{
				for(j=0;j<4;j++)
				{
					b[i][j]=a[i][j];
				}
			}

			//输出得分
			cout<<"得分"<<point<<endl<<endl;

			//输出数组
			for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
				cout<<setw(5)<<a[i][j];
			cout<<endl<<endl;
		}

			//输入想进行的移动
			cout<<"请输入 w(上)或 s (下) 或 a (左) 或 d(右)"<<endl;
			cout<<"如果您想退出，请输入b（后退）"<<endl;
			cout<<"如果您想重新开始，请输入1"<<endl;
			c=_getch();

			//上移操作
			if(c=='w')
				//上移整列的数据
			{	for(j=0;j<4;j++)
					for(i=3;i>=0;i--)
						if(a[i][j]==0)
							for(int s=i;s<3;s++)
							{
								int temp=a[s][j];
								a[s][j]=a[s+1][j];
								a[s+1][j]=temp;
							}
				//合并数据
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

			//下移操作
			else if(c=='s')
			{
				//下移整列数组
				for(j=0;j<4;j++)
					for(i=0;i<4;i++)
						if(a[i][j]==0)
							for(int s=i;s>0;s--)
							{
								int temp=a[s][j];
								a[s][j]=a[s-1][j];
								a[s-1][j]=temp;
							}
				//合并数据
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

			//左移操作
			else if(c=='a')
			{
				//左移整行数组
				for(i=0;i<4;i++)
					for(j=3;j>=0;j--)
						if(a[i][j]==0)
							for(int s=j;s<3;s++)
							{
								int temp=a[i][s];
								a[i][s]=a[i][s+1];
								a[i][s+1]=temp;
							}
				//合并数据
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

			//右移操作
			else if(c=='d')
			{
				//右移整列数组
				for(i=0;i<4;i++)
					for(j=0;j<4;j++)
						if(a[i][j]==0)
							for(int s=j;s>0;s--)
							{
								int temp=a[i][s];
								a[i][s]=a[i][s-1];
								a[i][s-1]=temp;
							}
				//合并数据
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

			//玩家要退出游戏
			else if(c=='b')
			{
				char x;
				cout<<"您确定要退出吗，您会丢失当前的进度"<<endl;
				cout<<"请输入y（确定）或者按任意键取消"<<endl;
				x=_getch();
				if(x=='y')return 0;
			}

			//玩家要重开
			else if(c=='1')
			{
				char x;
				cout<<"您确定要重新开始吗"<<endl;
				cout<<"请输入y（确定）或者按任意键取消"<<endl;
				x=_getch();
				if(x=='y')
				{
					//把所有值初始化
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

			//判断游戏是否结束
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
				if(flag2)flag1=1;//格子满了，也不能移动，游戏结束
			}
			if(flag1)break;//跳出while循环
			system("cls");
		}
	if(flag1==1||flag1==2)
	{
		cout<<"游戏结束，你的得分是"<<point<<endl;
		scoredealer::FastIOScore(point, "2048.dat");
	}
	//再来一局
	cout<<"请输入a（again，再来一局！）,或者按任意键退出"<<endl;
	char again;
	again=_getch();
	if(again=='a')
	{
		//把所有值初始化
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