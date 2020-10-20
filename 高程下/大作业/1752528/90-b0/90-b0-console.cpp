/* 1752528 计2 朱世轩 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "90-b0.h"
#include"../common/cmd_console_tools.h"
#include"../common/common.h"
#include <conio.h>
using namespace std;

void frame(int a,int b,char c)                     //ab为行列数
{
	int high, wide;
	setcursor(CURSOR_INVISIBLE);
	if (c == '5')
	{
		high = a * 3 + 10;
		wide = b * 6 + 5;
	}
	if (c == '6'||c=='7'||c=='8'||c=='9')
	{
		high = a * 3 + a + 8;
		wide = b * 6 + (b + 1) * 2 + 1;
	}
		setconsoleborder(wide, high);
		cout << "屏幕当前设置为：" << high - 3 << "行" << wide << "列" << endl;
}

void border(int a, int b,char c,int & nx,int & ny)             //ab行列数  c菜单选项
{
	if (c == '5')
	{
		getxy(nx, ny);
		nx=nx+2;
		ny=ny+1;
		setcolor(15, 0);
		cout << "╔";
		for (int i = 1; i <= b * 3; i++)
		{
			Sleep(5);
			cout << "═";
		}
		cout << "╗";
		cout << endl;
		for (int i = 1; i <= a * 3; i++)
		{
			Sleep(5);
			cout << "║";
			setcolor(0, 7);
			for (int j = 1; j <= b * 6; j++)
				cout << " ";
			setcolor(15, 0);
			cout << "║"<<endl;
		}
		cout << "╚";
		for (int i = 1; i <= b * 3; i++)
		{
			Sleep(5);
			cout << "═";
		}
		cout << "╝";
		setcolor(0, 7);
	}
	if (c == '6'||c=='7'||c=='8'||c=='9')
	{
		getxy(nx, ny);
		nx = nx + 2;
		ny = ny + 1;
		setcolor(15, 0);
		cout << "╔";
		for (int i = 1; i < b ; i++)
		{
			Sleep(5);
			cout << "═══╤";
		}
		cout << "═══╗";
		cout << endl;
		for (int i = 1; i < a ; i++)
		{
			for (int j = 1; j <= 3; j++)
			{
				Sleep(5);
				cout << "║";
				for (int j = 1; j < b; j++)
					cout << "      │";
				setcolor(15, 0);
				cout << "      ║" << endl;
			}
			cout << "╟";
			for (int j = 1; j < b; j++)
				cout << "───┼";
			cout << "───╢";
		}
		for (int j = 1; j <= 3; j++)
		{
			Sleep(5);
			cout << "║";
			for (int j = 1; j < b; j++)
				cout << "      │";
			cout << "      ║";
			cout << endl;
		}
		cout << "╚";
		for (int i = 1; i < b; i++)
		{
			Sleep(5);
			cout << "═══╧";
		}
		cout << "═══╝";
		cout << endl;
		setcolor(0, 7);
	}
}

void blocks(int nx,int ny,int z)
{
	if (z < 10)
	{
		showstr(nx, ny, "╔═╗", z % 15, 0);
		showstr(nx, ny + 1, "║", z % 15, 0);
		cout << " " << z;
		showstr(nx + 4, ny + 1, "║", z % 15, 0);
		showstr(nx, ny + 2, "╚═╝", z % 15, 0);
	}
	else
	{
		showstr(nx, ny, "╔═╗", z % 15, 0);
		showstr(nx, ny + 1, "║", z % 15, 0);
		cout  << z;
		showstr(nx + 4, ny + 1, "║", z % 15, 0);
		showstr(nx, ny + 2, "╚═╝", z % 15, 0);
	}
}

void  cursor(int nx, int ny,int num)                                            //num为当前光标选中的数
{
	if (num < 10)
	{
		showstr(nx, ny, "╔═╗", 14, 9);
		showstr(nx, ny + 1, "║", 14, 9);
		cout << " " << num;
		showstr(nx + 4, ny + 1, "║", 14, 9);
		showstr(nx, ny + 2, "╚═╝", 14, 9);
	}
	else
	{
		showstr(nx, ny, "╔═╗", 14, 9);
		showstr(nx, ny + 1, "║", 14, 9);
		cout << num;
		showstr(nx + 4, ny + 1, "║", 14, 9);
		showstr(nx, ny + 2, "╚═╝", 14, 9);
	}
}

void blocksmove(int N[12][12], char W[12][12], int a, int b,char c,int &nx,int &ny,int & m,int & n)     // 移动光标函数  ab为行列数 c为菜单选项 mn为选择位置    
{
	setcursor(CURSOR_INVISIBLE);
	static int i=1;
	static int j=1;
	int num;
	while (1)
	{
		showstr(0, 4 * a + 2, "方向键移动，回车键确认选择                      ", 0, 7);
		num = N[i][j];
		cursor(nx, ny, num);
		int ret, X, Y, maction, keycode1, keycode2;
		enable_mouse();
		ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		if (ret == CCT_KEYBOARD_EVENT)
		{
			if (keycode2 == '\120')                                      //下降
			{
				if (i < a)
				{
					num = N[i][j];
					blocks(nx, ny, num);
					ny = ny + 4;
					i = i + 1;
					num = N[i][j];
					cursor(nx, ny, num);
					continue;
				}
				else
				{
					num = N[i][j];
					blocks(nx, ny, num);
					ny = ny - 4 * (a - 1);
					i = 1;
					num = N[i][j];
					cursor(nx, ny, num);
					continue;
				}
			}
			if (keycode2 == '\110')                                      //上升
			{
				if (i > 1)
				{
					num = N[i][j];
					blocks(nx, ny, num);
					ny = ny - 4;
					i = i - 1;
					num = N[i][j];
					cursor(nx, ny, num);
					continue;
				}
				else
				{
					num = N[i][j];
					blocks(nx, ny, num);
					ny = ny + 4 * (a - 1);
					i = a;
					num = N[i][j];
					cursor(nx, ny, num);
					continue;
				}

			}
			if (keycode2 == '\113')                                      //左移
			{
				if (j > 1)
				{
					num = N[i][j];
					blocks(nx, ny, num);
					nx = nx - 8;
					j = j - 1;
					num = N[i][j];
					cursor(nx, ny, num);
					continue;
				}
				else
				{
					num = N[i][j];
					blocks(nx, ny, num);
					nx = nx + 8 * (b - 1);
					j = b;
					num = N[i][j];
					cursor(nx, ny, num);
					continue;
				}
			}
			if (keycode2 == '\115')                                      //右移
			{
				if (j < b)
				{
					num = N[i][j];
					blocks(nx, ny, num);
					nx = nx + 8;
					j = j + 1;
					num = N[i][j];
					cursor(nx, ny, num);
					continue;
				}
				else
				{
					num = N[i][j];
					blocks(nx, ny, num);
					nx = nx - 8 * (b - 1);
					j = 1;
					num = N[i][j];
					cursor(nx, ny, num);
					continue;
				}
			}
			if (keycode1 == '\r')
				break;
		}
		else if (ret == CCT_MOUSE_EVENT)
		{
			for (int m = 1; m <= a; m++)
				for (int n = 1; n <= b; n++)
				{
					int nx1 = 8 * n - 6;
					int ny1 = 4 * m - 2;
					if (X >= nx1 && X <= nx1 + 5 && Y >= ny1 && Y <= ny1 + 2)
					{
						blocks(nx, ny, num);
						cursor(nx1, ny1, N[(nx1 + 6) / 8][(ny1 + 2) / 4]);
						nx = nx1;
						ny = ny1;
						i = m;
						j = n;
					}
				}
			if (maction == MOUSE_LEFT_BUTTON_CLICK)
				break;
		}
	}
	if (c == '7')
		gotoxy(0, 4 * a + 3);
	else if (c == '8' || c == '9')
	{
		m = i;
		n = j;
	}
}



char compound_cmd(char W[12][12], int N[12][12], int a, int b, char choose, int a1, int b1, int & score, int goal, int & max)         //完成一次合成  ab为行列数 a1 b1为目标数 goal为合成目标
{
	
	max = 3;                                           //记录合成后最大值
	int sbc = 0;                                          //本次得分
	int g = N[a1][b1] + 1;                            //g为合成后的值
	gotoxy(0, 0);
	for (int i = 1; i <= a; i++)
		for (int j = 1; j <= b; j++)
		{
			if (W[i][j] == '*')
			{
				N[i][j] = 0;
				sbc = sbc + 3 * (g - 1);
			}
		}
	N[a1][b1] = g;
	for (int i = 1; i <= a; i++)
		for (int j = 1; j <= b; j++)
		{

			if (N[i][j] == 0)
			{
				int nx2 = 8 * j - 6;
				int ny2 = 4 * i - 2;
				showstr(nx2, ny2, "      ", 15 , 15);
				showstr(nx2, ny2 + 1, "      ", 15 , 15);
				showstr(nx2, ny2 + 2, "      ", 15, 15);
			}
		}
	int nx3 = 8 * b1 - 6;
	int ny3 = 4 * a1 - 2;
	for (int t = 0; t < 9; t++)
	{
		Sleep(70);
		if (g < 10)
		{
			showstr(nx3, ny3, "╔═╗", t, 9);
			showstr(nx3, ny3 + 1, "║", t, 9);
			cout << " " << g;
			showstr(nx3 + 4, ny3 + 1, "║", t, 9);
			showstr(nx3, ny3 + 2, "╚═╝", t, 9);
		}
		else
		{
			showstr(nx3, ny3, "╔═╗", t, 9);
			showstr(nx3, ny3 + 1, "║", t, 9);
			cout << g;
			showstr(nx3 + 4, ny3 + 1, "║", t, 9);
			showstr(nx3, ny3 + 2, "╚═╝", t, 9);
		}
	}
	                 
	if (choose == '8')
	{
		showstr(0,4*a+2 , "合成完成，按enter下落                   ", 0, 7);
		while (1)
		{
			int t = ENTER();
			if (t == 0)
				break;
		}
	}
	score = score + sbc;
	gotoxy(0, 0);
	setcolor(0, 7);
	cout << "本次得分：" << sbc << "总得分：" << score << "                    ";






for(int i=1;i<20;i++)
	for (int i = 1; i <= a ; i++)                                            //实现0下落
		for (int j = 1; j <= b; j++)
		{
			if (N[i][j] != 0 && N[i + 1][j] == 0)
			{
				int nx4 = 8 * j - 6;
				int ny4 = 4 * i - 2;
				Sleep(30);
				showstr(nx4, ny4, "      ", 15, 15);
				blocks(nx4, ny4 + 1, N[i][j]);
				showstr(nx4, ny4 + 1, "      ", 15, 15);
				blocks(nx4, ny4 + 2, N[i][j]);
				showstr(nx4, ny4 + 2, "      ", 15, 15);
				blocks(nx4, ny4 + 3, N[i][j]);
				showstr(nx4, ny4 + 3, "———", 15, 0);
				blocks(nx4, ny4 + 4, N[i][j]);
				N[i + 1][j] = N[i][j];
				N[i][j] = 0;
				W[i + 1][j] = W[i][j];
				W[i][j] = '0';
			}
		}
if (choose == '8')
{
	showstr(0, 4 * a + 2, "下落完成，按enter填充                               ", 0, 7);
	while (1)
	{
		int t = ENTER();
		if (t == 0)
			break;
	}
	showstr(0, 4 * a + 2, "                               ", 0, 7);
}
	newfillin(max, N, a, b);                              //新值填充
	for (int i = 1; i <= a; i++)                                            
		for (int j = 1; j <= b; j++)
		{
				Sleep(15);
				int nx3 = 8 * j - 6;
				int ny3 = 4 * i - 2;
				if (N[i][j] < 10)
				{
					showstr(nx3, ny3, "╔═╗", N[i][j] % 15, 0);
					showstr(nx3, ny3 + 1, "║", N[i][j] % 15, 0);
					cout << " " << N[i][j];
					showstr(nx3 + 4, ny3 + 1, "║", N[i][j] % 15, 0);
					showstr(nx3, ny3 + 2, "╚═╝", N[i][j] % 15, 0);
				}
				else
				{
					showstr(nx3, ny3, "╔═╗", N[i][j] % 15, 0);
					showstr(nx3, ny3 + 1, "║", N[i][j] % 15, 0);
					cout << N[i][j];
					showstr(nx3 + 4, ny3 + 1, "║", N[i][j] % 15, 0);
					showstr(nx3, ny3 + 2, "╚═╝", N[i][j] % 15, 0);
				}
		}
	for (int i = 1; i <= a; i++)                                      
		for (int j = 1; j <= b; j++)
		{
			if (max < N[i][j])
				max = N[i][j];
		}
	for (int i = 1; i <= a; i++)                           //重置标记数组               
		for (int j = 1; j <= b; j++)
		{
			W[i][j] = char(N[i][j] + '0');
		}
	char ch='0';
	if (choose == '8')
	{
		while (1)
		{
			showstr(0, 4 * a + 2, " 本次合成已完成，按c进行一次新的合成                          ", 0, 7);
			ch = _getch();
			if (ch == 'c')
			{
				break;
			}
		}
		return ch;
	}
	
	return ch;
}


