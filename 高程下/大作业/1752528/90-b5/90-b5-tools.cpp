/*朱世轩 计2 1752528*/
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include<iostream>
#include <fstream>
#include <atlconv.h>
#include <conio.h>
#include <stdio.h>
#include<iomanip>
#include <experimental/filesystem>
#include "90-b5.h"
#include "../common/cmd_console_tools.h"
#include "../common/common_cfgfile_tools.hpp"
using namespace std;
int GetCharacter(Character &ch)     //ch为存放汉字信息的结构体数组元素
{
	fstream fp_hzk;
	int i, j, k, offset;
	int flag;
	char buffer[32];              //存放字库中读取出的点阵信息
	unsigned char key[8] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };
	if (ch.chmode)
		fp_hzk.open("hzk16f", ios::in | ios::binary);
	else
		fp_hzk.open("hzk16", ios::in | ios::binary);

	if (!fp_hzk.is_open()) {
		fprintf(stderr, "error hzk16\n");
		return 1;
	}
	offset = (94 * (unsigned int)(ch.word[0] - 0xa0 - 1) + (ch.word[1] - 0xa0 - 1)) * 32;
	fp_hzk.seekg(offset, ios::beg);
	fp_hzk.read(buffer, 32);
	for (k = 0; k < 16; k++)
	{
		for (j = 0;
			j < 2; j++)
		{
			for (i = 0; i < 8; i++)
			{
				flag = buffer[k * 2 + j] & key[i];
				if (flag)
				{
					ch.graph[k][j * 8 + i] = 1;
				}
				else
				{
					ch.graph[k][j * 8 + i] = 0;
				}
			}
		}
	}
	fp_hzk.close();
	return 0;
}

int get_info(LED &led)                                           //从配置文件中获取配置信息
{
	fstream fp_led;
	if (open_cfgfile(fp_led, "led.cfg", OPEN_OPT_RDONLY) == 0)
	{
		cout << "无法打开配置文件 " << endl;
		return -1;
	}
	item_get_value(fp_led, "setup", "行数", &led.row, TYPE_INT);
	item_get_value(fp_led, "setup", "列数", &led.col, TYPE_INT);
	item_get_value(fp_led, "setup", "屏延时", &led.screen_time, TYPE_INT);
	item_get_value(fp_led, "setup", "条延时", &led.sen_time, TYPE_INT);
	item_get_value(fp_led, "setup", "背景色", &led.bgcolor, TYPE_INT);
	if (!item_get_value(fp_led, "setup", "字库", led.CH_Mode, TYPE_STRING))
		strcpy(led.CH_Mode, "HZK16");
	for (int i = 0; i < 20; i++)
	{
		char item_name[64];
		strcpy(item_name, "item");
		if (i < 9)
		{
			item_name[4] = i + 1 + '0';
			item_name[5] = 0;
		}
		else if (i < 19)
		{
			item_name[4] = '1';
			item_name[5] = i - 9 + '0';
			item_name[6] = 0;
		}
		else
		{
			item_name[4] = '2';
			item_name[5] = i - 19 + '0';
			item_name[6] = 0;
		}
		if (!item_get_value(fp_led, "content", item_name, led.content[i], TYPE_STRING))
			led.content[i][0] = 0;
		strcat(item_name, "_color");
		char color;
		if (!item_get_value(fp_led, "content", item_name, &color, TYPE_CHARACTER))
		{
			srand((unsigned)time(NULL));
			led.content_color[i] = rand() % 15;
		}
		if (color == 'x')
		{
			srand((unsigned)time(NULL));
			led.content_color[i] = rand() % 15;
		}
		else
			led.content_color[i] = color - '0';
	}
	int flag_spec = 0;
	for (int i = 0; i < 20; i++)
	{
		char spec_name[64];
		strcpy(spec_name, "特效");
		spec_name[4] = i + 1 + '0';
		spec_name[5] = 0;
		if (item_get_value(fp_led, "setup", spec_name, &led.spec[i], TYPE_CHARACTER))
			flag_spec = 1;
	}
	if (flag_spec == 0)
		led.spec[0] = 'Y';
	return 0;
}

int get_ch_info(Character &ch, LED led)
{
	if (strcmp(led.CH_Mode, "HZK16") == 0)
		ch.chmode = CH_J;
	else
		ch.chmode = CH_F;
	return 0;
}

int GetString(Character ch[128], LED led, int num_of_item)  //将字符串中的全角字符读进ch数组
{
	int i = 0;
	int num = 0;
	char word1 = 0, word2 = 0;
	cout << led.content[num_of_item] << endl;              //test
	while (led.content[num_of_item][num] != '\0'&&i < 128)
	{
		if (led.content[num_of_item][num] < 0x80 && led.content[num_of_item][num]>0x20)//如果是半角字符 先转全角
		{
			ch[i].word[0] = 0xA3;
			ch[i].word[1] = led.content[num_of_item][num] + 0x80;
			ch[i].word[2] = 0;
			i++;
			num++;
		}
		else
		{
			ch[i].word[0] = led.content[num_of_item][num];
			ch[i].word[1] = led.content[num_of_item][num + 1];
			ch[i].word[2] = 0;
			i++;
			num = num + 2;
		}
	}
	return 0;
}


