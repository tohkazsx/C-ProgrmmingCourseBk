/* 1752528 ��2 ������ */
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include<iomanip>
#include <conio.h>
#include <Windows.h>
#include"../common/common.h"
#include "../common/cmd_console_tools.h"
using namespace std;
char cd(char menu[12][60], int game)                      //�˵�����
{
	char choose;
	int lm = 0;
	int max = 0;
	int h = 0;
	for (int i = 0; i < 12; i++)
	{
		if (menu[i][0] == 0)
			h = i - 1;
		else
		{
			for (int j = 0; menu[i][j] != 0; j++)
				lm++;
			if (lm > max)
			{
				max = lm;
			}
			lm = 0;
		}
	}
	for (int i = 0; i < max; i++)
		cout << "-";
	cout << endl;
	for (int i = 0; i < h; i++)
	{
		cout << menu[i] << endl;
	}
	for (int i = 0; i < max; i++)
		cout << "-";
	cout << endl;
	cout << menu[h];
	while (1)
	{
		choose = _getch();
		if (game == 0)
		{
			if (choose >= '0'&& choose <= '9')
			{
				cout << choose << endl;
				break;
			}
		}
		else if (game == 1)
		{
			if (choose >= 'a'&& choose <= 'z')
				choose = choose - 32;
			if (choose >= 'A'&& choose <= 'G' || choose >= 'Q')
			{
				cout << choose << endl;
				break;
			}
		}
		else if (game == 2)
		{
			if (choose >= 'a'&& choose <= 'z')
				choose = choose - 32;
			if (choose == 'Y' || choose == 'Q')
			{
				cout << choose << endl;
				break;
			}
		}
	}
	if (choose != '0')
	{
		system("cls"); //����ϵͳ���������Ļ
	}
	return choose;
}
void free_blocks(int nx, int ny, int z, int game)
{
	int color;
	if (game == 0)
		color = z % 15;
	else if (game == 1)
		color = z % 15 + 8;
	else if (game == 2)
		color = 14;
	if (z == 0 || (game == 2 && (z == 2 || z == 4)))
	{
		showstr(nx, ny, "      ", 15, 15);
		showstr(nx, ny + 1, "      ", 15, 15);
		showstr(nx, ny + 2, "      ", 15, 15);
	}
	else if (z < 10 && z != 0 && game != 2)
	{
		showstr(nx, ny, "�X�T�[", color, 0);
		showstr(nx, ny + 1, "�U", color, 0);
		if (game == 0)
			cout << " " << z;
		else if (game == 1)
			cout << "��";
		showstr(nx + 4, ny + 1, "�U", color, 0);
		showstr(nx, ny + 2, "�^�T�a", color, 0);
	}
	else if (game = 2)
	{
		showstr(nx, ny, "������", color, 0);
		showstr(nx, ny + 1, "��", color, 0);
		cout << "��";
		showstr(nx + 4, ny + 1, "��", color, 0);
		showstr(nx, ny + 2, "������", color, 0);
	}
	else if (z >= 10)
	{
		showstr(nx, ny, "�X�T�[", color, 0);
		showstr(nx, ny + 1, "�U", color, 0);
		cout << z;
		showstr(nx + 4, ny + 1, "�U", color, 0);
		showstr(nx, ny + 2, "�^�T�a", color, 0);
	}
}
void free_cursor(int nx, int ny, int num, int game)                                            //numΪ��ǰ���ѡ�е���
{

	if (num == 0)
	{
		showstr(nx, ny, "      ", 15, 15);
		showstr(nx, ny + 1, "      ", 15, 15);
		showstr(nx, ny + 2, "      ", 15, 15);
	}
	else if (num < 10)
	{
		if (game == 0)
		{
			showstr(nx, ny, "�X�T�[", 14, 9);
			showstr(nx, ny + 1, "�U", 14, 9);
			cout << " " << num;
			showstr(nx + 4, ny + 1, "�U", 14, 9);
			showstr(nx, ny + 2, "�^�T�a", 14, 9);
		}
		else if (game == 1)
		{
			int color = num % 15 + 8;
			showstr(nx, ny, "�X�T�[", color, 7);
			showstr(nx, ny + 1, "�U", color, 7);
			cout << "��";
			showstr(nx + 4, ny + 1, "�U", color, 7);
			showstr(nx, ny + 2, "�^�T�a", color, 7);
		}
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
void search(int x, char W[ar][ar], int a, int b)           //�ǵݹ鷽������ abΪ������ xΪĿ��
{
	int i, j, c;
	for (c = 0; c < ar; c++)
		for (i = 1; i <= a; i++)
			for (j = 1; j <= b; j++)
			{
				if (W[i][j] == '0' + x && (W[i + 1][j] == '*' || W[i - 1][j] == '*' || W[i][j + 1] == '*' || W[i][j - 1] == '*'))
					W[i][j] = '*';
			}
	for (i = 1; i <= a; i++)
		for (j = 1; j <= b; j++)
		{
			if (W[i][j] != '*')
				W[i][j] = '0';
		}
}
void search_dg(int x, char W[ar][ar], int a, int b)                           //�ݹ鷽������ abΪĿ������� xΪĿ��
{
	if (W[a][b + 1] == x + '0')
	{
		W[a][b + 1] = '*';
		search_dg(x, W, a, b + 1);
	}
	if (W[a + 1][b] == x + '0')
	{
		W[a + 1][b] = '*';
		search_dg(x, W, a + 1, b);
	}
	if (W[a - 1][b] == x + '0')
	{
		W[a - 1][b] = '*';
		search_dg(x, W, a - 1, b);
	}
	if (W[a][b - 1] == x + '0')
	{
		W[a][b - 1] = '*';
		search_dg(x, W, a, b - 1);
	}
}
void highlight(char W[ar][ar], int N[ar][ar], int a, int b, int game)          //��ͬɫ��Ǵ�ӡ   abΪ������    
{
	cout << "��ǰ���飨��ͬɫ��ʶ����" << endl;
	cout << "  " << "|";
	for (int i = 1; i <= a; i++)
		cout << setw(3) << i - 1;
	cout << endl;
	cout << "--+";
	for (int i = 1; i <= b; i++)
		cout << "---";
	cout << endl;
	for (int i = 1; i <= a; i++)
	{
		cout << char('A' + i - 1) << " |";
		for (int j = 1; j <= b; j++)
		{
			if (W[i][j] == '0')
				cout << setw(3) << N[i][j];
			else
			{
				if (game == 0)
				{
					setcolor(0, 14);
					cout << setw(3) << N[i][j];
					setcolor(0, 15);
				}                //����
				else if (game == 1)
				{
					cout << "  ";
					setcolor(14, 0);
					cout << N[i][j];
					setcolor(0, 15);
				}//����
			}
		}
		cout << endl;
	}
}
void printarray(char W[ar][ar], int N[ar][ar], int a, int b, int game, const int mode)        //ab������
{
	cout << "  " << "|";
	for (int i = 0; i < b; i++)
		cout << setw(3) << i;
	cout << endl;
	cout << "--+";
	for (int i = 0; i < b; i++)
		cout << "---";
	cout << endl;
	for (int i = 1; i <= a; i++)
	{
		cout << char('A' + i - 1) << " |";
		if (mode == 0)
		{
			for (int j = 1; j <= b; j++)
				cout << setw(3) << N[i][j];
		}
		else if (mode == 1)
		{
			for (int j = 1; j <= b; j++)
				cout << setw(3) << W[i][j];
		}
		cout << endl;
	}
}
void free_border(int a, int b, int & nx, int & ny, const int mode, const int style)             //ab������   mode0�޷ָ��� mode1�зָ��� style0 style1�������б�  
{
	if (mode == 0)
	{
		getxy(nx, ny);
		nx = nx + 2;
		ny = ny + 1;
		if (style == 1)
		{
			nx = nx + 2;
			ny = ny + 1;
		}
		if (style == 1)
		{
			for (int i = 0; i < b; i++)
			{
				gotoxy(6 * i + 6, 1);
				cout << i;
			}
			cout << endl;
		}
		if (style == 1)
			cout << "  ";
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
			if (style == 1 && (i + 1) % 3 == 0)
			{
				setcolor(0, 7);
				cout << char('A' + (i + 1) / 3 - 1) << " ";
				setcolor(15, 0);
			}
			if (style == 1 && (i + 1) % 3 != 0)
			{
				setcolor(0, 7);
				cout << "  ";
				setcolor(15, 0);
			}
			cout << "�U";
			for (int j = 1; j <= b * 6; j++)
				cout << " ";
			cout << "�U" << endl;
		}
		if (style == 1)
		{
			setcolor(0, 7);
			cout << "  ";
			setcolor(15, 0);
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
	if (mode == 1)
	{
		getxy(nx, ny);
		nx = nx + 2;
		ny = ny + 1;
		setcolor(15, 0);
		cout << "�X";
		for (int i = 1; i < b; i++)
		{
			Sleep(5);
			cout << "�T�T�T�h";
		}
		cout << "�T�T�T�[";
		cout << endl;
		for (int i = 1; i < a; i++)
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
char gameover(int row, int col, int Narray[ar][ar], char Warray[ar][ar], int game)
{
	int count = 0;
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= col; j++)
		{
			if (Narray[i][j] != 0 && (Narray[i][j] == Narray[i + 1][j] || Narray[i][j] == Narray[i][j + 1] || Narray[i][j] == Narray[i - 1][j] || Narray[i][j] == Narray[i][j - 1]))
			{
				count = count + 1;
			}
		}
	if (game == 1)
	{
		if (count == 0)
		{
			int count1 = 0;
			showstr(2, 3 * row + 5, "�޿����������ǣ����ؽ���", 0, 14);
			for (int i = 1; i <= row; i++)
				for (int j = 1; j <= col; j++)
				{
					if (Narray[i][j] != 0)
					{
						count1 = count1 + 1;
					}
				}
			cout << endl;
			cout << "  ʣ��" << count1 << "�����ǣ��������������һ��";
			char c = _getch();
			return 'c';
		}
		return '0';
	}
	else if (game == 0)
	{
		if (count == 0)
		{
			cout << "�޿ɼ����ϳɵ�������Ϸ����";
			return 'c';
		}
		return '0';
	}
	return '0';
}
void blocksmove(int N[ar][ar], char W[ar][ar], int a, int b, char c, int nx, int ny, int & m, int & n, int game, int mode)     // �ƶ���꺯��  abΪ������ cΪ�˵�ѡ�� mnΪѡ��λ��    
{
	setcursor(CURSOR_INVISIBLE);
	static int i = 1;
	static int j = 1;
	int num;
	if (c == 'D' || c == 'F' || c == 'G')
	{
		ny = 3 * i;
		nx = 6 * j - 2;
	}
	else
	{
		ny = 4 * i - 2;
		nx = 8 * j - 6;
	}
	while (1)
	{
		showstr(2, (3 + mode) * a + 4 - 2 * mode, "�����/����ƶ����س���/���ȷ��ѡ��              ", 0, 15);
		num = N[i][j];
		int flag = 0;
		free_cursor(nx, ny, num, game);
		int ret, X, Y, maction, keycode1, keycode2;
		enable_mouse();
		ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		if (ret == CCT_KEYBOARD_EVENT)
		{
			while (keycode2 == '\120')                                      //�½�
			{
				if (i < a)
				{
					num = N[i][j];
					free_blocks(nx, ny, num, game);
					ny = ny + 3 + mode;
					i = i + 1;
					num = N[i][j];
					free_cursor(nx, ny, num, game);
					if (N[i][j] == 0)
						flag = 1;
					else
						flag = 0;
				}
				else
				{
					num = N[i][j];
					free_blocks(nx, ny, num, game);
					ny = ny - (3 + mode) * (a - 1);
					i = 1;
					num = N[i][j];
					free_cursor(nx, ny, num, game);
					if (N[i][j] == 0)
						flag = 1;
					else
						flag = 0;
				}
				if (flag == 1)
					continue;
				else
					break;
			}
			while (keycode2 == '\110')                                      //����
			{
				if (i > 1)
				{
					num = N[i][j];
					free_blocks(nx, ny, num, game);
					ny = ny - (3 + mode);
					i = i - 1;
					num = N[i][j];
					free_cursor(nx, ny, num, game);
					if (N[i][j] == 0)
						flag = 1;
					else
						flag = 0;
				}
				else
				{
					num = N[i][j];
					free_blocks(nx, ny, num, game);
					ny = ny + (3 + mode) * (a - 1);
					i = a;
					num = N[i][j];
					free_cursor(nx, ny, num, game);
					if (N[i][j] == 0)
						flag = 1;
					else
						flag = 0;
				}
				if (flag == 1)
					continue;
				else
					break;
			}
			while (keycode2 == '\113')                                      //����
			{
				if (j > 1)
				{
					num = N[i][j];
					free_blocks(nx, ny, num, game);
					nx = nx - (6 + 2 * mode);
					j = j - 1;
					num = N[i][j];
					free_cursor(nx, ny, num, game);
					if (N[i][j] == 0)
						flag = 1;
					else
						flag = 0;
				}
				else
				{
					num = N[i][j];
					free_blocks(nx, ny, num, game);
					nx = nx + (6 + 2 * mode) * (b - 1);
					j = b;
					num = N[i][j];
					free_cursor(nx, ny, num, game);
					if (N[i][j] == 0)
						flag = 1;
					else
						flag = 0;
				}
				if (flag == 1)
					continue;
				else
					break;
			}
			while (keycode2 == '\115')                                      //����
			{
				if (j < b)
				{
					num = N[i][j];
					free_blocks(nx, ny, num, game);
					nx = nx + (6 + 2 * mode);
					j = j + 1;
					num = N[i][j];
					free_cursor(nx, ny, num, game);
					if (N[i][j] == 0)
						flag = 1;
					else
						flag = 0;
				}
				else
				{
					num = N[i][j];
					free_blocks(nx, ny, num, game);
					nx = nx - (6 + 2 * mode) * (b - 1);
					j = 1;
					num = N[i][j];
					free_cursor(nx, ny, num, game);
					if (N[i][j] == 0)
						flag = 1;
					else
						flag = 0;
				}
				if (flag == 1)
					continue;
				else
					break;
			}
			if (keycode1 == '\r')
				break;
		}
		else if (ret == CCT_MOUSE_EVENT)
		{
			for (int m = 1; m <= a; m++)
				for (int n = 1; n <= b; n++)
				{
					int nx1;
					int ny1;
					if (mode == 0)
					{
						nx1 = 6 * n - 2;
						ny1 = 3 * m;
					}
					else
					{
						nx1 = 8 * n - 6;
						ny1 = 4 * m - 2;
					}
					if (X >= nx1 && X <= nx1 + 5 && Y >= ny1 && Y <= ny1 + 2)
					{
						if (N[m][n] != 0)
						{
							free_blocks(nx, ny, num, game);
							free_cursor(nx1, ny1, N[n][m], game);
							nx = nx1;
							ny = ny1;
							i = m;
							j = n;
							showstr(2, (3 + mode) * a + 5 - mode * 2, "[��ǰ���]", 0, 15);
							cout << char(i + 'A' - 1) << "��" << j - 1 << "��    ";
						}
						else
						{
							showstr(2, (3 + mode) * a + 5 - mode * 2, "[��ǰ���]", 0, 15);
							cout << "λ�÷Ƿ�   ";
							continue;
						}
					}
				}

			if (maction == MOUSE_LEFT_BUTTON_CLICK)
			{
				if (N[i][j] == 0)
					continue;
				else
					break;
			}
		}
	}
	if (c == 'E' || c == 'D')
		gotoxy(0, 4 * a + 3);
	else if (c == 'F' || c == 'G')
	{
		m = i;
		n = j;
	}
}
void fall(int map[YL][XL], int blocks[5][3], int game, int & row, int & col, int & endflag)
{
	setcursor(CURSOR_INVISIBLE);
	int nx;
	int ny;
	int t;
	int flag = 0;
	for (int i = YL - 1; i > 0; i--)
		for (int j = XL - 1; j > 0; j--)
			if (map[i][j] == 3 && map[i - 1][j] == 1)
			{
				endflag = 1;
				break;
			}
	for (int i = YL - 1; i > 0; i--)
	{
		for (int j = XL - 1; j > 0; j--)
		{

			if ((map[i][j] == 0 || map[i][j] == 4) && (map[i - 1][j] == 1 || map[i - 1][j] == 2))
			{
				t = map[i][j];
				map[i][j] = map[i - 1][j];
				map[i - 1][j] = t;
			}
			if (map[i][j] == 3 && map[i - 1][j] == 2)
			{
				map[i - 1][j] = 0;
			}
		}
		if (endflag == 1)
			break;
	}
	for (int i = YL - 2; i > 0; i--)
		for (int j = XL - 2; j > 0; j--)
		{
			nx = (j - 1) * 6 + 2;
			ny = (i - 1) * 3 + 1;
			free_blocks(nx, ny, map[i][j], game);
		}

	for (int i = 1; i < YL; i++)
		for (int j = 1; j < XL; j++)
		{
			if ((map[i][j] == 1 || map[i][j] == 2) && flag == 0)
			{
				row = i;
				col = j;
				flag = 1;
			}
		}

}
void turn_right(int map[YL][XL], int blocks[5][3], int game, int & row, int & col)
{
	setcursor(CURSOR_INVISIBLE);
	int nx;
	int ny;
	int t;
	int flag = 0;
	int eflag = 0;
	for (int j = XL - 1; j >= 0; j--)
		for (int i = YL - 1; i >= 0; i--)
		{
			if (map[i][j] == 1 && map[i][j + 1] == 3)
			{
				eflag = 1;
			}
		}
	if (eflag == 0)
	{
		for (int j = XL; j > 0; j--)
			for (int i = YL; i > 0; i--)
			{
				if ((map[i][j] == 0 || map[i][j] == 4) && (map[i][j - 1] == 1 || map[i][j - 1] == 2))
				{
					t = map[i][j];
					map[i][j] = map[i][j - 1];
					map[i][j - 1] = t;
				}
				if (map[i][j] == 3 && map[i][j - 1] == 2)
				{
					map[i][j - 1] = 4;
				}

			}

		for (int j = XL - 2; j > 0; j--)
			for (int i = YL - 2; i > 0; i--)
			{
				nx = (j - 1) * 6 + 2;
				ny = (i - 1) * 3 + 1;
				free_blocks(nx, ny, map[i][j], game);
			}
		for (int i = 0; i < YL; i++)
			for (int j = 0; j < XL; j++)
			{
				if ((map[i][j] == 1 || map[i][j] == 2) && flag == 0)
				{
					row = i;
					col = j;
					flag = 1;
				}
			}
	}
	eflag = 0;
}

void turn_left(int map[YL][XL], int blocks[5][3], int game, int & row, int & col)
{
	setcursor(CURSOR_INVISIBLE);
	int nx;
	int ny;
	int t;
	int flag = 0;
	int eflag = 0;
	for (int j = 0; j < XL - 1; j++)
		for (int i = 0; i < YL; i++)
		{
			if (map[i][j] == 3 && map[i][j + 1] == 1)
			{
				eflag = 1;
			}
		}
	if (eflag == 0)
	{
		for (int i = 1; i < YL; i++)
			for (int j = 1; j < XL; j++)
			{
				if ((map[i][j] == 0 || map[i][j] == 4) && (map[i][j + 1] == 1 || map[i][j + 1] == 2))
				{
					t = map[i][j];
					map[i][j] = map[i][j + 1];
					map[i][j + 1] = t;
				}
				if (map[i][j] == 2 && map[i][j - 1] == 3)
				{
					map[i][j] = 4;
				}
			}

		for (int i = 1; i < YL - 1; i++)
			for (int j = 1; j < XL - 1; j++)
			{
				nx = (j - 1) * 6 + 2;
				ny = (i - 1) * 3 + 1;
				free_blocks(nx, ny, map[i][j], game);
			}
		for (int i = 0; i < YL; i++)
			for (int j = 0; j < XL; j++)
			{
				if ((map[i][j] == 1 || map[i][j] == 2) && flag == 0)
				{
					row = i;
					col = j;
					flag = 1;
				}
			}
	}
	else
		eflag = 0;
}

int spin(int map[YL][XL], int blocks[5][3], int game, int & row, int & col, int & spinflag)
{
	int nx;
	int ny;
	int r = row;
	int c = col;
	int flag = 0;
	gotoxy(56, 62);
	if (spinflag == 1 || spinflag == 3)        //����
	{
		r = r - 1;
		for (int i = r; i < r + 5; i++)
		{
			for (int j = c; j < c + 5; j++)
			{
				if (map[i][j] == 3)
					return -1;
			}
		}
	}
	if (spinflag == 0 || spinflag == 2)        //����
	{
		c = c - 1;
		for (int i = r; i < r + 5; i++)
		{
			for (int j = c; j < c + 5; j++)
			{
				if (map[i][j] == 3)
					return -1;
			}
		}
	}
	if (spinflag == 0)
	{
		col = col - 1;
		for (int i = row; i < row + 5; i++)
			for (int j = col; j < col + 5; j++)
				map[i][j] = 0;
		row = row + 1;
		for (int j = col; j < col + 5; j++)
			for (int i = row; i < row + 3; i++)
			{
				map[i][j] = blocks[j - col][i - row];
			}
		for (int i = 1; i < YL - 1; i++)
			for (int j = 1; j < XL - 1; j++)
			{
				nx = (j - 1) * 6 + 2;
				ny = (i - 1) * 3 + 1;
				free_blocks(nx, ny, map[i][j], game);
			}
	}
	if (spinflag == 1)
	{
		row = row - 1;
		for (int i = row; i < row + 5; i++)
			for (int j = col; j < col + 5; j++)
				map[i][j] = 0;
		col = col + 1;
		for (int i = row; i < row + 5; i++)
			for (int j = col; j < col + 3; j++)
			{
				map[i][j] = blocks[-i + row + 4][-j + col + 2];
			}
		for (int i = 1; i < YL - 1; i++)
			for (int j = 1; j < XL - 1; j++)
			{
				nx = (j - 1) * 6 + 2;
				ny = (i - 1) * 3 + 1;
				free_blocks(nx, ny, map[i][j], game);
			}
	}
	if (spinflag == 2)
	{
		col = col - 1;
		for (int i = row; i < row + 5; i++)
			for (int j = col; j < col + 5; j++)
				map[i][j] = 0;
		row = row + 1;
		for (int j = col; j < col + 5; j++)
			for (int i = row; i < row + 3; i++)
			{
				map[i][j] = blocks[j - col][2 - i + row];
			}
		for (int i = 1; i < YL - 1; i++)
			for (int j = 1; j < XL - 1; j++)
			{
				nx = (j - 1) * 6 + 2;
				ny = (i - 1) * 3 + 1;
				free_blocks(nx, ny, map[i][j], game);
			}
	}
	if (spinflag == 3)
	{
		row = row - 1;
		for (int i = row; i < row + 5; i++)
			for (int j = col; j < col + 5; j++)
				map[i][j] = 0;
		col = col + 1;
		for (int j = col; j < col + 3; j++)
			for (int i = row; i < row + 5; i++)
			{
				map[i][j] = blocks[i - row][j - col];
			}
		for (int i = 1; i < YL - 1; i++)
			for (int j = 1; j < XL - 1; j++)
			{
				nx = (j - 1) * 6 + 2;
				ny = (i - 1) * 3 + 1;
				free_blocks(nx, ny, map[i][j], game);
			}
		spinflag = 0;
		flag = 1;
	}

	if (flag == 0)
		spinflag = spinflag + 1;
	return 0;
}

void mapfall(int map[YL][XL], int & row, int & col, int nr, int game)
{
	setcursor(CURSOR_INVISIBLE);
	int nx;
	int ny;
	int t;
	int flag = 0;
	for (int i = nr; i > 1; i--)
		for (int j = 1; j < XL - 1; j++)
		{
			t = map[i][j];
			map[i][j] = map[i - 1][j];
			map[i - 1][j] = t;
		}
	for (int i = YL - 2; i > 0; i--)
		for (int j = XL - 2; j > 0; j--)
		{
			nx = (j - 1) * 6 + 2;
			ny = (i - 1) * 3 + 1;
			free_blocks(nx, ny, map[i][j], game);
		}
}
