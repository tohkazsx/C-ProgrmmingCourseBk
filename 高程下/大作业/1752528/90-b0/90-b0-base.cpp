/* 1752528 ��2 ������ */
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

void Narray(char c, int game, const char *filename)                 //����������鲢�����ʼ����
{
	int row, col;
	int max;                 //��¼���鵱ǰ���ֵ
	int z;                    //��¼����ֵ
	int a, b;              //a,b ΪĿ����������е����
	int x;                 //Ŀ����
	int goal;             //�ϳ�Ŀ��
	char ynq;              //ѡ��
	int score=0;             //��¼����
	int nx, ny;     //  ��¼αͼ�ν����ڲ���ʼ��ӡ����λ��
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
	    cout << "������������5-8����";
		CIN(&row, 5, 8);
		cout << "������������5-10����";
		CIN(&col, 5, 10);
	for(int i=1;i<=row;i++)
        for (int j = 1; j <= col; j++)
		{
			Narray[i][j] = rand() % 3 + 1;
			Warray[i][j] = Narray[i][j]+'0';
		}
		
		if (c == '3' || c == '4'||c=='8'||c=='9')
		{
			cout << "������ϳ�Ŀ��(5-20)��";
			CIN(&goal, 5, 20);
		}
		if (c == '1' || c == '2' || c == '3' || c == '4')
		{
			cout << "��ǰ���飺" << endl;       //���ԭ����
			printarray(Warray, Narray, row, col, game, 0);
		}
		if (c == '1' || c == '2' || c == '3' || c == '4')
		{
			while (1)
			{
				location(row, col, point, Warray, Narray);        //��λ a,b ΪĿ����������е����

				a = *point - 'A' + 1;
				b = *(point + 1) - '0' + 1;
				x = Narray[a][b];
				Warray[a][b] = '*';
				if (c == '1')
				{
					search(x, Warray, row, col);    //�ǵݹ�
				}

				if (c == '2' || c == '3' || c == '4')
				{
					search_dg(x, Warray, a, b);       //�ݹ�
					for (int i = 1; i <= row; i++)
						for (int j = 1; j <= col; j++)
						{
							if (Warray[i][j] != '*')
								Warray[i][j] = '0';
						}
				}


				if (c == '1' || c == '2' || c == '3' || c == '4')
				{
					cout << "��������飺" << endl;       //������������
					printarray(Warray, Narray, row, col, game, 1);
				}
				highlight(Warray, Narray, row, col,game);
				if (c == '3' || c == '4')
				{
					ynq = YNQ(a, b);
					if (ynq == 'Y')
					{
						compound(Warray, Narray, xu, row, col, c, a, b, score, goal, max);            //һ�κϳ�
					}
					if (ynq == 'Q')
					{
						break;
					}
					if (ynq == 'N')
					{
						cout << endl;
						cout << "��ǰ���飺" << endl;       //���ԭ����
						printarray(Warray, Narray, row, col, game, 0);
						continue;
					}
					if (c == '4')
					{
						if (max == goal)
						{
							setcolor(14, 7);
							cout << "�Ѻϳɵ�" << goal;
							setcolor(0, 7);

							cout << " ���س��������ϳ�";
						}
						else
							cout << "���κϳɽ��������س�������һ���µĺϳɣ�" << endl;
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
	if (c == '5' || c == '6'||c == '7'||c=='8'||c=='9')                      //αͼ��
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
				showstr(0, 4 * row + 2, "�����/����ƶ����س���ѡ��", 0, 15);
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
						showstr(0, 4 * row + 2, "   ��Χ����ֵͬ����ͷ���ƶ����س���ȷ��", 0, 14);
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
									showstr(nx1, ny1, "�X�T�[", 14, 9);
									showstr(nx1, ny1 + 1, "�U", 14, 9);
									cout << " " << Narray[i][j];
									showstr(nx1 + 4, ny1 + 1, "�U", 14, 9);
									showstr(nx1, ny1 + 2, "�^�T�a", 14, 9);
									showstr(0, 4 * row + 2, "��ͷ���ƶ���ȡ����ǰѡ�񣬻س���ȷ�Ϻϳ�", 14, 9);
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
											showstr(nx1, ny1, "�X�T�[", Narray[i][j] % 15, 0);
											showstr(nx1, ny1 + 1, "�U", Narray[i][j] % 15, 0);
											cout << " " << Narray[i][j];
											showstr(nx1 + 4, ny1 + 1, "�U", Narray[i][j] % 15, 0);
											showstr(nx1, ny1 + 2, "�^�T�a", Narray[i][j] % 15, 0);
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
									showstr(0, 4 * row + 3, "�Ѵﵽ�ϳ�Ŀ��", 14, 9);
									setcolor(14, 9);
									cout << goal;
									setcolor(0, 7);
									showstr(16, 4 * row + 3, "��������ֽ���", 14, 9);
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
											showstr(nx1, ny1, "�X�T�[", Narray[i][j] % 15, 0);
											showstr(nx1, ny1 + 1, "�U", Narray[i][j] % 15, 0);
											cout << " " << Narray[i][j];
											showstr(nx1 + 4, ny1 + 1, "�U", Narray[i][j] % 15, 0);
											showstr(nx1, ny1 + 2, "�^�T�a", Narray[i][j] % 15, 0);
										}
									}
								for (int i = 1; i <= row; i++)
									for (int j = 1; j <= col; j++)
									{
										Warray[i][j] = Narray[i][j] + '0';
									}

								if (keycode2 == '\120')                                      //�½�
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
								if (keycode2 == '\110')                                      //����
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
								if (keycode2 == '\113')                                      //����
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
								if (keycode2 == '\115')                                      //����
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
									showstr(0, 4 * row + 3, "�Ѵﵽ�ϳ�Ŀ��", 14, 9);
									setcolor(14, 9);
									cout << goal;
									setcolor(0, 7);
									showstr(16, 4 * row + 3, "��������ֽ���", 14, 9);
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
									cout << "�޿ɼ����ϳɵ�������Ϸ����";
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


void resetarray(char W[12][12], int N[12][12], int a, int b)                      //��������ǰ��������
{
	int i, j;
	for (i = 1; i <= a; i++)
		for (j = 1; j <= b; j++)
		{
			W[i][j] = char(N[i][j] + '0');
		}
}



char YNQ(int a, int b)                                    //����ѡ�� �ϳ� ȡ�� �˳�
{
	char a1, b1,ynq;
	int x, y;
	a1 = char(a + 'A' - 1);
	b1 = char(b + '0' - 1);
	cout << "��ȷ���Ƿ�Ҫ��������ֵͬ�ϲ���" << a1 << b1 << "�У�Y/N/Q����";
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


