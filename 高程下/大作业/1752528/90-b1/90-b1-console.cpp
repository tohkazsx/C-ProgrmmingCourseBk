/*������ ��2 1752528*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include"../common/common.h"
#include"../common/cmd_console_tools.h"
#include "90-b1.h"
#include <conio.h>
using namespace std;

void frame(int a, int b, char c)                     //abΪ������
{
	int high, wide;
	setcursor(CURSOR_INVISIBLE);
	if (c == 'D' || c == 'F' || c == 'G')
	{
		high = a * 3 + 10;
		wide = b * 6 + 7;
	}
	if (c == 'E')
	{
		high = a * 3 + a + 8;
		wide = b * 6 + (b + 1) * 2 + 1;
	}
	setconsoleborder(wide, high);
	cout << "��Ļ��ǰ����Ϊ��" << high - 3 << "��" << wide << "��" << endl;

}


char compound_cmd(char W[12][12], int N[12][12], int a, int b, char choose, int a1, int b1,int & score,int game)         //���һ�κϳ�  abΪ������ a1 b1ΪĿ���� goalΪ�ϳ�Ŀ��
{

	int sbc = 0;                                          //���ε÷�
	int count = 0;
	gotoxy(2, 0);
	for (int i = 1; i <= a; i++)
		for (int j = 1; j <= b; j++)
		{
			if (W[i][j] == '*')
			{
				N[i][j] = 0;
				count = count + 1;
			}
		}
	sbc = 5 * count*count;
	for (int i = 1; i <= a; i++)
		for (int j = 1; j <= b; j++)
		{

			if (N[i][j] == 0)
			{
				int nx2 = 6 * j - 2;
				int ny2 = 3 * i ;
				showstr(nx2, ny2, "      ", 15, 15);
				showstr(nx2, ny2 + 1, "      ", 15, 15);
				showstr(nx2, ny2 + 2, "      ", 15, 15);
			}
		}
	int nx3 = 6 * b1 - 2;
	int ny3 = 3 * a1;                       //�ϴι��λ��

	if (choose == 'F')
	{
		showstr(2, 3 * a + 4, "������ɣ���enter/����������                   ", 0, 15);
		while (1)
		{
			int ret, X, Y, maction, keycode1, keycode2;
			ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			if ((ret == CCT_MOUSE_EVENT&&maction== MOUSE_LEFT_BUTTON_CLICK)||(ret == CCT_KEYBOARD_EVENT&&keycode1=='\r'))
				break;
		}
	}
	score = score + sbc;
	gotoxy(0, 0);
	setcolor(0, 7);
	cout << "���ε÷֣�" << sbc << "�ܵ÷֣�" << score << "                    ";


	for (int i = 1; i < 20; i++)
		for (int i = 1; i <= a; i++)                                            //ʵ��0����
			for (int j = 1; j <= b; j++)
			{
				if (N[i][j] != 0 && N[i + 1][j] == 0)
				{
					int nx4 = 6 * j - 2;
					int ny4 = 3 * i ;
					Sleep(15);
					showstr(nx4, ny4, "      ", 15, 15);
					free_blocks(nx4, ny4 + 1, N[i][j],game);
					showstr(nx4, ny4 + 1, "      ", 15, 15);
					free_blocks(nx4, ny4 + 2, N[i][j],game);
					showstr(nx4, ny4 + 2, "      ", 15, 15);
					free_blocks(nx4, ny4 + 3, N[i][j],game);
					N[i + 1][j] = N[i][j];
					N[i][j] = 0;
					W[i + 1][j] = W[i][j];
					W[i][j] = '0';
				}
			}
	
	          
	for (int i = 1; i < 5; i++)
		for (int j = 1; j < b; j++)                        //ʵ����������
		{
			if (N[a][j] == 0)
			{
				for(int n=j;n < b;n++)
					for (int m = a; m >= 1; m--)
					{
						int nx5 = 6 * n - 2;
						int ny5 = 3 * m;
						Sleep(5);
						showstr(nx5 + 6, ny5 + 2, "      ", 15, 15);
						showstr(nx5 + 6, ny5 + 1, "      ", 15, 15);
						showstr(nx5 + 6, ny5, "      ", 15, 15);
						free_blocks(nx5, ny5, N[m][n+1], game);
						N[m][n] = N[m][n+1];
						N[m][n+1] = 0;
						W[m][n] = W[m][n+1];
						W[m][n+1] = '0';
					}
			}
		}


	for (int i = 1; i <= a; i++)                           //���ñ������               
		for (int j = 1; j <= b; j++)
		{
			W[i][j] = char(N[i][j] + '0');
		}

	if (choose == 'F')
	{
		showstr(2, 3 * a + 4, " ���κϳ�����ɣ���c/����������һ���µĺϳ�   ", 0, 15);
		while (1)
		{
			int ret, X, Y, maction, keycode1, keycode2;
			ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			if ((ret == CCT_MOUSE_EVENT&&maction == MOUSE_LEFT_BUTTON_CLICK) || (ret == CCT_KEYBOARD_EVENT&&(keycode1 == 'C'|| keycode1 == 'c')))
				break;
		}
		return 'c';
	}
	return 'e';
}


