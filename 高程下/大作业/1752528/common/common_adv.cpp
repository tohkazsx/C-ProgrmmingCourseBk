/* 1752528 ��2 ������ */
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include"../common/common.h"
#include "../common/cmd_console_tools.h"
using namespace std;

void CIN(int*s, int a, int b)              //������  ����  sΪ�������� ab����ȷ��Χ
{
	while (1)
	{
		int x, y;
		getxy(x, y);
		cin >> *s;
		if (!cin.good())
		{
			cout << "����Ƿ����������룺";
			cin.clear();
			cin.ignore(1024, '\n');
			gotoxy(x, y);
			continue;
		}
		else if (*s > b || *s < a)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����Ƿ����������룺";
			gotoxy(x, y);
			continue;
		}
		else
			break;
	}
	cin.ignore(1024, '\n');
}
void location(int a, int b, char * point, char W[ar][ar], int N[ar][ar])                       //ȡ��Ŀ������� abΪ������
{
	char loc[4];
	int a1, b1;                                                                            //a1,b1Ϊ��������λ��
	int x, y;
	getxy(x, y);
	cout << "������ĸ+������ʽ[����c2]����������꣺";
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
				cout << "Ŀ�����Χ����ֵͬ������������";
				continue;
			}
			else if (W[a1][b1] == '0')
			{
				cout << "Ŀ���Ϊ0λ�÷Ƿ�������������";
			}
			else
				break;
		}

		else
		{
			cout << "���벻�Ϸ� ����������";
			gotoxy(x, y);
		}
	}
	cout << "����Ϊ" << loc[0] << "��" << loc[1] << "��" << endl;
	*point = loc[0];
	*(point + 1) = loc[1];
}
void tips(int a, int b,int num,int score,const int length,const int wide,const int mode)                   //ab������  ��߿���ʾ��ʾ��Ϣ
{
	int nx, ny;
	nx = b * 6 + 4;
	ny = 0;
	setcolor(14, 0);
	gotoxy(nx, ny);
     cout << "�X";
	 for (int i = 1; i <= wide; i++)
	 {
		 Sleep(5);
		 cout << "�T";
	 }
	 cout << "�[";
	 cout << endl; 
	
	 for (int i = 1; i <= length; i++)
	 {
		 ny = i;
		 gotoxy(nx, ny);
		 cout << "�U";
		 for (int j = 1; j <= wide; j++)
			 cout << "  ";
		 cout << "�U" << endl;
	 } 
	 ny = 4 + (a - 1) * 3;
	 gotoxy(nx, ny);
	 cout << "�^";
	 for (int i = 1; i <= wide; i++)
	 {
		 cout << "�T";
	 }
	 cout << "�a";
	 setcolor(0, 7);
	 nx = nx + 6;
	 ny = (a / 2) * 3 - 10;
	 showstr(nx, ny, "�����ֶ���˹�����", 14, 7);
	 showstr(nx, ny + 2, "��Ϸ��ʼ", 14, 7);
	 showstr(nx, ny + 4, "��Ϸ˵����", 14, 7);
	 showstr(nx, ny + 6, "���ҷ�����ƶ�", 14, 7);
	 showstr(nx, ny + 8, "�Ϸ������ת", 14, 7);
	 showstr(nx, ny + 10, "�·������������", 14, 7);
	 showstr(nx, ny + 12, "���������λ����ͣ", 14, 7);
	 if (mode == 1)
	 {
		 showstr(nx, ny + 14, "��ǰ���֣�", 14, 7);
		 cout << num;
		 showstr(nx, ny + 16, "���ĵ÷֣�", 14, 7);
		 cout << score;
	 }
	 if (mode == 2)
	 {
		 showstr(nx, ny + 14, "��Ϸ������", 14, 3);
		 showstr(nx, ny + 16, "����������Ϊ��", 14, 3); 
		 cout << num;
		 showstr(nx, ny + 18, "��c������һ�Σ�", 14, 3);
		 showstr(nx, ny + 20, "���������˳���Ϸ", 14, 3);
		
	 }
}


