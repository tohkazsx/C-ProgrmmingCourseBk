/* 1752528 ��2 ������ */
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include"../common/common.h"
#include "../common/cmd_console_tools.h"
#include "90-b1.h"
using namespace std;
int main(int arcg, char *argv[])
{
	if (arcg == 1 || arcg == 3)
	{
		char choose;
		char last = '0';
		int lastrow, lastcol;
		char menu[12][60] = {
			{ "A.�������ҳ����������ʶ" },
			{ "B.���������һ���������ֲ�����ʾ��" },
			{ "C.���������һ�أ��ֲ�����ʾ��" },
			{ "D.αͼ�ν��������ѡ��һ��ɫ�飨�޷ָ��ߣ�" },
			{ "E.αͼ�ν��������ѡ��һ��ɫ�飨�зָ��ߣ�" },
			{ "F.αͼ�ν������һ���������ֲ��裩" },
			{ "G.αͼ�ν���������" },
			{ "[��ѡ��A-Q] " },
		};
		int game = 1;
		int e;
		while (1)
		{
			setconsoleborder(80, 28);
			choose = cd(menu, game);
			while (1)
			{
				last = Narray(choose, game, last, lastrow, lastcol);
				if (last == 'c')
					continue;
				else
					break;
			}
			e = End();
			if (e == 0)
				continue;
			else;
			return 0;
		}
	}
	else if (arcg != 3)
	{
		cout<< "��������" << endl;
		return 0;
	}
}
