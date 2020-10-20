/*朱世轩 计2 1752528*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include<iomanip>
#include <Windows.h>
#include <string.h>
#include "90-b5.h"
#include "../common/cmd_console_tools.h"
using namespace std;
int main()
{
	Character ch[128];                        //存放单字的结构体数组
	LED led;                                   //存放配置信息的结构体数组
	int num_of_item = 1;                       //内容项
	get_info(led);                           //读取配置信息
	int spec = 1;
	
	while (1)
	{
		/*数据初始化*/
		for (int i = 0; i < 128; i++)
		{
			ch[i].word[0] = 0;
			ch[i].word[1] = 0;
			ch[i].word[2] = 0;
		}
		setcolor();
		GetString(ch, led, (num_of_item - 1) % 20);
		for (int i = 0; i < 128; i++)
		{
			get_ch_info(ch[i], led);
			GetCharacter(ch[i]);
		}
		int count = 0;
		srand((unsigned)time(NULL));
		while(1)              //选择特效
		{
			count = rand() % 7;
			if (led.spec[count] == 'Y')
			{
				spec = count + 1;
				break;
			}
		}
		if (spec == 1)
			PrintLED(ch, led, (num_of_item - 1) % 20);
		else if (spec == 2)
			PrintLED_spec2(ch, led, (num_of_item - 1) % 20);
		else if (spec == 3)
			PrintLED_spec3(ch, led, (num_of_item - 1) % 20);
		else if (spec == 4)
			PrintLED_spec4(ch, led, (num_of_item - 1) % 20);
		else if (spec == 5)
			PrintLED_spec5(ch, led, (num_of_item - 1) % 20); 
		else if (spec == 6)
			PrintLED_spec6(ch, led, (num_of_item - 1) % 20);
		else if (spec == 7)
			PrintLED_spec7(ch, led, (num_of_item - 1) % 20);
		Sleep(led.sen_time * 1000);
		num_of_item++;
	}
	return 0;
}
