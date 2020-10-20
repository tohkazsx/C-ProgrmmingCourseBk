/* 1752528 计2 朱世轩 */
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include"../common/common.h"
#include "../common/cmd_console_tools.h"
using namespace std;

void CIN(int*s, int a, int b)              //输入检查  报错  s为输入数据 ab是正确范围
{
	while (1)
	{
		int x, y;
		getxy(x, y);
		cin >> *s;
		if (!cin.good())
		{
			cout << "输入非法请重新输入：";
			cin.clear();
			cin.ignore(1024, '\n');
			gotoxy(x, y);
			continue;
		}
		else if (*s > b || *s < a)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入非法请重新输入：";
			gotoxy(x, y);
			continue;
		}
		else
			break;
	}
	cin.ignore(1024, '\n');
}
void location(int a, int b, char * point, char W[ar][ar], int N[ar][ar])                       //取得目标点坐标 ab为行列数
{
	char loc[4];
	int a1, b1;                                                                            //a1,b1为在数组中位置
	int x, y;
	getxy(x, y);
	cout << "请以字母+数字形式[例：c2]输入矩阵坐标：";
	while (1)
	{
		gets_s(loc);
		if (loc[0] >= 'a'&&loc[0] <= 'z')
			loc[0] = loc[0] - 32;
		if (loc[0] >= 'A'&&loc[0] <= char('A' + a - 1) && loc[1] >= '0'&&loc[1] <= 'col')
		{
			a1 = loc[0] - 'A' + 1;
			b1 = loc[1] - '0' + 1;
			if (W[a1 + 1][b1] != W[a1][b1] && W[a1 - 1][b1] != W[a1][b1] && W[a1][b1 + 1] != W[a1][b1] && W[a1][b1 - 1] != W[a1][b1])
			{
				cout << "目标点周围无相同值，请重新输入";
				continue;
			}
			else if (W[a1][b1] == '0')
			{
				cout << "目标点为0位置非法，请重新输入";
			}
			else
				break;
		}

		else
		{
			cout << "输入不合法 请重新输入";
			gotoxy(x, y);
		}
	}
	cout << "输入为" << loc[0] << "行" << loc[1] << "列" << endl;
	*point = loc[0];
	*(point + 1) = loc[1];
}
void tips(int a, int b,int num,int score,const int length,const int wide,const int mode)                   //ab行列数  侧边框显示提示信息
{
	int nx, ny;
	nx = b * 6 + 4;
	ny = 0;
	setcolor(14, 0);
	gotoxy(nx, ny);
     cout << "╔";
	 for (int i = 1; i <= wide; i++)
	 {
		 Sleep(5);
		 cout << "═";
	 }
	 cout << "╗";
	 cout << endl; 
	
	 for (int i = 1; i <= length; i++)
	 {
		 ny = i;
		 gotoxy(nx, ny);
		 cout << "║";
		 for (int j = 1; j <= wide; j++)
			 cout << "  ";
		 cout << "║" << endl;
	 } 
	 ny = 4 + (a - 1) * 3;
	 gotoxy(nx, ny);
	 cout << "╚";
	 for (int i = 1; i <= wide; i++)
	 {
		 cout << "═";
	 }
	 cout << "╝";
	 setcolor(0, 7);
	 nx = nx + 6;
	 ny = (a / 2) * 3 - 10;
	 showstr(nx, ny, "★数字俄罗斯方块★", 14, 7);
	 showstr(nx, ny + 2, "游戏开始", 14, 7);
	 showstr(nx, ny + 4, "游戏说明：", 14, 7);
	 showstr(nx, ny + 6, "左右方向键移动", 14, 7);
	 showstr(nx, ny + 8, "上方向键旋转", 14, 7);
	 showstr(nx, ny + 10, "下方向键加速下落", 14, 7);
	 showstr(nx, ny + 12, "鼠标点击任意位置暂停", 14, 7);
	 if (mode == 1)
	 {
		 showstr(nx, ny + 14, "当前数字：", 14, 7);
		 cout << num;
		 showstr(nx, ny + 16, "您的得分：", 14, 7);
		 cout << score;
	 }
	 if (mode == 2)
	 {
		 showstr(nx, ny + 14, "游戏结束！", 14, 3);
		 showstr(nx, ny + 16, "您最后的数字为：", 14, 3); 
		 cout << num;
		 showstr(nx, ny + 18, "按c键再试一次？", 14, 3);
		 showstr(nx, ny + 20, "按其他键退出游戏", 14, 3);
		
	 }
}


