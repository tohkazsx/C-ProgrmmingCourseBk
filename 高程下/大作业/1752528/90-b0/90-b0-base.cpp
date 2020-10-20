/* 1752528 计2 朱世轩 */
#include <iostream>
#include <ctime>
#include<iomanip>
#include <cmath>
#include <cstdio>
#include<fstream>
#include <conio.h>
#include <Windows.h>
#include"../common/common.h"
#include "../common/cmd_console_tools.h"
#include "90-b0.h"
using namespace std;

void Narray(char c, int game, const char *filename)                 //生成随机数组并输出初始数组
{
	int row, col;
	int max;                 //记录数组当前最大值
	int z;                    //记录数组值
	int a, b;              //a,b 为目标点在数组中的序号
	int x;                 //目标数
	int goal;             //合成目标
	char ynq;              //选项
	int score=0;             //记录分数
	int nx, ny;     //  记录伪图形界面内部开始打印方块位置
	char xu='A';
	int Narray[12][12];
	char Warray[12][12];
	char p[4];
	char * point=p;
	for(int i = 0; i<12; i++)
		for (int j = 0; j < 12; j++)
		{

			Narray[i][j] = -1;
			Warray[i][j] = '0';
		}
	srand((unsigned)time(NULL));
	
if (c == '1' || c == '2' || c == '3' || c == '4'||c=='5'|| c=='6' ||c=='7' ||c=='8'|| c == '9')
{
	    cout << "请输入行数（5-8）：";
		CIN(&row, 5, 8);
		cout << "请输入列数（5-10）：";
		CIN(&col, 5, 10);
	for(int i=1;i<=row;i++)
        for (int j = 1; j <= col; j++)
		{
			Narray[i][j] = rand() % 3 + 1;
			Warray[i][j] = Narray[i][j]+'0';
		}
		
		if (c == '3' || c == '4'||c=='8'||c=='9')
		{
			cout << "请输入合成目标(5-20)：";
			CIN(&goal, 5, 20);
		}
		if (c == '1' || c == '2' || c == '3' || c == '4')
		{
			cout << "当前数组：" << endl;       //输出原数组
			printarray(Warray, Narray, row, col, game, 0);
		}
		if (c == '1' || c == '2' || c == '3' || c == '4')
		{
			while (1)
			{
				location(row, col, point, Warray, Narray);        //定位 a,b 为目标点在数组中的序号

				a = *point - 'A' + 1;
				b = *(point + 1) - '0' + 1;
				x = Narray[a][b];
				Warray[a][b] = '*';
				if (c == '1')
				{
					search(x, Warray, row, col);    //非递归
				}

				if (c == '2' || c == '3' || c == '4')
				{
					search_dg(x, Warray, a, b);       //递归
					for (int i = 1; i <= row; i++)
						for (int j = 1; j <= col; j++)
						{
							if (Warray[i][j] != '*')
								Warray[i][j] = '0';
						}
				}


				if (c == '1' || c == '2' || c == '3' || c == '4')
				{
					cout << "检查结果数组：" << endl;       //输出检查结果数组
					printarray(Warray, Narray, row, col, game, 1);
				}
				highlight(Warray, Narray, row, col,game);
				if (c == '3' || c == '4')
				{
					ynq = YNQ(a, b);
					if (ynq == 'Y')
					{
						compound(Warray, Narray, xu, row, col, c, a, b, score, goal, max);            //一次合成
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
					if (c == '4')
					{
						if (max == goal)
						{
							setcolor(14, 7);
							cout << "已合成到" << goal;
							setcolor(0, 7);

							cout << " 按回车键继续合成";
						}
						else
							cout << "本次合成结束，按回车键进行一次新的合成：" << endl;
						while (1)
						{
							int t = ENTER();
							if (t == 0)
								break;
						}
						continue;

					}

				}

			}
		}
	}
	if (c == '5' || c == '6'||c == '7'||c=='8'||c=='9')                      //伪图形
	{
		
			frame(row, col, c);
			border(row, col, c, nx, ny);
			for (int i = 1; i <= row; i++)
			{
				for (int j = 1; j <= col; j++)
				{
					z = Narray[i][j];
					blocks(nx, ny, z);
					if(c=='5')
					    nx = nx + 6;
					if(c=='6'||c=='7'||c=='8'||c=='9')
						nx = nx + 8;
				}
				if (c == '5')
				{
					nx = nx - 6 * col;
					ny = ny + 3;
				}
				if (c == '6'||c == '7'||c=='8'||c=='9')
				{
					nx = nx - 8 * col;
					ny = ny + 4;
				}
			}
			if (c == '7'||c=='8'||c=='9')
			{
				getxy(nx, ny);
				nx = nx - 8 * col + 2;
				cout << endl;
				cout << endl;
				showstr(0, 4 * row + 2, "方向键/鼠标移动，回车键选择", 0, 15);
				ny = ny - 4 * row + 2;
				gotoxy(nx, ny);
			}
			
			setcolor(0, 7);
			cout << endl;
			cout << endl;
			if (c == '7')
			{
				blocksmove(Narray, Warray, row, col, c, nx, ny, a, b);
				
			}
			if (c == '8' || c == '9')
			{
				while (1)
				{
					blocksmove(Narray, Warray, row, col, c, nx, ny, a, b);
					nx = 8 * b - 6;
					ny = 4 * a - 2;
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
						showstr(0, 4 * row + 2, "   周围无相同值，箭头键移动，回车键确认", 0, 14);
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
									ny1 = 4 * i - 2;
									nx1 = 8 * j - 6;
									showstr(nx1, ny1, "╔═╗", 14, 9);
									showstr(nx1, ny1 + 1, "║", 14, 9);
									cout << " " << Narray[i][j];
									showstr(nx1 + 4, ny1 + 1, "║", 14, 9);
									showstr(nx1, ny1 + 2, "╚═╝", 14, 9);
									showstr(0, 4 * row + 2, "箭头键移动并取消当前选择，回车键确认合成", 14, 9);
								}
							}
					}

					cursor(nx, ny, Narray[a][b]);
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
										if (Warray[i][j] == '*')
										{
											int ny1 = 4 * i - 2;
											int nx1 = 8 * j - 6;
											showstr(nx1, ny1, "╔═╗", Narray[i][j] % 15, 0);
											showstr(nx1, ny1 + 1, "║", Narray[i][j] % 15, 0);
											cout << " " << Narray[i][j];
											showstr(nx1 + 4, ny1 + 1, "║", Narray[i][j] % 15, 0);
											showstr(nx1, ny1 + 2, "╚═╝", Narray[i][j] % 15, 0);
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
								char cmd = compound_cmd(Warray, Narray, row, col, c, a, b, score, goal, max);
								if (max > goal - 1)
								{
									showstr(0, 4 * row + 3, "已达到合成目标", 14, 9);
									setcolor(14, 9);
									cout << goal;
									setcolor(0, 7);
									showstr(16, 4 * row + 3, "向更高数字进发", 14, 9);
								}
								break;
							}

						}
						else if (ret == CCT_KEYBOARD_EVENT)
						{
							if (keycode1 != '\r')
							{
								int nx1 = 3, ny1 = 3;
								for (int i = 1; i <= row; i++)
									for (int j = 1; j <= col; j++)
									{
										if (Warray[i][j] == '*')
										{
											ny1 = 4 * i - 2;
											nx1 = 8 * j - 6;
											showstr(nx1, ny1, "╔═╗", Narray[i][j] % 15, 0);
											showstr(nx1, ny1 + 1, "║", Narray[i][j] % 15, 0);
											cout << " " << Narray[i][j];
											showstr(nx1 + 4, ny1 + 1, "║", Narray[i][j] % 15, 0);
											showstr(nx1, ny1 + 2, "╚═╝", Narray[i][j] % 15, 0);
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

										blocks(nx, ny, Narray[a][b]);
										ny = ny + 4;
										a = a + 1;
										cursor(nx, ny, Narray[a][b]);
									}
									else
									{
										blocks(nx, ny, Narray[a][b]);
										ny = ny - 4 * (a - 1);
										a = 1;
										cursor(nx, ny, Narray[a][b]);
									}


								}
								if (keycode2 == '\110')                                      //上升
								{
									if (a > 1)
									{

										blocks(nx, ny, Narray[a][b]);
										ny = ny - 4;
										a = a - 1;
										cursor(nx, ny, Narray[a][b]);

									}
									else
									{
										blocks(nx, ny, Narray[a][b]);
										ny = ny + 4 * (col - 1);
										a = row;
										cursor(nx, ny, Narray[a][b]);
									}

								}
								if (keycode2 == '\113')                                      //左移
								{
									if (b > 1)
									{
										blocks(nx, ny, Narray[a][b]);
										nx = nx - 8;
										b = b - 1;
										cursor(nx, ny, Narray[a][b]);

									}
									else
									{
										blocks(nx, ny, Narray[a][b]);
										nx = nx + 8 * (row - 1);
										b = col;
										cursor(nx, ny, Narray[a][b]);

									}

								}
								if (keycode2 == '\115')                                      //右移
								{
									if (b < col)
									{
										blocks(nx, ny, Narray[a][b]);
										nx = nx + 8;
										b = b + 1;
										cursor(nx, ny, Narray[a][b]);

									}
									else
									{
										blocks(nx, ny, Narray[a][b]);
										nx = nx - 8 * (b - 1);
										b = 1;
										cursor(nx, ny, Narray[a][b]);

									}

								}
							}
							else if (keycode1 == '\r')
							{
								char cmd = compound_cmd(Warray, Narray, row, col, c, a, b, score, goal, max);
								if (max > goal - 1)
								{
									showstr(0, 4 * row + 3, "已达到合成目标", 14, 9);
									setcolor(14, 9);
									cout << goal;
									setcolor(0, 7);
									showstr(16, 4 * row + 3, "向更高数字进发", 14, 9);
								}
								int count = 0;
								for (int i = 1; i <= row; i++)
									for (int j = 1; j <= col; j++)
									{
										if (Narray[i][j] != 0 && (Narray[i][j] == Narray[i + 1][j] || Narray[i][j] == Narray[i][j + 1] || Narray[i][j] == Narray[i - 1][j] || Narray[i][j] == Narray[i][j - 1]))
										{
											count = count + 1;
										}
									}
								if (count == 0)
								{
									cout << "无可继续合成的数，游戏结束";
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
				}
			}
				
			
	
	    }
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
	char a1, b1,ynq;
	int x, y;
	a1 = char(a + 'A' - 1);
	b1 = char(b + '0' - 1);
	cout << "请确认是否要将相邻相同值合并到" << a1 << b1 << "中（Y/N/Q）：";
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


