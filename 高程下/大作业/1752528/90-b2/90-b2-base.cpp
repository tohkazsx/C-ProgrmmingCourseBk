/*朱世轩 计2 1752528*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <time.h> 
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include<fstream>
#include "../common/cmd_console_tools.h"
#include "../common/common.h"
#include "90-b2.h"
using namespace std;
char tetris(char choose, int game, char & last)
{
	int X = 0;
	int Y = 0;
	int endflag = 0;
	int score = 0;
	int numnow;
	int spinflag = 0;
	int count = 0;
	int row, col;                           //记录数字方块第一个小方块的位置
	char c = '0';
	int map[YL][XL];
	int blocks[5][3] = { 0 };

	if (choose == 'Y')
	{
		for (int i = 0; i < YL; i++)                       //给范围内数组赋初值
			for (int j = 0; j < XL; j++)
			{
				map[i][j] = 3;
			}
		for (int i = 1; i < YL - 1; i++)                       //给范围内数组赋初值
			for (int j = 1; j < XL - 1; j++)
			{
				map[i][j] = 0;
			}

		setconsoleborder((XL - 1) * 6 + 30, (YL - 1) * 3 + 50);
		free_border(YL - 2, XL - 2, X, Y, 0, 0);
		tips(YL - 2, XL - 2, 0, 0, (YL - 2) * 3, 13, 0);
		for (int i = 1; i < YL - 1; i++)
			for (int j = 1; j < XL - 1; j++)
			{
				X = (j - 1) * 6 + 2;
				Y = (i - 1) * 3 + 1;
				free_blocks(X, Y, map[i][j], game);
			}


		char i, hc;
		int a[30];
		ifstream fin; //fin 为变量名 
		fin.open("tetris.dat", ios::in);//打开文件 
		srand((unsigned)time(NULL));
		for (i = 0; i < 30; i++)
		{
			a[i] = rand() % 10;
		}
		if (fin.is_open())
		{

			for (i = 0; i < 30; )
			{
				fin >> hc;
				if (hc >= '0'&&hc <= '9')
				{
					a[i] = hc - '0';
					i++;
				}
			}
			fin.close(); //关闭文件 
		}
		for (i = 0; i < 30; i++)
		{
			/*setcolor(6, 5);
			cout << a[i];*/
			//test
			numnow = a[i];
			numberblocks(blocks, a[i]);
			changearray(blocks, map, 0);
			tips(YL - 2, XL - 2, a[i], score, (YL - 2) * 3, 13, 1);
			while (1)
			{
				int keycode;
				if (_kbhit())
				{
					keycode = _getch();
					if (keycode == '\120') //下键
					{
						fall(map, blocks, game, row, col, endflag);
						count = count + 1;
					}
					if (keycode == '\113') //左键
					{
						turn_left(map, blocks, game, row, col);
					}
					if (keycode == '\115') //右键
					{
						turn_right(map, blocks, game, row, col);
					}
					if (keycode == '\110') //下键
					{
						spin(map, blocks, game, row, col, spinflag);
					}

					/*gotoxy(0,62);
					setcolor(6, 5);
					for (int i = 0; i < YL; i++)           //test
					{
						for (int j = 0; j < XL; j++)
							cout << map[i][j] << " ";
						cout << endl;
					}
					Sleep(200);
					*/
					continue;
				}
				Sleep(240);
				fall(map, blocks, game, row, col, endflag);
				count = count + 1;
				/*gotoxy(0, 68);
				setcolor(6, 5);
				for (int i = 0; i < YL; i++)           //test   测试内部数组
				{
					for (int j = 0; j < XL; j++)
						cout << map[i][j] << " ";
					cout << endl;
				}
				*/



				if (count >= YL - 3 || endflag == 1)
				{
					for (int i = 1; i < YL - 1; i++)
						for (int j = 1; j < XL - 1; j++)
						{
							if (map[i][j] == 1)
								map[i][j] = 3;
							if (map[i][j] == 2)
								map[i][j] = 4;
						}
					count = 0;
					endflag = 0;
					spinflag = 0;
					for (int i = 1; i < YL - 1; i++)                            //消除一行
					{
						int xc = 0;
						for (int j = 1; j < XL - 1; j++)
						{
							if (map[i][j] == 3)
								xc = xc + 1;
						}
						if (xc == XL - 2)
						{
							for (int j = 1; j < XL - 1; j++)
								map[i][j] = 0;
							mapfall(map, row, col, i, game);
							score = score + 10;
							tips(YL - 2, XL - 2, numnow, score, (YL - 2) * 3, 13, 1);
						}

					}
					for (int i = 1; i < XL - 1; i++)                           //判断是否结束
					{
						if (map[1][i] == 3)
						{
							endflag = 2;
							tips(YL - 2, XL - 2, numnow, score, (YL - 2) * 3, 13, 2);
						}
					}
					break;
				}
			}
			if (endflag == 2)
			{
				last = _getch();
				break;
			}
		}
	}
	return c;
}

void numberblocks(int blocks[5][3], const int num)
{
	if (num == 0)
	{
		blocks[0][0] = 1;
		blocks[0][1] = 1;
		blocks[0][2] = 1;
		blocks[4][0] = 1;
		blocks[4][1] = 1;
		blocks[4][2] = 1;
		blocks[1][0] = 1;
		blocks[1][1] = 2;
		blocks[1][2] = 1;
		blocks[2][0] = 1;
		blocks[2][1] = 2;
		blocks[2][2] = 1;
		blocks[3][0] = 1;
		blocks[3][1] = 2;
		blocks[3][2] = 1;
	}
	if (num == 1)
	{
		blocks[0][0] = 2;
		blocks[0][1] = 1;
		blocks[0][2] = 2;
		blocks[1][1] = 1;
		blocks[2][1] = 1;
		blocks[3][1] = 1;
		blocks[4][1] = 1;
		blocks[1][0] = 2;
		blocks[2][0] = 2;
		blocks[3][0] = 2;
		blocks[4][0] = 2;
		blocks[1][2] = 2;
		blocks[2][2] = 2;
		blocks[3][2] = 2;
		blocks[4][2] = 2;
	}
	if (num == 2)
	{
		blocks[0][0] = 1;
		blocks[0][1] = 1;
		blocks[0][2] = 1;
		blocks[1][0] = 2;
		blocks[1][1] = 2;
		blocks[1][2] = 1;
		blocks[2][0] = 1;
		blocks[2][1] = 1;
		blocks[2][2] = 1;
		blocks[3][0] = 1;
		blocks[3][1] = 2;
		blocks[3][2] = 2;
		blocks[4][0] = 1;
		blocks[4][1] = 1;
		blocks[4][2] = 1;
	}
	if (num == 3)
	{
		blocks[0][0] = 1;
		blocks[0][1] = 1;
		blocks[0][2] = 1;
		blocks[1][0] = 2;
		blocks[1][1] = 2;
		blocks[1][2] = 1;
		blocks[2][0] = 1;
		blocks[2][1] = 1;
		blocks[2][2] = 1;
		blocks[3][0] = 2;
		blocks[3][1] = 2;
		blocks[3][2] = 1;
		blocks[4][0] = 1;
		blocks[4][1] = 1;
		blocks[4][2] = 1;
	}
	if (num == 4)
	{
		blocks[0][0] = 1;
		blocks[0][1] = 2;
		blocks[0][2] = 1;
		blocks[1][2] = 1;
		blocks[1][1] = 2;
		blocks[1][0] = 1;
		blocks[2][0] = 1;
		blocks[2][1] = 1;
		blocks[2][2] = 1;
		blocks[3][2] = 1;
		blocks[4][2] = 1;
		blocks[3][1] = 2;
		blocks[4][1] = 2;
		blocks[3][0] = 2;
		blocks[4][0] = 2;
	}
	if (num == 5)
	{
		blocks[0][0] = 1;
		blocks[0][1] = 1;
		blocks[0][2] = 1;
		blocks[1][0] = 1;
		blocks[1][1] = 2;
		blocks[1][2] = 2;
		blocks[2][0] = 1;
		blocks[2][1] = 1;
		blocks[2][2] = 1;
		blocks[3][2] = 1;
		blocks[3][1] = 2;
		blocks[3][0] = 2;
		blocks[4][0] = 1;
		blocks[4][1] = 1;
		blocks[4][2] = 1;
	}
	if (num == 6)
	{
		blocks[0][0] = 1;
		blocks[0][1] = 1;
		blocks[0][2] = 1;
		blocks[1][0] = 1;
		blocks[1][1] = 2;
		blocks[1][2] = 2;
		blocks[2][0] = 1;
		blocks[2][1] = 1;
		blocks[2][2] = 1;
		blocks[3][0] = 1;
		blocks[3][1] = 2;
		blocks[3][2] = 1;
		blocks[4][0] = 1;
		blocks[4][1] = 1;
		blocks[4][2] = 1;
	}
	if (num == 7)
	{
		blocks[0][0] = 1;
		blocks[0][1] = 1;
		blocks[0][2] = 1;
		blocks[1][2] = 1;
		blocks[2][2] = 1;
		blocks[3][2] = 1;
		blocks[4][2] = 1;
		blocks[1][1] = 2;
		blocks[2][1] = 2;
		blocks[3][1] = 2;
		blocks[4][1] = 2;
		blocks[1][0] = 2;
		blocks[2][0] = 2;
		blocks[3][0] = 2;
		blocks[4][0] = 2;
	}
	if (num == 8)
	{
		blocks[0][0] = 1;
		blocks[0][1] = 1;
		blocks[0][2] = 1;
		blocks[4][0] = 1;
		blocks[4][1] = 1;
		blocks[4][2] = 1;
		blocks[1][0] = 1;
		blocks[1][1] = 2;
		blocks[1][2] = 1;
		blocks[2][0] = 1;
		blocks[2][1] = 1;
		blocks[2][2] = 1;
		blocks[3][0] = 1;
		blocks[3][1] = 2;
		blocks[3][2] = 1;
	}
	if (num == 9)
	{
		blocks[0][0] = 1;
		blocks[0][1] = 1;
		blocks[0][2] = 1;
		blocks[4][0] = 1;
		blocks[4][1] = 1;
		blocks[4][2] = 1;
		blocks[1][0] = 1;
		blocks[1][1] = 2;
		blocks[1][2] = 1;
		blocks[2][0] = 1;
		blocks[2][1] = 1;
		blocks[2][2] = 1;
		blocks[3][0] = 2;
		blocks[3][1] = 2;
		blocks[3][2] = 1;
	}
}
void changearray(int blocks[5][3], int map[YL][XL], const int mode)
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 3; j++)
			map[i + 1][j + 7] = blocks[i][j];
}