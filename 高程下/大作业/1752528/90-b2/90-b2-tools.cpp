/*������ ��2 1752528*/
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "../common/cmd_console_tools.h"
#include"../common/common.h"
using namespace std;
int End()                                                                             //�ж��Ƿ����
{
	int judge, x, y;
	char c[6];
	showstr(0, 62, "��С�����������end����", 0, 7);
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