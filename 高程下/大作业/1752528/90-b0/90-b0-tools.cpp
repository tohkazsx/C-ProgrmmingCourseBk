/* 1752528 ��2 ������ */
#include <iostream>
#include<iomanip>
#include <conio.h>
#include "90-b0.h"
#include"../common/common.h"
#include"../common/cmd_console_tools.h"
using namespace std;

int End()                                                                             //�ж��Ƿ����
{
	int judge,x,y;
	char c[6];
	cout << "��С�����������end����"<<endl;
	getxy(x, y);
	while (1)
	{
		gets_s(c);
		for (int i = 0; c[i] != '\0'; i++)
		{
			if (c[i] >= 'a'&&c[i] <= 'z')
				c[i] = c[i] - 32;
		}
		if (c[0] == 'E'&&c[1] == 'N'&&c[2] == 'D')
		{
			system("cls"); //����ϵͳ���������Ļ
			judge = 0;
			break;
		}
		else
		{
			cout << "�����������������";
			judge = 1;
			gotoxy(x, y);
		}
	}
	
	return judge;
}

void compound(char W[12][12],int N[12][12],char xh,int a,int b,char choose,int a1,int b1,int & score,int goal, int & max)         //���һ�κϳ�  abΪ������ a1 b1ΪĿ���� goalΪ�ϳ�Ŀ��
{
	int t;
	max=3;                                           //��¼�ϳɺ����ֵ
	int sbc=0;                                          //���ε÷�
	int g = N[a1][b1] + 1;                             //gΪ�ϳɺ��ֵ
	for (int i = 1; i <= a; i++)
		for (int j = 1; j <= b; j++)
		{
			if (W[i][j] == '*')
				N[i][j] = 0;
		}
	N[a1][b1] = g;
	cout << endl;
	cout << "��ֵͬ�鲢������飨��ͬɫ��ʶ����"<<endl;
	cout << "  " << "|";
	for (int i = 0; i < b; i++)
		cout << setw(3) << i;
	cout << endl;
	cout << "--+";
	for (int i = 1; i <= a; i++)
		cout << "---";
	cout << endl;
	for (int i = 1; i <= a; i++)                                         //��ʽ
	{                                                                   //
		cout << char(xh + i-1) << " |";                                //
		for (int j = 1; j <= b; j++)                                  //
			if (W[i][j] == '*')                                      //
			{                                                       //
				setcolor(0, 14);
				cout << setw(3) << N[i][j];
				setcolor(0, 7);
				sbc = sbc + 3 * (g - 1);
			}
			else
			{
				cout << setw(3) << N[i][j];
			}
		cout << endl;
	}               
	score = score + sbc;


for(int i=0;i<50;i++)
	for(int i=1;i <= a;i++)                                            //ʵ��0����
		for (int j = 1; j <= b; j++)
		{
			if (N[i][j] != 0 && N[i + 1][j] == 0)
			{
				N[i + 1][j] = N[i][j];
				N[i][j] = 0;
			}
		}

	cout << "���ε÷֣�" << sbc << " " << "�ܵ÷֣�" << score << " " << "�ϳ�Ŀ�꣺" << goal << endl;

	cout << "���س���ȷ�������0"<<endl;
	while (1)
	{
		t = ENTER();
		if (t == 0)
			break;
	}

	cout << "  " << "|";
	for (int i = 0; i < a; i++)
		cout << setw(3) << i;
	cout << endl;
	cout << "--+";
	for (int i = 1; i <= a; i++)
		cout << "---";                                                    //
	cout << endl;                                                        //
	for (int i = 1; i <= a; i++)                                        //
	{                                                                  //
		cout << char(xh + i - 1) << " |";                             //
		for (int j = 1; j <= b; j++)                                 //
			if (N[i][j] == 0)                                       //
			{                                                      //
				setcolor(0, 14);                                  //
				cout << setw(3) << N[i][j];                      //
				setcolor(0, 7);                                 //
			}
			else
			{
				cout << setw(3) << N[i][j];
			}
		cout << endl;
	}       
	cout << "���س���ȷ�������ֵ��" << endl;
	while (1)
	{
		t = ENTER();
		if (t == 0)
			break;
	}
	newfillin(max, N, a, b);

	cout << "  " << "|";
	for (int i = 0; i < a; i++)
		cout << setw(3) << i;
	cout << endl;
	cout << "--+";
	for (int i = 1; i <= a; i++)
		cout << "---";                                                    //
	cout << endl;                                                        //
	for (int i = 1; i <= a; i++)                                        //
	{                                                                  //
		cout << char(xh + i - 1) << " |";                             //
		for (int j = 1; j <= b; j++)                                 //
			if (N[i][j] == 0)                                       //
			{                                                      //
				setcolor(0, 14);                                  //
				cout << setw(3) << N[i][j];                      //
				setcolor(0, 7);                                 //
			}
			else
			{
				cout << setw(3) << N[i][j];
			}
		cout << endl;
		for (int i = 1; i <= a; i++)                           //���ñ������               
			for (int j = 1; j <= b; j++)
			{
				W[i][j] = char(N[i][j] + '0');
			}
	}
}

int ENTER()                                                        //��enter����
{
	char next;
	next = _getch();
	if (next == '\r')
		return 0;
	else
		return 1;
}

void newfillin(int max,int N[12][12],int a,int b)                   //����Ӧ���ʲ�����ֵ ���0
{
	for (int i = 1; i <= a; i++)
		for (int j = 1; j <= b; j++)
		{
			if (max < N[i][j])
				max = N[i][j];
		}
	int part;
	if (max == 3)
	{
		for(int i=1;i<=a;i++)
			for (int j = 1; j <= b; j++)
			{
				if (N[i][j] == 0)
					N[i][j] = rand() % 3 + 1;
			}
	}
	else if (max == 4)
	{
		for (int i = 1; i <= a; i++)
			for (int j = 1; j <= b; j++)
			{
				part = rand() % 100;
				if (N[i][j] == 0)
				{
					if (part >= 0 && part <= 89)
						N[i][j] = rand() % 3 + 1;
					else
						N[i][j] = 4;
				}
			}

	}
	else if (max == 5)
	{
		
			for (int i = 1; i <= a; i++)
				for (int j = 1; j <= b; j++)
				{
					part = rand() % 100;
					if (N[i][j] == 0)
					{
						if (part >= 0 && part <= 74)
							N[i][j] = rand() % 3 + 1;
						else if (part >= 75 && part <= 89)
							N[i][j] = 4;
						else
							N[i][j] = 5;
					}
				}
	
	}
	else if (max == 6)
	{

		for (int i = 1; i <= a; i++)
			for (int j = 1; j <= b; j++)
			{
				part = rand() % 100;
				if (N[i][j] == 0)
				{
					if (part >= 0 && part <= 79)
						N[i][j] = rand() % 4 + 1;
					else if (part >= 80 && part <= 94)
						N[i][j] = 5;
					else
						N[i][j] = 6;
				}
			}

	}
	else
		for (int i = 1; i <= a; i++)
			for (int j = 1; j <= b; j++)
			{
				part = rand() % 100;
				if (N[i][j] == 0)
				{
					if (part >= 0 && part <= 79)
						N[i][j] = rand() % (max - 3) + 1;
					else if (part >= 80 && part <= 89)
						N[i][j] = max - 2;
					else if (part >= 90 && part <= 94)
						N[i][j] = max - 1;
					else
						N[i][j] = max;
				}
			}
}


