/*朱世轩 计2 1752528*/
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "../common/cmd_console_tools.h"
#include"../common/common.h"
using namespace std;
int End()                                                                             //判断是否结束
{
	int judge, x, y;
	char c[6];
	showstr(0, 62, "本小题结束，输入end继续", 0, 7);
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
			system("cls"); //调用系统命令清除屏幕
			judge = 0;
			break;
		}
		else
		{
			cout << "输入错误，请重新输入";
			judge = 1;
			gotoxy(x, y);
		}
	}

	return judge;
}