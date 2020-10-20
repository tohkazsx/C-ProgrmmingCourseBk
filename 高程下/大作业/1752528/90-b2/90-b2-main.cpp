/*朱世轩 计2 1752528*/
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "../common/cmd_console_tools.h"
#include"../common/common.h"
#include"90-b2.h"
using namespace std;
int main()
{
	char choose;
	char last = '0';
	char menu[12][60] = {
		{"★数字俄罗斯方块★"},
		{ "Y.开始游戏" },
		{"Q.退出"},
		{ "[请选择A-Q] " },
	};
	int game = 2;
	choose = cd(menu, game);
	while (1)
	{
		setcolor(0, 7);
		tetris(choose, game, last);
		if (last == 'c')
			continue;
		else
			break;
	}
	return 0;

}