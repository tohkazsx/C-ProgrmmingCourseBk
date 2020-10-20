/*������ ��2 1752528*/
#pragma once
#include <Windows.h>
#include "../common/cmd_console_tools.h"
#include "../common/common_cfgfile_tools.hpp"
#define MAX_LENGTH 128
#define CH_J 0
#define CH_F 1

struct LED
{
	int col;    //����
	int row;    //����
	int bgcolor;   //����ɫ
	char spec[20];   //��Ч
	int screen_time;  //����ʱ
	int sen_time;     //����ʱ
	char CH_Mode[10];     //�ֿ�
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
/*ȡ�ú�����Ϣ*/
int get_ch_info(Character &ch, LED led);
/*ȡ�ú��ֵ�����Ϣ*/
int GetCharacter(Character &ch);
/*��ӡ���ֵ���*/
int PrintCharacter(Character ch, LED led, int item_num);  //item_numΪ��ʾitem�����

int PrintCharacter_spec2(Character ch, LED led, int item_num, int play_num);

int PrintCharacter_spec3(Character ch, LED led, int item_num, int play_num);



/*ȡ����ʾ��Ϣ*/
int get_info(LED &led);
/*��ӡģ��led*/
int PrintLED(Character ch[128], LED led, int item_num);  //item_numΪ��ʾitem�����

int PrintLED_spec2(Character ch[128], LED led, int item_num);

int PrintLED_spec3(Character ch[128], LED led, int item_num);

int PrintLED_spec4(Character ch[128], LED led, int item_num);

int PrintLED_spec5(Character ch[128], LED led, int item_num);

int PrintLED_spec6(Character ch[128], LED led, int item_num);

int PrintLED_spec7(Character ch[128], LED led, int item_num);
/*��content���ݴ��ch�ṹ������*/
int GetString(Character ch[128], LED led, int num_of_item);//item_numΪ��ȡitem�����