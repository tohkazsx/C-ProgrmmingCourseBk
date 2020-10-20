/*朱世轩 计2 1752528*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <io.h>
#include<stdlib.h>
#include <conio.h>
#include<string.h>

#include "common_cfgfile_tools.h"
/***************************************************************************
函数名称：double_to_str
功    能：去掉传入字符串前后的空格回车
输入参数：
返 回 值：去掉后的字符串
说    明：
***************************************************************************/
static char *deletezero(char *buf)
{
	char *p;
	/*去除尾部空格*/
	p = &buf[strlen(buf) - 1];
	while (*p &&*p == '0')
		p--;
	*(p + 1) = 0;
	return buf;
}


/***************************************************************************
函数名称：alltrim
功    能：去掉传入字符串前后的空格回车
输入参数：
返 回 值：去掉后的字符串
说    明：
***************************************************************************/
static char *alltrim(char *buf)
{
	char *p;
	/*去除尾部空格*/
	p = &buf[strlen(buf) - 1];
	while (*p && (*p == 0x0d || *p == 0x0a || *p == 0x20 || *p == 0x09))
		p--;
	*(p + 1) = 0;
	/*去除头部空格*/
	p = &buf[0];
	while (*p && (*p == 0x0d || *p == 0x0a || *p == 0x20 || *p == 0x09))
		p++;
	/*p移动到buf，含尾零*/
	if (p != buf)
		memmove(buf, p, strlen(p) + 1);

	return buf;
}
/***************************************************************************
函数名称：
功    能：
输入参数：
返 回 值：
说    明：此函数允许放到 common_cfgfile_tools.c 中做为内部工具函数
***************************************************************************/
static int file_length(FILE *fp)
{
	int file_len, now_pos;

	/* 取fp当前指针位置 */
	now_pos = ftell(fp);

	/* 将文件指针移动到最后，此时tellp的结果就是文件大小 */
	fseek(fp, 0, SEEK_END);
	file_len = ftell(fp);

	/* 指针移动回函数调用前的原位置 */
	fseek(fp, now_pos, SEEK_SET);

	return file_len;
}

/***************************************************************************
函数名称：
功    能：
输入参数：
返 回 值：
说    明：此函数允许放到 common_cfgfile_tools.c 中做为内部工具函数
***************************************************************************/
static int file_resize(FILE *fp, int newsize)
{
	int now_pos = ftell(fp);
	/* 如果大小是负数则直接返回-1 */
	if (newsize < 0)
		return -1;

	_chsize(_fileno(fp), newsize);

	/* 如果当前文件指针超过了文件大小，则rewind */
	if (now_pos > newsize)
		rewind(fp);

	return 0;
}




FILE *open_cfgfile(const char *cfgname, int opt)
{
	if (opt == OPEN_OPT_RDWR)
	{
		FILE*fp = fopen(cfgname, "ab");
		fclose(fp);
		FILE*FP = fopen(cfgname, "rb+");
		return FP;
	}
	if (opt == OPEN_OPT_RDONLY)
	{
		FILE*fp = fopen(cfgname, "r");
		return fp;
	}
	else
		return NULL;
}

void close_cfgfile(FILE *fp)
{
	fclose(fp);
}

int group_add(FILE *fp, const char *group_name)
{
	int suc_fail = 1;
	char groupname[32] = { 0 };
	char groupcheck[32] = { 0 };
	strcpy(groupname, "[");
	strcat(groupname, group_name);
	strcat(groupname, "]");

	while (!feof(fp))
	{
		fgets(groupcheck, sizeof(groupcheck), fp);
		alltrim(groupcheck);
		if (strstr(groupcheck, groupname) != NULL)
		{
			suc_fail = 0;
		}
	}
	fseek(fp, 0, SEEK_END);
	if (suc_fail == 1)
	{
		fprintf(fp, "%s", "\r\n");
		fprintf(fp, "%s", "[");
		fprintf(fp, "%s", group_name);
		fprintf(fp, "%s", "]");
		fprintf(fp, "%s", "\r\n");

	}
	fseek(fp, 0, SEEK_SET);
	return suc_fail;
}

int group_del(FILE *fp, const char *group_name)
{
	int num_of_delete = 0;
	int delete_flag = 0;
	int size_of_file = file_length(fp);
	char *filelast = (char*)malloc(size_of_file);//动态申请文件大小的空间
	if (filelast == NULL)
	{
		fprintf(stdout, "%s", "申请失败");
	}
	int headloc = -1;                   //记录要删除组名位置
	int tailloc = -1;                  //记录下一个组名出现位置
	char groupname[64] = { 0 };
	char groupcheck[64] = { 0 };
	char nextgroup[64] = { 0 };
	strcpy(groupname, "[");
	strcat(groupname, group_name);
	strcat(groupname, "]");
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		headloc = (int)(ftell(fp));
		if (fgets(groupcheck, sizeof(groupcheck), fp) == NULL)
			break;
		alltrim(groupcheck);
		if (strcmp(groupcheck, groupname) == 0)           //找到要删除的组名   继续寻找下一个组名
		{
			num_of_delete++;
			while (!feof(fp))               //继续读取  直到找到下一个组名
			{
				tailloc = (int)(ftell(fp));
				fgets(nextgroup, sizeof(nextgroup), fp);
				alltrim(nextgroup);
				if (strstr(nextgroup, "[") && strstr(nextgroup, "]"))
					break;
			}
			if (!feof(fp))               //找到了下一个组名 且没读到文件尾
			{
				fseek(fp, tailloc, SEEK_SET);
				fread((char *)filelast, size_of_file - tailloc, 1, fp);
				filelast[size_of_file - tailloc] = '\0';
				fseek(fp, headloc, SEEK_SET);
				fwrite((char*)filelast, size_of_file - tailloc, 1, fp);
				file_resize(fp, size_of_file - (tailloc - headloc));
			}
			else
			{
				file_resize(fp, headloc);//没找到下一个组名 tailloc在文件结尾
			}
			size_of_file = file_length(fp);
			fseek(fp, headloc, SEEK_SET);
		}
	}
	free(filelast);
	return num_of_delete;
}

int item_add(FILE *fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	int flagerror = 0;
	int headloc = -1;
	int suc_fail = 0;
	int size_of_file = file_length(fp);
	char *filelast = (char*)malloc(size_of_file);//动态申请文件大小的空间
	if (filelast == NULL)
	{
		fprintf(stdout, "%s", "申请失败");
	}
	char groupname[64] = { 0 };
	char groupcheck[64] = { 0 };
	char itemcheck[64] = { 0 };
	strcpy(groupname, "[");
	strcat(groupname, group_name);
	strcat(groupname, "]");
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		/*从文件中一行一行读取*/
		if (fgets(groupcheck, sizeof(groupcheck), fp) == NULL)
			break;
		alltrim(groupcheck);
		if (strcmp(groupcheck, groupname) == 0)
		{
			headloc = (int)(ftell(fp));            //要插入位置
			suc_fail = 1;
			break;
		}
	}
	fseek(fp, headloc, SEEK_SET);
	while (!feof(fp))                               //判断是否已经存在项
	{
		/*从文件中一行一行读取*/
		if (fgets(itemcheck, sizeof(itemcheck), fp) == NULL)
			break;
		alltrim(groupcheck);
		if (strstr(itemcheck, item_name))
		{
			return 0;
		}
	}
	fseek(fp, headloc, SEEK_SET);
	fread(filelast, size_of_file - headloc, 1, fp);
	fseek(fp, headloc, SEEK_SET);
	fprintf(fp, "%s", item_name);
	fprintf(fp, "%s", "=");
	if (item_type == TYPE_INT)
	{
		int value = *(int*)(item_value);
		fprintf(fp, "%d", value);
		fprintf(fp, "%s", "\r\n");
	}
	if (item_type == TYPE_DOUBLE)
	{
		double value = *(double*)(item_value);
		char value_str[64] = { 0 };
		sprintf(value_str, "%lf", value);////////////////////////////////
		deletezero(value_str);
		fprintf(fp, "%s", value_str);
		fprintf(fp, "%s", "\r\n");
	}
	if (item_type == TYPE_STRING)
	{
		char value[64] = { 0 };
		strcpy(value, (char*)(item_value));
		fprintf(fp, "%s", value);
		fprintf(fp, "%s", "\r\n");
	}
	if (item_type == TYPE_CHARACTER)
	{
		char value = *(char*)(item_value);
		fprintf(fp, "%c", value);
		fprintf(fp, "%s", "\r\n");
	}
	if (item_type == TYPE_NULL)
	{
		fprintf(fp, "%s", "\r\n");
	}
	fwrite(filelast, size_of_file - headloc, 1, fp);
	free(filelast);
	return suc_fail;
}

int item_del(FILE *fp, const char *group_name, const char *item_name)
{
	int num_of_delete = 0;
	int delete_flag = 0;
	int group_flag = 0;
	int find_item_flag = 0;
	int size_of_file = file_length(fp);
	char *filelast = (char*)malloc(size_of_file);//动态申请文件大小的空间
	if (filelast == NULL)
	{
		fprintf(stdout, "%s", "申请失败");
	}
	int itemloc1 = -1;                   //记录要删除组名位置
	int itemloc2 = -1;                   //记录开始读取剩余内容的位置
	char groupname[64] = { 0 };
	char groupcheck[64] = { 0 };
	char checkitem[64] = { 0 };
	strcpy(groupname, "[");
	strcat(groupname, group_name);
	strcat(groupname, "]");
	fseek(fp, 0, SEEK_SET);
	if (group_name == NULL)
	{
		while (!feof(fp))
		{
			itemloc1 = (int)(ftell(fp));
			if (fgets(checkitem, sizeof(checkitem), fp) == NULL)
				break;
			alltrim(checkitem);
			if (strstr(checkitem, item_name))
			{
				find_item_flag = 1;
				itemloc2 = (int)(ftell(fp));
			}
			if (find_item_flag == 1)
			{
				fread(filelast, size_of_file - itemloc2, 1, fp);
				fseek(fp, itemloc1, SEEK_SET);
				fwrite(filelast, size_of_file - itemloc2, 1, fp);
				file_resize(fp, size_of_file - (itemloc2 - itemloc1));
				size_of_file = file_length(fp);
				num_of_delete++;
				fseek(fp, itemloc1, SEEK_SET);
				find_item_flag = 0;
			}
		}
		file_resize(fp, itemloc1);
	}
	else
	{
		while (!feof(fp))
		{
			if (fgets(groupcheck, sizeof(groupcheck), fp) == NULL)
				break;
			alltrim(groupcheck);
			if (strcmp(groupcheck, groupname) == 0)           //找到要删除的组名   继续寻找项目名
			{
				while (!feof(fp))
				{
					itemloc1 = (int)(ftell(fp));
					if (fgets(checkitem, sizeof(checkitem), fp) == NULL)
						break;
					alltrim(checkitem);
					if (strstr(checkitem, item_name))
					{
						find_item_flag = 1;
						itemloc2 = (int)(ftell(fp));
					}
					if (find_item_flag == 1)
					{
						fread(filelast, size_of_file - itemloc2, 1, fp);
						fseek(fp, itemloc1, SEEK_SET);
						fwrite(filelast, size_of_file - itemloc2, 1, fp);
						file_resize(fp, size_of_file - (itemloc2 - itemloc1));
						size_of_file = file_length(fp);
						num_of_delete++;
						fseek(fp, itemloc1, SEEK_SET);
						find_item_flag = 0;
					}
					if (strstr(checkitem, "[") != NULL && strstr(checkitem, "]") != NULL)
					{
						group_flag = 1;
						break;
					}
				}
				if (group_flag == 0)
					file_resize(fp, itemloc1);
				else
					break;
			}
		}
	}
	free(filelast);

	return num_of_delete;
}

int item_update(FILE *fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	int item_add(FILE *fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
	int item_del(FILE *fp, const char *group_name, const char *item_name);
	fseek(fp, 0, SEEK_SET);
	int find_group = 0;
	int group_flag = 0;
	int find_first_item = 0;
	int itemloc1 = -1;                         //记录需要更新的位置
	int itemloc2 = -1;
	int size_of_file = file_length(fp);
	char *filelast = (char*)malloc(size_of_file);//动态申请文件大小的空间
	char groupname[64] = { 0 };
	char groupcheck[64] = { 0 };
	char checkitem[64] = { 0 };
	strcpy(groupname, "[");
	strcat(groupname, group_name);
	strcat(groupname, "]");
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		/*从文件中一行一行读取*/
		if (fgets(groupcheck, sizeof(groupcheck), fp) == NULL)
			break;
		alltrim(groupcheck);
		if (strcmp(groupcheck, groupname) == 0)           //找到要更新的组名   继续寻找项目名
		{
			find_group = 1;
			while (!feof(fp))
			{
				itemloc1 = (int)(ftell(fp));
				fgets(checkitem, sizeof(checkitem), fp);
				alltrim(checkitem);
				if (strstr(checkitem, item_name))
				{
					itemloc2 = (int)(ftell(fp));
					find_first_item = 1;
					break;
				}
				if (strstr(checkitem, "[") != NULL && strstr(checkitem, "]") != NULL)
				{
					group_flag = 1;
					break;
				}
			}
		}
		if (find_first_item == 1)
			break;
		if (group_flag == 1)
			break;
	}
	if (find_group == 0)
		return 0;
	if (find_first_item == 1)
	{
		item_del(fp, group_name, item_name);
		size_of_file = file_length(fp);
		fseek(fp, itemloc1, SEEK_SET);
		fread(filelast, size_of_file - itemloc1, 1, fp);
		fseek(fp, itemloc1, SEEK_SET);
		fprintf(fp, "%s", item_name);
		fprintf(fp, "%s", "=");
		if (item_type == TYPE_INT)
		{
			int value = *(int*)(item_value);
			fprintf(fp, "%d", value);
		}
		if (item_type == TYPE_DOUBLE)
		{
			double value = *(double*)(item_value);
			char value_str[64] = { 0 };
			sprintf(value_str, "%lf", value);///////////////
			deletezero(value_str);
			fprintf(fp, "%s", value_str);
		}
		if (item_type == TYPE_STRING)
		{
			char value[64] = { 0 };
			strcpy(value, (char*)(item_value));
			fprintf(fp, "%s", value);
		}
		if (item_type == TYPE_CHARACTER)
		{
			char value = *(char*)(item_value);
			fprintf(fp, "%c", value);
		}
		if (item_type == TYPE_NULL)
		{
		}
		fprintf(fp, "%s", "\r\n");
		fwrite(filelast, size_of_file - itemloc1, 1, fp);
	}
	if (find_first_item == 0)
	{
		item_add(fp, group_name, item_name, item_value, item_type);
	}
	return 1;
}

int item_get_value(FILE *fp, const char *group_name, const char *item_name, void *item_value, const enum ITEM_TYPE item_type)
{
	int flagerror = 0;
	int headloc = -1;
	int suc_fail = 0;
	int size_of_file = file_length(fp);
	int tailloc = size_of_file;
	char *filelast = (char*)malloc(size_of_file);//动态申请文件大小的空间

	char groupname[64] = { 0 };
	char groupcheck[64] = { 0 };
	char itemcheck[64] = { 0 };
	strcpy(groupname, "[");
	strcat(groupname, group_name);
	strcat(groupname, "]");
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		/*从文件中一行一行读取*/
		fgets(groupcheck, sizeof(groupcheck), fp);
		alltrim(groupcheck);
		if (strcmp(groupcheck, groupname) == 0)
		{
			suc_fail = 1;
			break;
		}
	}
	if (suc_fail == 1)                                 //如果存在组
	{
		while (!feof(fp))                               //找到要查找的项
		{
			/*从文件中一行一行读取*/
			fgets(itemcheck, sizeof(itemcheck), fp);
			alltrim(itemcheck);
			if (strstr(itemcheck, item_name))
			{
				break;
			}
		}
		char *p;
		p = &itemcheck[0];
		while (*p && *p != '=')
			p++;
		/*p移动到buf，含尾零*/
		if (p != itemcheck)
			memmove(itemcheck, p + 1, strlen(p));

		if (item_type == TYPE_INT)
		{
			int value = 0;
			unsigned int i;
			for (i = 0; i < strlen(itemcheck); i++)
			{
				value = value * 10 + (itemcheck[i] - '0');
			}
			*(int*)(item_value) = value;
		}
		if (item_type == TYPE_DOUBLE)
		{
			double value = 0;
			sscanf(itemcheck, "%lf", &value);
			*(double*)(item_value) = value;
		}
		if (item_type == TYPE_STRING)
		{
			strcpy((char*)(item_value), itemcheck);
		}
		if (item_type == TYPE_CHARACTER)
		{
			*(char*)(item_value) = (char)(itemcheck[0]);
		}
		if (item_type == TYPE_NULL)
		{
			return 0;
		}
	}
	return 1;
}

