/* 1752528 ��2 ������ */
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include<fstream>
#include <conio.h>
#include <Windows.h>
#include "../common/cmd_console_tools.h"
#include"../common/common.h"
#include "90-b0.h"
using namespace std;
int main(int arcg, char *argv[])
{
	if (arcg == 1|| arcg == 3)
	{
		char choose;
		int game = 0;
		char menu[12][60] = {
			{ "1.�������ҳ��ɺϳ����ʶ���ǵݹ飩" },
			{ "2.�������ҳ��ɺϳ����ʶ���ݹ飩" },
			{ "3.���������һ�κϳɣ��ֲ�����ʾ��" },
			{ "4.�����������棨�ֲ�����ʾ��" },
			{ "5.αͼ�ν�����ʾ��ʼ���飨�޷ָ��ߣ�" },
			{ "6.αͼ�ν�����ʾ��ʼ���飨�зָ��ߣ�" },
			{ "7.αͼ�ν������ü�ͷ��ѡ��ǰɫ��" },
			{ "8.αͼ�ν������һ�κϳɣ��ֲ��裩" },
			{ "9.αͼ�ν���������" },
			{"0.�˳�"},
			{ "[��ѡ��0-9] " },
		};
		int e;
		while (1)
		{
			setconsoleborder(80, 28);
			choose = cd(menu, game);
			Narray(choose, game, 0);
			e = End();
			if (e == 0)
				continue;
			else;
			return 0;
		}
	}
	else if (arcg != 3)
	{
		cout << "��������" << endl;
		return 0;
	}
}
