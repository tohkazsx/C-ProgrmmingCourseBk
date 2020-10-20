/* 1752528 计2 朱世轩 */
#include <iostream>
#include<iomanip>
#include <conio.h>
#include "90-b0.h"
#include"../common/common.h"
#include"../common/cmd_console_tools.h"
using namespace std;

int End()                                                                             //判断是否结束
{
	int judge,x,y;
	char c[6];
	cout << "本小题结束，输入end继续"<<endl;
	getxy(x, y);
	while (1)
	{
		gets_s(c);
		for (int i = 0; c[i] != '\0'; i++)
		{
			if (c[i] >= 'a'&&c[i] <= 'z')
				c[i] = c[i] - 32;
		}
		if (c[0] == 'E'&&c[1] == 'N'&&c[2] == 'D')
		{
			system("cls"); //调用系统命令清除屏幕
			judge = 0;
			break;
		}
		else
		{
			cout << "输入错误，请重新输入";
			judge = 1;
			gotoxy(x, y);
		}
	}
	
	return judge;
}

void compound(char W[12][12],int N[12][12],char xh,int a,int b,char choose,int a1,int b1,int & score,int goal, int & max)         //完成一次合成  ab为行列数 a1 b1为目标数 goal为合成目标
{
	int t;
	max=3;                                           //记录合成后最大值
	int sbc=0;                                          //本次得分
	int g = N[a1][b1] + 1;                             //g为合成后的值
	for (int i = 1; i <= a; i++)
		for (int j = 1; j <= b; j++)
		{
			if (W[i][j] == '*')
				N[i][j] = 0;
		}
	N[a1][b1] = g;
	cout << endl;
	cout << "相同值归并后的数组（不同色标识）："<<endl;
	cout << "  " << "|";
	for (int i = 0; i < b; i++)
		cout << setw(3) << i;
	cout << endl;
	cout << "--+";
	for (int i = 1; i <= a; i++)
		cout << "---";
	cout << endl;
	for (int i = 1; i <= a; i++)                                         //格式
	{                                                                   //
		cout << char(xh + i-1) << " |";                                //
		for (int j = 1; j <= b; j++)                                  //
			if (W[i][j] == '*')                                      //
			{                                                       //
				setcolor(0, 14);
				cout << setw(3) << N[i][j];
				setcolor(0, 7);
				sbc = sbc + 3 * (g - 1);
			}
			else
			{
				cout << setw(3) << N[i][j];
			}
		cout << endl;
	}               
	score = score + sbc;


for(int i=0;i<50;i++)
	for(int i=1;i <= a;i++)                                            //实现0下落
		for (int j = 1; j <= b; j++)
		{
			if (N[i][j] != 0 && N[i + 1][j] == 0)
			{
				N[i + 1][j] = N[i][j];
				N[i][j] = 0;
			}
		}

	cout << "本次得分：" << sbc << " " << "总得分：" << score << " " << "合成目标：" << goal << endl;

	cout << "按回车键确认下落除0"<<endl;
	while (1)
	{
		t = ENTER();
		if (t == 0)
			break;
	}

	cout << "  " << "|";
	for (int i = 0; i < a; i++)
		cout << setw(3) << i;
	cout << endl;
	cout << "--+";
	for (int i = 1; i <= a; i++)
		cout << "---";                                                    //
	cout << endl;                                                        //
	for (int i = 1; i <= a; i++)                                        //
	{                                                                  //
		cout << char(xh + i - 1) << " |";                             //
		for (int j = 1; j <= b; j++)                                 //
			if (N[i][j] == 0)                                       //
			{                                                      //
				setcolor(0, 14);                                  //
				cout << setw(3) << N[i][j];                      //
				setcolor(0, 7);                                 //
			}
			else
			{
				cout << setw(3) << N[i][j];
			}
		cout << endl;
	}       
	cout << "按回车键确认填充新值：" << endl;
	while (1)
	{
		t = ENTER();
		if (t == 0)
			break;
	}
	newfillin(max, N, a, b);

	cout << "  " << "|";
	for (int i = 0; i < a; i++)
		cout << setw(3) << i;
	cout << endl;
	cout << "--+";
	for (int i = 1; i <= a; i++)
		cout << "---";                                                    //
	cout << endl;                                                        //
	for (int i = 1; i <= a; i++)                                        //
	{                                                                  //
		cout << char(xh + i - 1) << " |";                             //
		for (int j = 1; j <= b; j++)                                 //
			if (N[i][j] == 0)                                       //
			{                                                      //
				setcolor(0, 14);                                  //
				cout << setw(3) << N[i][j];                      //
				setcolor(0, 7);                                 //
			}
			else
			{
				cout << setw(3) << N[i][j];
			}
		cout << endl;
		for (int i = 1; i <= a; i++)                           //重置标记数组               
			for (int j = 1; j <= b; j++)
			{
				W[i][j] = char(N[i][j] + '0');
			}
	}
}

int ENTER()                                                        //按enter继续
{
	char next;
	next = _getch();
	if (next == '\r')
		return 0;
	else
		return 1;
}

void newfillin(int max,int N[12][12],int a,int b)                   //按相应概率产生新值 替代0
{
	for (int i = 1; i <= a; i++)
		for (int j = 1; j <= b; j++)
		{
			if (max < N[i][j])
				max = N[i][j];
		}
	int part;
	if (max == 3)
	{
		for(int i=1;i<=a;i++)
			for (int j = 1; j <= b; j++)
			{
				if (N[i][j] == 0)
					N[i][j] = rand() % 3 + 1;
			}
	}
	else if (max == 4)
	{
		for (int i = 1; i <= a; i++)
			for (int j = 1; j <= b; j++)
			{
				part = rand() % 100;
				if (N[i][j] == 0)
				{
					if (part >= 0 && part <= 89)
						N[i][j] = rand() % 3 + 1;
					else
						N[i][j] = 4;
				}
			}

	}
	else if (max == 5)
	{
		
			for (int i = 1; i <= a; i++)
				for (int j = 1; j <= b; j++)
				{
					part = rand() % 100;
					if (N[i][j] == 0)
					{
						if (part >= 0 && part <= 74)
							N[i][j] = rand() % 3 + 1;
						else if (part >= 75 && part <= 89)
							N[i][j] = 4;
						else
							N[i][j] = 5;
					}
				}
	
	}
	else if (max == 6)
	{

		for (int i = 1; i <= a; i++)
			for (int j = 1; j <= b; j++)
			{
				part = rand() % 100;
				if (N[i][j] == 0)
				{
					if (part >= 0 && part <= 79)
						N[i][j] = rand() % 4 + 1;
					else if (part >= 80 && part <= 94)
						N[i][j] = 5;
					else
						N[i][j] = 6;
				}
			}

	}
	else
		for (int i = 1; i <= a; i++)
			for (int j = 1; j <= b; j++)
			{
				part = rand() % 100;
				if (N[i][j] == 0)
				{
					if (part >= 0 && part <= 79)
						N[i][j] = rand() % (max - 3) + 1;
					else if (part >= 80 && part <= 89)
						N[i][j] = max - 2;
					else if (part >= 90 && part <= 94)
						N[i][j] = max - 1;
					else
						N[i][j] = max;
				}
			}
}


