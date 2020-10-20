/*������ ��2 1752528*/
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
/*��ӡ������ ���� ��Ч1*/
int PrintCharacter(Character ch, LED led, int item_num)                //��ӡ������
{
	for (int i = 0; i < 16; i++)
	{
		gotoxy(ch.word_x, ch.word_y + i);
		for (int j = 0; j < 16; j++)
		{
			if (ch.graph[i][j])
				setcolor(led.content_color[item_num], led.content_color[item_num]);//���ֲ���
			else
				setcolor(led.bgcolor, led.bgcolor);  //��������
			putchar(' ');
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}
/*��ӡ������ ��Ч2*/
int PrintCharacter_spec2(Character ch, LED led, int item_num, int play_num)       //play_num��ʾ�ƶ��˼���
{
	for (int i = 0; i < 16; i++)
	{
		gotoxy(ch.word_x, ch.word_y + i);
		for (int j = (play_num / 2) % 8; j < 16; j++)
		{
			if (ch.graph[i][j])
				setcolor(led.content_color[item_num], led.content_color[item_num]);//���ֲ���
			else
				setcolor(led.bgcolor, led.bgcolor);  //��������
			putchar(' ');
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}
/*��ӡ������ ��Ч3*/
int PrintCharacter_spec3(Character ch, LED led, int item_num, int play_num)       //play_num��ʾ�ƶ��˼���
{
	for (int i = 0; i < 16; i++)
	{
		gotoxy(ch.word_x, ch.word_y + i);
		for (int j = (play_num / 2) % 16; j < 16; j++)
		{
			if (ch.graph[i][j])
				setcolor(led.content_color[item_num], led.content_color[item_num]);//���ֲ���
			else
				setcolor(led.bgcolor, led.bgcolor);  //��������
			putchar(' ');
			putchar(' ');
		}
		//cout << endl;
		putchar('\n');
	}
	return 0;
}
/*��ӡ������ ��Ч6*/
int PrintCharacter_spec6(Character ch, LED led, int item_num)                //��ӡ������
{
	for (int i = 0; i < 16; i++)
	{
		gotoxy(ch.word_x, ch.word_y + i);
		for (int j = 0; j < 16; j++)
		{
			setcolor();
			cout << "  ";
		}
		putchar('\n');
	}
	return 0;
}
/*��ӡ������ ��Ч7*/
int PrintCharacter_spec7(Character ch, LED led, int item_num)       //play_num��ʾ�ƶ��˼���
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < 16; i++)
	{
		gotoxy(ch.word_x, ch.word_y + i);
		for (int j = 0; j < 16; j++)
		{
			if (ch.graph[i][j])
			{
				setcolor(rand() % 15, rand() % 15);
			}
			else
				setcolor(led.bgcolor, led.bgcolor);  //��������
			putchar(' ');
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}

/*��Ч1 ������ֹ��ʾ*/
int PrintLED(Character ch[128], LED led, int item_num)             //������ʾ  ��Ч1
{
	setfontsize("����", 6);
	setconsoleborder(32 * led.col + 2, 16 * led.row + 2, 32 * led.col + 2, 16 * led.row + 2);
	int count = 0; //���� �Ѵ�ӡ���ַ���
	while (1)
	{
		for (int i = 0; i < led.row; i++)
		{
			for (int j = 0; j < led.col; j++)
			{
				if (ch[i*led.col + j + count].word[0])
				{
					ch[i*led.col + j + count].word_x = 32 * j;
					ch[i*led.col + j + count].word_y = 16 * i;
					PrintCharacter(ch[i*led.col + j + count], led, item_num);
				}
				else
					return 0;
			}
		}
		if (count == 0)
		{
			Sleep(led.screen_time * 1000);
			count = (led.col)*(led.row);
		}
		else
		{
			Sleep(led.screen_time * 1000);
			break;
		}
		cls();
	}
	return 0;
}
/*��Ч2 ����Ч��*/
int PrintLED_spec2(Character ch[128], LED led, int item_num)              //��ӡled���� ��Ч2  rowΪ�� colΪ�� item_numΪ��ʾ�ڼ���
{
	setfontsize("����", 6);
	setconsoleborder(32 * led.col + 2, 16 * led.row + 2, 32 * led.col + 2, 16 * led.row + 2);
	int count = 0;
	for (int num = 0; num < led.col * 32; num = num + 16)                    //num��¼�ƶ�����
	{
		for (int j = num / 32; j < led.col; j++)
		{
			for (int i = 0; i < led.row; i++)
			{
				if (ch[i*led.col + j].word[0])
				{

					if (j - num / 32 == 0)
					{
						ch[i*led.col + j].word_x = 0;
						ch[i*led.col + j].word_y = 16 * (i);
						PrintCharacter_spec2(ch[i*led.col + j], led, item_num, num);
					}
					else
					{
						ch[i*led.col + j].word_x = 32 * (j)-num;
						ch[i*led.col + j].word_y = 16 * (i);
						PrintCharacter(ch[i*led.col + j], led, item_num);
					}
				}
				else
					break;
			}
		}
		if (count == 0)
		{
			Sleep(led.screen_time * 1000);
			count++;
		}
	}
	return 0;
}
/*��Ч3 �󻬣���ʵ����ëë��= =��*/
int PrintLED_spec3(Character ch[128], LED led, int item_num)
{
	setfontsize("����", 6);
	setconsoleborder(32 * led.col + 2, 16 * led.row + 2, 32 * led.col + 2, 16 * led.row + 2);
	for (int num = 0; num < led.col * 32; num++)                    //num��¼�ƶ�����
	{
		for (int j = num / 32; j < led.col; j++)
		{
			for (int i = 0; i < led.row; i++)
			{
				if (ch[i*led.col + j].word[0])
				{

					if (j - num / 32 == 0)
					{
						ch[i*led.col + j].word_x = 0;
						ch[i*led.col + j].word_y = 16 * (i);
						PrintCharacter_spec3(ch[i*led.col + j], led, item_num, num);
					}
					else
					{
						ch[i*led.col + j].word_x = 32 * (j)-num;
						ch[i*led.col + j].word_y = 16 * (i);
						PrintCharacter(ch[i*led.col + j], led, item_num);
					}
				}
				else
					break;
			}
		}
	}
	return 0;
}
/*��Ч4 ��ɫ �����*/
int PrintLED_spec4(Character ch[128], LED led, int item_num)
{
	setfontsize("����", 6);
	setconsoleborder(32 * led.col + 2, 16 * led.row + 2, 32 * led.col + 2, 16 * led.row + 2);
	int count = 0; //���� �Ѵ�ӡ���ַ���

	while (1)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int i = 0; i < led.row; i++)
			{
				for (int j = 0; j < led.col; j++)
				{
					if (ch[i*led.col + j + count].word[0])
					{
						ch[i*led.col + j + count].word_x = 32 * j;
						ch[i*led.col + j + count].word_y = 16 * i;
						srand((unsigned)time(NULL));
						led.content_color[item_num] = rand() % 15;
						PrintCharacter(ch[i*led.col + j + count], led, item_num);
					}
					else
						return 0;
				}
			}
		}
		if (count == 0)
		{
			Sleep(led.screen_time * 1000);
			count = (led.col)*(led.row);
		}
		else
		{
			Sleep(led.screen_time * 1000);
			break;
		}
		//Sleep(led.screen_time * 1000);
		cls();

	}
	return 0;

}
/*��Ч5 ���ִ�ӡ ����*/
int PrintLED_spec5(Character ch[128], LED led, int item_num)             //������ʾ  ��Ч1
{
	setfontsize("����", 6);
	setconsoleborder(32 * led.col + 2, 16 * led.row + 2, 32 * led.col + 2, 16 * led.row + 2);
	int count = 0; //���� �Ѵ�ӡ���ַ���
	while (1)
	{
		for (int i = 0; i < led.row; i++)
		{
			for (int j = 0; j < led.col; j++)
			{
				if (ch[i*led.col + j + count].word[0])
				{
					ch[i*led.col + j + count].word_x = 32 * j;
					ch[i*led.col + j + count].word_y = 16 * i;
					PrintCharacter(ch[i*led.col + j + count], led, item_num);
					Sleep(200);
				}
				else
					return 0;
			}
		}
		if (count == 0)
		{
			Sleep(led.screen_time * 1000);
			count = (led.col)*(led.row);
		}
		else
		{
			Sleep(led.screen_time * 1000);
			break;
		}
		cls();
	}
	return 0;
}
/*��Ч6 ����*/
int PrintLED_spec6(Character ch[128], LED led, int item_num)             //������ʾ  ��Ч1
{
	setfontsize("����", 6);
	setconsoleborder(32 * led.col + 2, 16 * led.row + 2, 32 * led.col + 2, 16 * led.row + 2);
	int count = 0; //���� �Ѵ�ӡ���ַ���
	while (1)
	{
		for (int i = 0; i < led.row; i++)
		{
			for (int j = 0; j < led.col; j++)
			{
				if (ch[i*led.col + j + count].word[0])
				{
					ch[i*led.col + j + count].word_x = 32 * j;
					ch[i*led.col + j + count].word_y = 16 * i;
					PrintCharacter(ch[i*led.col + j + count], led, item_num);
				}
				else
					return 0;
			}
		}
		if (count == 0)
		{
			Sleep(led.screen_time * 1000);
			count = (led.col)*(led.row);
		}
		else
		{
			Sleep(led.screen_time * 1000);
			break;
		}
		for (int i = 0; i < led.row; i++)
		{
			for (int j = 0; j < led.col; j++)
			{
					ch[i*led.col + j + count].word_x = 32 * j;
					ch[i*led.col + j + count].word_y = 16 * i;
					PrintCharacter_spec6(ch[i*led.col + j + count], led, item_num);
					Sleep(100);
			}
		}
		//cls();
	}
	return 0;
}
/*��Ч7 �ʺ���*/
int PrintLED_spec7(Character ch[128], LED led, int item_num)
{
	setfontsize("����", 6);
	setconsoleborder(32 * led.col + 2, 16 * led.row + 2, 32 * led.col + 2, 16 * led.row + 2);
	int count = 0; //���� �Ѵ�ӡ���ַ���

	while (1)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int i = 0; i < led.row; i++)
			{
				for (int j = 0; j < led.col; j++)
				{
					if (ch[i*led.col + j + count].word[0])
					{
						ch[i*led.col + j + count].word_x = 32 * j;
						ch[i*led.col + j + count].word_y = 16 * i;	
						PrintCharacter_spec7(ch[i*led.col + j + count], led, item_num);
					}
					else
						return 0;
				}
			}
		}
		if (count == 0)
		{
			Sleep(led.screen_time * 1000);
			count = (led.col)*(led.row);
		}
		else
		{
			Sleep(led.screen_time * 1000);
			break;
		}
		//Sleep(led.screen_time * 1000);
		cls();

	}
	return 0;

}