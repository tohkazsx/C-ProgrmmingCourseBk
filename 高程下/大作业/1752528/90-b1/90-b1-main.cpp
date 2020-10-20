/* 1752528 计2 朱世轩 */
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
			{ "A.命令行找出可消除项并标识" },
			{ "B.命令行完成一次消除（分步骤显示）" },
			{ "C.命令行完成一关（分步骤显示）" },
			{ "D.伪图形界面用鼠标选择一个色块（无分隔线）" },
			{ "E.伪图形界面用鼠标选择一个色块（有分隔线）" },
			{ "F.伪图形界面完成一次消除（分步骤）" },
			{ "G.伪图形界面完整版" },
			{ "[请选择A-Q] " },
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
		cout<< "参数错误" << endl;
		return 0;
	}
}
