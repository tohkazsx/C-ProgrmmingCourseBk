/* 1752528 ��2 ������ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "90-b0.h"
#include"../common/cmd_console_tools.h"
#include"../common/common.h"
#include <conio.h>
using namespace std;

void frame(int a,int b,char c)                     //abΪ������
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
		cout << "��Ļ��ǰ����Ϊ��" << high - 3 << "��" << wide << "��" << endl;
}

void border(int a, int b,char c,int & nx,int & ny)             //ab������  c�˵�ѡ��
{
	if (c == '5')
	{
		getxy(nx, ny);
		nx=nx+2;
		ny=ny+1;
		setcolor(15, 0);
		cout << "�X";
		for (int i = 1; i <= b * 3; i++)
		{
			Sleep(5);
			cout << "�T";
		}
		cout << "�[";
		cout << endl;
		for (int i = 1; i <= a * 3; i++)
		{
			Sleep(5);
			cout << "�U";
			setcolor(0, 7);
			for (int j = 1; j <= b * 6; j++)
				cout << " ";
			setcolor(15, 0);
			cout << "�U"<<endl;
		}
		cout << "�^";
		for (int i = 1; i <= b * 3; i++)
		{
			Sleep(5);
			cout << "�T";
		}
		cout << "�a";
		setcolor(0, 7);
	}
	if (c == '6'||c=='7'||c=='8'||c=='9')
	{
		getxy(nx, ny);
		nx = nx + 2;
		ny = ny + 1;
		setcolor(15, 0);
		cout << "�X";
		for (int i = 1; i < b ; i++)
		{
			Sleep(5);
			cout << "�T�T�T�h";
		}
		cout << "�T�T�T�[";
		cout << endl;
		for (int i = 1; i < a ; i++)
		{
			for (int j = 1; j <= 3; j++)
			{
				Sleep(5);
				cout << "�U";
				for (int j = 1; j < b; j++)
					cout << "      ��";
				setcolor(15, 0);
				cout << "      �U" << endl;
			}
			cout << "�c";
			for (int j = 1; j < b; j++)
				cout << "��������";
			cout << "�������f";
		}
		for (int j = 1; j <= 3; j++)
		{
			Sleep(5);
			cout << "�U";
			for (int j = 1; j < b; j++)
				cout << "      ��";
			cout << "      �U";
			cout << endl;
		}
		cout << "�^";
		for (int i = 1; i < b; i++)
		{
			Sleep(5);
			cout << "�T�T�T�k";
		}
		cout << "�T�T�T�a";
		cout << endl;
		setcolor(0, 7);
	}
}

void blocks(int nx,int ny,int z)
{
	if (z < 10)
	{
		showstr(nx, ny, "�X�T�[", z % 15, 0);
		showstr(nx, ny + 1, "�U", z % 15, 0);
		cout << " " << z;
		showstr(nx + 4, ny + 1, "�U", z % 15, 0);
		showstr(nx, ny + 2, "�^�T�a", z % 15, 0);
	}
	else
	{
		showstr(nx, ny, "�X�T�[", z % 15, 0);
		showstr(nx, ny + 1, "�U", z % 15, 0);
		cout  << z;
		showstr(nx + 4, ny + 1, "�U", z % 15, 0);
		showstr(nx, ny + 2, "�^�T�a", z % 15, 0);
	}
}

void  cursor(int nx, int ny,int num)                                            //numΪ��ǰ���ѡ�е���
{
	if (num < 10)
	{
		showstr(nx, ny, "�X�T�[", 14, 9);
		showstr(nx, ny + 1, "�U", 14, 9);
		cout << " " << num;
		showstr(nx + 4, ny + 1, "�U", 14, 9);
		showstr(nx, ny + 2, "�^�T�a", 14, 9);
	}
	else
	{
		showstr(nx, ny, "�X�T�[", 14, 9);
		showstr(nx, ny + 1, "�U", 14, 9);
		cout << num;
		showstr(nx + 4, ny + 1, "�U", 14, 9);
		showstr(nx, ny + 2, "�^�T�a", 14, 9);
	}
}

void blocksmove(int N[12][12], char W[12][12], int a, int b,char c,int &nx,int &ny,int & m,int & n)     // �ƶ���꺯��  abΪ������ cΪ�˵�ѡ�� mnΪѡ��λ��    
{
	setcursor(CURSOR_INVISIBLE);
	static int i=1;
	static int j=1;
	int num;
	while (1)
	{
		showstr(0, 4 * a + 2, "������ƶ����س���ȷ��ѡ��                      ", 0, 7);
		num = N[i][j];
		cursor(nx, ny, num);
		int ret, X, Y, maction, keycode1, keycode2;
		enable_mouse();
		ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		if (ret == CCT_KEYBOARD_EVENT)
		{
			if (keycode2 == '\120')                                      //�½�
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
			if (keycode2 == '\110')                                      //����
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
			if (keycode2 == '\113')                                      //����
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
			if (keycode2 == '\115')                                      //����
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



char compound_cmd(char W[12][12], int N[12][12], int a, int b, char choose, int a1, int b1, int & score, int goal, int & max)         //���һ�κϳ�  abΪ������ a1 b1ΪĿ���� goalΪ�ϳ�Ŀ��
{
	
	max = 3;                                           //��¼�ϳɺ����ֵ
	int sbc = 0;                                          //���ε÷�
	int g = N[a1][b1] + 1;                            //gΪ�ϳɺ��ֵ
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
			showstr(nx3, ny3, "�X�T�[", t, 9);
			showstr(nx3, ny3 + 1, "�U", t, 9);
			cout << " " << g;
			showstr(nx3 + 4, ny3 + 1, "�U", t, 9);
			showstr(nx3, ny3 + 2, "�^�T�a", t, 9);
		}
		else
		{
			showstr(nx3, ny3, "�X�T�[", t, 9);
			showstr(nx3, ny3 + 1, "�U", t, 9);
			cout << g;
			showstr(nx3 + 4, ny3 + 1, "�U", t, 9);
			showstr(nx3, ny3 + 2, "�^�T�a", t, 9);
		}
	}
	                 
	if (choose == '8')
	{
		showstr(0,4*a+2 , "�ϳ���ɣ���enter����                   ", 0, 7);
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
	cout << "���ε÷֣�" << sbc << "�ܵ÷֣�" << score << "                    ";






for(int i=1;i<20;i++)
	for (int i = 1; i <= a ; i++)                                            //ʵ��0����
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
				showstr(nx4, ny4 + 3, "������", 15, 0);
				blocks(nx4, ny4 + 4, N[i][j]);
				N[i + 1][j] = N[i][j];
				N[i][j] = 0;
				W[i + 1][j] = W[i][j];
				W[i][j] = '0';
			}
		}
if (choose == '8')
{
	showstr(0, 4 * a + 2, "������ɣ���enter���                               ", 0, 7);
	while (1)
	{
		int t = ENTER();
		if (t == 0)
			break;
	}
	showstr(0, 4 * a + 2, "                               ", 0, 7);
}
	newfillin(max, N, a, b);                              //��ֵ���
	for (int i = 1; i <= a; i++)                                            
		for (int j = 1; j <= b; j++)
		{
				Sleep(15);
				int nx3 = 8 * j - 6;
				int ny3 = 4 * i - 2;
				if (N[i][j] < 10)
				{
					showstr(nx3, ny3, "�X�T�[", N[i][j] % 15, 0);
					showstr(nx3, ny3 + 1, "�U", N[i][j] % 15, 0);
					cout << " " << N[i][j];
					showstr(nx3 + 4, ny3 + 1, "�U", N[i][j] % 15, 0);
					showstr(nx3, ny3 + 2, "�^�T�a", N[i][j] % 15, 0);
				}
				else
				{
					showstr(nx3, ny3, "�X�T�[", N[i][j] % 15, 0);
					showstr(nx3, ny3 + 1, "�U", N[i][j] % 15, 0);
					cout << N[i][j];
					showstr(nx3 + 4, ny3 + 1, "�U", N[i][j] % 15, 0);
					showstr(nx3, ny3 + 2, "�^�T�a", N[i][j] % 15, 0);
				}
		}
	for (int i = 1; i <= a; i++)                                      
		for (int j = 1; j <= b; j++)
		{
			if (max < N[i][j])
				max = N[i][j];
		}
	for (int i = 1; i <= a; i++)                           //���ñ������               
		for (int j = 1; j <= b; j++)
		{
			W[i][j] = char(N[i][j] + '0');
		}
	char ch='0';
	if (choose == '8')
	{
		while (1)
		{
			showstr(0, 4 * a + 2, " ���κϳ�����ɣ���c����һ���µĺϳ�                          ", 0, 7);
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


