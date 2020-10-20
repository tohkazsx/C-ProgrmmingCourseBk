/* 1752528 计2 朱世轩 */
#include <iostream>
#include <ctime>
#include<iomanip>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include"../common/common.h"
#include "../common/cmd_console_tools.h"
#include "90-b1.h"
using namespace std;

char Narray(char c,int game,char last,int & lasta,int & lastb)              //生成随机数组并输出初始数组
{
	int row, col;
	int max;                 //记录数组当前最大值
	int z;                    //记录数组值
	int a, b;              //a,b 为目标点在数组中的序号
	int x;                 //目标数
	char ynq;              //选项
	int score = 0;             //记录分数
	int nx, ny;     //  记录伪图形界面内部开始打印方块位置
	char xu = 'A';
	int Narray[12][12];
	char Warray[12][12];
	char p[4];
	char * point = p;
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 12; j++)
		{

			Narray[i][j] = -1;
			Warray[i][j] = '0';
		}
	srand((unsigned)time(NULL));

	if (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F' || c == 'G')
	{
		if (last == 'c')
		{
			row = lasta + 1;
			col = lastb + 1;
		}
		else
		{
			cout << "请输入行数（8-10）：";
			CIN(&row, 8, 10);
			cout << "请输入列数（8-10）：";
			CIN(&col, 8, 10);
			lasta = row;
			lastb = col;
		}
		for (int i = 1; i <= row; i++)
			for (int j = 1; j <= col; j++)
			{
				Narray[i][j] = rand() % 5 + 1;
				Warray[i][j] = Narray[i][j] + '0';
			}
		

		if (c == 'A' || c == 'B' || c == 'C')
		{
			cout << "当前数组：" << endl;       //输出原数组
			printarray(Warray, Narray, row, col, game, 0);
		}
		if (c == 'A' || c == 'B' || c == 'C')
		{
			while (1)
			{
				

				location(row, col, point, Warray, Narray);        //定位 a,b 为目标点在数组中的序号

				a = *point - 'A' + 1;
				b = *(point + 1) - '0' + 1;
				x = Narray[a][b];
				Warray[a][b] = '*';

				if (c == 'A' || c == 'B' || c == 'C')
				{
					search_dg(x, Warray, a, b);       //递归
					for (int i = 1; i <= row; i++)
						for (int j = 1; j <= col; j++)
						{
							if (Warray[i][j] != '*')
								Warray[i][j] = '0';
						}
				}


				if (c == 'A' || c == 'B' || c == 'C')
				{
					cout << "检查结果数组：" << endl;       //输出检查结果数组
					printarray(Warray, Narray, row, col, game, 0);
				}
				highlight(Warray, Narray, row, col,game);
				if (c == 'A')
					break;
				if (c == 'B' || c == 'C')
				{
					ynq = YNQ(a, b);
					if (ynq == 'Y')
					{
						compound(Warray, Narray, xu, row, col, c, a, b, score, max);            //一次合成
		
						
						}
					}
					if (ynq == 'Q')
					{
						break;
					}
					if (ynq == 'N')
					{
						cout << endl;
						cout << "当前数组：" << endl;       //输出原数组
						printarray(Warray, Narray, row, col, game, 0);
						continue;
					}
					if (c == 'B')
					{
						break;
					}
					if (c == 'C')
					{
						if (score > 1000)
						{
							setcolor(14, 7);
							cout << "已达到过关得分" << 1000;
							setcolor(0, 7);
							cout << endl;
							cout << " 按回车键继续消除";
						}
						else
						{	
							cout << "本次消除结束，按回车键进行一次新的消除：" << endl;
						}
						
						while (1)
						{
							int t = ENTER();
							if (t == 0)
								break;
						}
						
                        cout << endl;
						cout << "当前数组：";
						cout << endl;
						printarray(Warray, Narray, row, col, game, 0);
						char c = gameover(row, col, Narray, Warray, game);
							if (c == 'c')
								break;

				}
              
			}
		}
	}
	if (c == 'D' || c == 'E' || c == 'F' || c == 'G')                      //伪图形
	{

		frame(row, col, c);
		if (c == 'D' || c == 'F' || c == 'G')
			free_border(row, col, nx, ny, 0, 1);
		if (c == 'E')
			free_border(row, col, nx, ny, 1, 0);
		for (int i = 1; i <= row; i++)
		{
			for (int j = 1; j <= col; j++)
			{
				z = Narray[i][j];
				free_blocks(nx, ny, z, game);
				if (c == 'D' || c == 'F' || c == 'G')
					nx = nx + 6;
				if (c == 'E')
					nx = nx + 8;
			}
			if (c == 'D' || c == 'F' || c == 'G')
			{
				nx = nx - 6 * col;
				ny = ny + 3;
			}
			if (c == 'E')
			{
				nx = nx - 8 * col;
				ny = ny + 4;
			}
		}

		setcolor(0, 7);
		cout << endl;
		cout << endl;
		if (c == 'E'||c=='D')
		{
			blocksmove(Narray, Warray, row, col, c, nx, ny, a, b,game,1);
		}
		if (c == 'F' || c == 'G')
		{
			char ch;                                                          //记录关卡是否结束信息
			while (1)
			{
				blocksmove(Narray, Warray, row, col, c, nx, ny, a, b, game,0);
				nx = 6 * b - 2;
				ny = 3 * a;
				Warray[a][b] = '*';
				search(Narray[a][b], Warray, row, col);
				int pd = 0;
				for (int i = 1; i <= row; i++)
					for (int j = 1; j <= col; j++)
					{
						if (Warray[i][j] == '*')
							pd = pd + 1;
					}
				if (pd == 1)
				{
					Warray[a][b] = Narray[a][b] + '0';
					showstr(2, 3 * row + 4, "   周围无相同值，箭头键移动，回车键确认", 0, 14);
					resetarray(Warray, Narray, row, col);
					continue;
				}
				else
				{
					for (int i = 1; i <= row; i++)
						for (int j = 1; j <= col; j++)
						{
							if (Warray[i][j] == '*')
							{
								int nx1, ny1;
								ny1 = 3 * i;
								nx1 = 6 * j - 2;
								showstr(nx1, ny1, "╔═╗", Narray[i][j]%15 + 8, 15);
								showstr(nx1, ny1 + 1, "║", Narray[i][j] % 15 + 8, 15);
								cout << "★";
								showstr(nx1 + 4, ny1 + 1, "║", Narray[i][j] % 15 + 8, 15);
								showstr(nx1, ny1 + 2, "╚═╝", Narray[i][j] % 15 + 8, 15);
								showstr(2, 3 * row + 4, "箭头键移动并取消当前选择，回车键确认合成", 0, 15);
							}
						}
				}
				free_cursor(nx, ny, Narray[a][b], game);
				int ret, X, Y, maction, keycode1, keycode2;
				while (1)
				{
					ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
					if (ret == CCT_MOUSE_EVENT)
					{
						if (X < nx || X > nx + 5 || Y < ny || Y > ny + 2)
						{
							for (int i = 1; i <= row; i++)
								for (int j = 1; j <= col; j++)
								{
										int ny1 = 3 * i ;
										int nx1 = 6 * j - 2;
										if (Narray[i][j] != 0)
										{
											showstr(nx1, ny1, "╔═╗", Narray[i][j] % 15 + 8, 0);
											showstr(nx1, ny1 + 1, "║", Narray[i][j] % 15 + 8, 0);
											cout << "★";
											showstr(nx1 + 4, ny1 + 1, "║", Narray[i][j] % 15 + 8, 0);
											showstr(nx1, ny1 + 2, "╚═╝", Narray[i][j] % 15 + 8, 0);
										}
										else
										{
											showstr(nx1, ny1, "      ", 15, 15);
											showstr(nx1, ny1+1, "      ", 15, 15);
											showstr(nx1, ny1+2, "      ", 15, 15);
										}
								}
							for (int i = 1; i <= row; i++)
								for (int j = 1; j <= col; j++)
								{
									Warray[i][j] = Narray[i][j] + '0';
								}
							break;
						}
						if (maction == MOUSE_LEFT_BUTTON_CLICK)
						{
								char cmd = compound_cmd(Warray, Narray, row, col, c, a, b, score, game);
								ch = gameover(row, col, Narray, Warray, game);
								if (ch == 'c')
								{
									break;
								}
								break;
						}

					}
					else if (ret == CCT_KEYBOARD_EVENT)
					{
						if (keycode1 != '\r')
						{
							for (int i = 1; i <= row; i++)
								for (int j = 1; j <= col; j++)
								{
									if (Warray[i][j] != '0')
									{
										int ny1 = 3 * i;
										int nx1 = 6 * j - 2;
										showstr(nx1, ny1, "╔═╗", Narray[i][j] % 15+8, 0);
										showstr(nx1, ny1 + 1, "║", Narray[i][j] % 15+8, 0);
										cout << "★";
										showstr(nx1 + 4, ny1 + 1, "║", Narray[i][j] % 15+8, 0);
										showstr(nx1, ny1 + 2, "╚═╝", Narray[i][j] % 15+8, 0);
									}
								}
							for (int i = 1; i <= row; i++)
								for (int j = 1; j <= col; j++)
								{
									Warray[i][j] = Narray[i][j] + '0';
								}

							if (keycode2 == '\120')                                      //下降
							{
								if (a < row)
								{

									free_blocks(nx, ny, Narray[a][b],game);
									ny = ny + 3;
									a = a + 1;
								}
								else
								{
									free_blocks(nx, ny, Narray[a][b], game);
									ny = ny - 3 * (a - 1);
									a = 1;
								}


							}
							if (keycode2 == '\110')                                      //上升
							{
								if (a > 1)
								{

									free_blocks(nx, ny, Narray[a][b], game);
									ny = ny - 3;
									a = a - 1;

								}
								else
								{
									free_blocks(nx, ny, Narray[a][b], game);
									ny = ny + 3 * (col - 1);
									a = row;
								}

							}
							if (keycode2 == '\113')                                      //左移
							{
								if (b > 1)
								{
									free_blocks(nx, ny, Narray[a][b], game);
									nx = nx - 6;
									b = b - 1;
								}
								else
								{
									free_blocks(nx, ny, Narray[a][b], game);
									nx = nx + 6 * (row - 1);
									b = col;
								}

							}
							if (keycode2 == '\115')                                      //右移
							{
								if (b < col)
								{
									free_blocks(nx, ny, Narray[a][b], game);
									nx = nx + 6;
									b = b + 1;
								}
								else
								{
									free_blocks(nx, ny, Narray[a][b], game);
									nx = nx - 6 * (b - 1);
									b = 1;
								}

							}
						}
						else if (keycode1 == '\r')
						{
							char cmd = compound_cmd(Warray, Narray, row, col, c, a, b, score, game);
							ch= gameover(row, col, Narray, Warray,  game);
							if (ch == 'c')
							{
								break;
							}
							if (cmd == 'c')
								break;
							else
								continue;
						}
						break;
					}
				}
				if (ch == 'c')
				{
					return 'c';
					break;
				}
				else
					continue;
			}

		}
	}
	return '0';
}

void resetarray(char W[12][12], int N[12][12], int a, int b)                      //重新输入前重置数组
{
	int i, j;
	for (i = 1; i <= a; i++)
		for (j = 1; j <= b; j++)
		{
			W[i][j] = char(N[i][j] + '0');
		}
}


char YNQ(int a, int b)                                    //输入选项 合成 取消 退出
{
	char a1, b1, ynq;
	int x, y;
	a1 = char(a + 'A' - 1);
	b1 = char(b + '0' - 1);
	cout << "请确认是否要将相邻相同值消除"  <<"<Y/N/Q>：";
	getxy(x, y);
	while (1)
	{
		gotoxy(x, y);
		ynq = _getch();
		cout << ynq;
		if (ynq >= 'a'&&ynq <= 'z')
			ynq = ynq - 32;
		if (ynq == 'Y' || ynq == 'Q' || ynq == 'N')
			break;
	}
	return ynq;
}

