/* 1752528 计2 朱世轩 */
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
			{ "1.命令行找出可合成项并标识（非递归）" },
			{ "2.命令行找出可合成项并标识（递归）" },
			{ "3.命令行完成一次合成（分步骤显示）" },
			{ "4.命令行完整版（分步骤显示）" },
			{ "5.伪图形界面显示初始数组（无分隔线）" },
			{ "6.伪图形界面显示初始数组（有分隔线）" },
			{ "7.伪图形界面下用箭头键选择当前色块" },
			{ "8.伪图形界面完成一次合成（分步骤）" },
			{ "9.伪图形界面完整版" },
			{"0.退出"},
			{ "[请选择0-9] " },
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
		cout << "参数错误" << endl;
		return 0;
	}
}
