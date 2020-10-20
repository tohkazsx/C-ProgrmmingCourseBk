/*朱世轩 计2 1752528*/
#pragma once
#include <Windows.h>
#include "../common/cmd_console_tools.h"
#include "../common/common_cfgfile_tools.hpp"
#define MAX_LENGTH 128
#define CH_J 0
#define CH_F 1

struct LED
{
	int col;    //列数
	int row;    //行数
	int bgcolor;   //背景色
	char spec[20];   //特效
	int screen_time;  //屏延时
	int sen_time;     //条延时
	char CH_Mode[10];     //字库
	char content[22][MAX_LENGTH];
	int content_color[22];

};

struct Character
{
	unsigned char word[3];
	char graph[16][16];
	int word_x;
	int word_y;
	int chmode;
};
/*取得汉字信息*/
int get_ch_info(Character &ch, LED led);
/*取得汉字点阵信息*/
int GetCharacter(Character &ch);
/*打印汉字点阵*/
int PrintCharacter(Character ch, LED led, int item_num);  //item_num为显示item的序号

int PrintCharacter_spec2(Character ch, LED led, int item_num, int play_num);

int PrintCharacter_spec3(Character ch, LED led, int item_num, int play_num);



/*取得显示信息*/
int get_info(LED &led);
/*打印模拟led*/
int PrintLED(Character ch[128], LED led, int item_num);  //item_num为显示item的序号

int PrintLED_spec2(Character ch[128], LED led, int item_num);

int PrintLED_spec3(Character ch[128], LED led, int item_num);

int PrintLED_spec4(Character ch[128], LED led, int item_num);

int PrintLED_spec5(Character ch[128], LED led, int item_num);

int PrintLED_spec6(Character ch[128], LED led, int item_num);

int PrintLED_spec7(Character ch[128], LED led, int item_num);
/*讲content内容存进ch结构体数组*/
int GetString(Character ch[128], LED led, int num_of_item);//item_num为获取item的序号