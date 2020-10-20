/*朱世轩 计2 1752528*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <io.h>
#include <iomanip>
#include <conio.h>
#include <experimental/filesystem>
#include "common_cfgfile_tools.hpp"
using namespace std;
/***************************************************************************
函数名称：alltrim_item
功    能：去掉传入字符串前后的空格回车
输入参数：
返 回 值：去掉后的字符串
说    明：
***************************************************************************/
static char *alltrim_item(char *buf)
{
	char *p;
	/*去除尾部空格*/
	p = &buf[strlen(buf) - 1];
	while (*p && (*p == 0x0d || *p == 0x0a || *p == 0x20 || *p == 0x09))
		p--;
	*(p + 1) = 0;
	/*去除=后面的注释*/
	p = strchr(buf, '=');
	if (p)
		*p = '\0';
	//#号后面的东西不需要
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
函数名称：item_trim
功    能：去掉传入字符串前后的空格回车
输入参数：
返 回 值：去掉后的字符串
说    明：
***************************************************************************/

void item_trim(char *item)
{
	char *p;

	/*去除#和;后面的注释*/
	p = strchr(item, '#');
	if (p)
		*p = '\0';
	p = strchr(item, ';');
	if (p)
		*p = '\0';
	p = &item[0];
	while (*p != '=')
		p++;
	p++;
	memmove(item, p, strlen(p) + 1);


	/*去除尾部空格*/
	p = &item[strlen(item) - 1];
	while (*p && (*p == 0x0d || *p == 0x0a || *p == 0x20 || *p == 0x09))
		p--;
	*(p + 1) = 0;

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
	/*去除注释*/
	p = &buf[0];
	while (*p && *p != '#'&&*p != ';')
		p++;
	*p = 0;
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
说    明：此函数允许放到 common_cfgfile_tools.cpp 中做为内部工具函数
***************************************************************************/
static int file_length(fstream &fp)
{
	int file_len, now_pos;

	/* 当前为错误状态则返回-1 */
	if (fp.fail())
		return -1;

	/* 取fp当前指针位置 */
	now_pos = int(fp.tellg());

	/* 将文件指针移动到最后，此时tellp的结果就是文件大小 */
	fp.seekg(0, ios::end);
	file_len = int(fp.tellp());

	/* 指针移动回函数调用前的原位置 */
	fp.seekg(now_pos, ios::beg);

	return file_len;
}

/***************************************************************************
函数名称：
功    能：
输入参数：
返 回 值：
说    明：此函数允许放到 common_cfgfile_tools.cpp 中做为内部工具函数
***************************************************************************/
static int file_resize(const char *filename, fstream &fp, int newsize)
{
	int now_pos;

	/* 当前为错误状态则返回-1 */
	if (fp.fail())
		return -1;

	/* 取fp当前指针位置 */
	now_pos = int(fp.tellg());

	/* 如果大小是负数则直接返回-1 */
	if (newsize < 0)
		return -1;

	experimental::filesystem::resize_file(filename, newsize);

	/* 如果当前文件指针超过了文件大小，则回到文件头 */
	if (now_pos > newsize)
		fp.seekg(0, ios::beg);

	return 0;
}


int open_cfgfile(fstream &fp, const char *cfgname, const int opt)
{
	int suc_fail = 1;
	if (opt == OPEN_OPT_RDWR)
	{
		fp.open(cfgname, ios::app | ios::out);
		if (fp.is_open() == 0)
			suc_fail = 0;
		fp.close();


		fp.open(cfgname, ios::in | ios::out | ios::binary);
		if (fp.is_open() == 0)
			suc_fail = 0;
	}
	if (opt == OPEN_OPT_RDONLY)
	{
		fp.open(cfgname, ios::app | ios::out);
		if (fp.is_open() == 0)
			suc_fail = 0;
		fp.close();

		fp.open(cfgname, ios::in);
		if (fp.is_open() == 0)
			suc_fail = 0;
	}
	return suc_fail;
}

void close_cfgfile(fstream &fp)
{
	fp.close();
}

int group_add(fstream &fp, const char *group_name)
{
	int suc_fail = 1;
	char groupname[64] = { 0 };
	char groupcheck[64] = { 0 };
	strcpy(groupname, "[");
	strcat(groupname, group_name);
	strcat(groupname, "]");

	while (!fp.eof())
	{
		/*从文件中一行一行读取*/
		if (!fp.getline(groupcheck, sizeof(groupcheck)))
			break;
		alltrim(groupcheck);
		if (strcmp(groupcheck, groupname) == 0)
		{
			suc_fail = 0;
		}
	}
	fp.clear();
	fp.seekp(0, ios::end);
	if (suc_fail == 1)
	{
		fp << '\r' << '\n';
		fp << "[" << group_name << "]" << '\r' << '\n';
	}
	fp.seekg(0, ios::beg);
	return suc_fail;
}


int group_del(fstream &fp, const char *filename, const char *group_name)
{

	int num_of_delete = 0;
	int delete_flag = 0;
	int size_of_file = file_length(fp);
	char *filelast = new char[size_of_file];//动态申请文件大小的空间
	if (filelast == NULL)
	{
		cout << "申请失败";
	}
	long headloc = -1;                   //记录要删除组名位置
	long tailloc;                    //记录下一个组名出现位置
	char groupname[64] = { 0 };
	char groupcheck[64] = { 0 };
	char nextgroup[64] = { 0 };
	strcpy(groupname, "[");
	strcat(groupname, group_name);
	strcat(groupname, "]");
	fp.clear();
	fp.seekg(0, ios::beg);
	while (!fp.eof())
	{
		headloc = long(fp.tellg());
		if (!fp.getline(groupcheck, sizeof(groupcheck)))
			break;
		alltrim(groupcheck);
		if (strcmp(groupcheck, groupname) == 0)           //找到要删除的组名   继续寻找下一个组名
		{
			num_of_delete++;
			while (!fp.eof())               //继续读取  直到找到下一个组名
			{
				tailloc = long(fp.tellg());
				if (!fp.getline(nextgroup, sizeof(nextgroup)))
					break;
				alltrim(nextgroup);
				if (strstr(nextgroup, "[") && strstr(nextgroup, "]"))
					break;
			}
			if (!fp.eof())               //找到了下一个组名 且没读到文件尾
			{
				//fp.clear();
				fp.seekg(tailloc, ios::beg);
				fp.read((char *)filelast, size_of_file - tailloc);
				filelast[size_of_file - tailloc] = '\0';
				fp.clear();
				fp.seekg(headloc, ios::beg);
				fp << filelast;
				file_resize(filename, fp, size_of_file - (tailloc - headloc));
			}
			else
			{
				file_resize(filename, fp, headloc);
				fp.clear();                //没找到下一个组名 tailloc在文件结尾
			}
			size_of_file = file_length(fp);
			fp.clear();
			fp.seekg(headloc, ios::beg);
		}
	}
	delete filelast;
	fp.clear();
	return num_of_delete;
}

int item_add(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	int flagerror = 0;
	int headloc = -1;
	int suc_fail = 0;
	int size_of_file = file_length(fp);
	char*filelast = new char[size_of_file];
	if (filelast == NULL)
	{
		cout << "申请失败";
	}
	char groupname[64] = { 0 };
	char groupcheck[64] = { 0 };
	char itemcheck[64] = { 0 };
	strcpy(groupname, "[");
	strcat(groupname, group_name);
	strcat(groupname, "]");
	fp.seekg(0, ios::beg);

	while (!fp.eof())
	{
		/*从文件中一行一行读取*/
		if (!fp.getline(groupcheck, sizeof(groupcheck)))
		{
			flagerror = 1;
			break;
		}
		alltrim(groupcheck);
		if (strcmp(groupcheck, groupname) == 0)
		{
			headloc = int(fp.tellg());             //要插入位置
			suc_fail = 1;
			break;
		}
	}
	fp.clear();
	fp.seekg(headloc, ios::beg);
	while (!fp.eof())                               //判断是否已经存在项
	{
		/*从文件中一行一行读取*/
		if (!fp.getline(itemcheck, sizeof(itemcheck)))
		{
			flagerror = 1;
			break;
		}
		alltrim(groupcheck);
		if (strstr(itemcheck, item_name))
		{
			return 0;
		}
	}
	fp.clear();
	fp.seekp(headloc, ios::beg);
	fp.clear();
	fp.read(filelast, size_of_file - headloc);
	fp.clear();
	fp.seekp(headloc, ios::beg);
	fp << item_name << "=";
	if (item_type == TYPE_INT)
	{
		int value = *(int*)(item_value);
		fp << value << '\r' << '\n';
	}
	if (item_type == TYPE_DOUBLE)
	{
		double value = *(double*)(item_value);
		fp << setprecision(10) << value << '\r' << '\n';
	}
	if (item_type == TYPE_STRING)
	{
		char value[64] = { 0 };
		strcpy(value, (char*)(item_value));
		fp << value << '\r' << '\n';
	}
	if (item_type == TYPE_CHARACTER)
	{
		char value = *(char*)(item_value);
		fp << value << '\r' << '\n';
	}
	if (item_type == TYPE_NULL)
	{
		fp << '\r' << '\n';
	}
	fp.write(filelast, size_of_file - headloc);
	delete filelast;
	return suc_fail;
}

int item_del(fstream &fp, const char *filename, const char *group_name, const char *item_name)
{
	int num_of_delete = 0;
	int delete_flag = 0;
	int find_item_flag = 0;
	int group_flag = 0;
	int lastline = 0;
	int size_of_file = file_length(fp);
	char *filelast = new char[size_of_file];//动态申请文件大小的空间
	if (filelast == NULL)
	{
		cout << "申请失败";
	}
	int itemloc1 = -1;                   //记录要删除组名位置
	int itemloc2 = -1;                   //记录开始读取剩余内容的位置
	char groupname[64] = { 0 };
	char groupcheck[64] = { 0 };
	char checkitem[64] = { 0 };
	strcpy(groupname, "[");
	strcat(groupname, group_name);
	strcat(groupname, "]");
	fp.clear();
	fp.seekg(0, ios::beg);
	if (group_name == NULL)
	{
		while (!fp.eof())
		{
			itemloc1 = int(fp.tellg());
			if (!fp.getline(checkitem, sizeof(checkitem)) || fp.eof())
			{
				lastline = 1;
				break;
			}
			alltrim(checkitem);
			if (strstr(checkitem, item_name))
			{

				find_item_flag = 1;
				itemloc2 = int(fp.tellg());
			}
			if (find_item_flag == 1)
			{
				fp.read(filelast, size_of_file - itemloc2);
				fp.seekg(itemloc1, ios::beg);
				fp.write(filelast, size_of_file - itemloc2);
				file_resize(filename, fp, size_of_file - (itemloc2 - itemloc1));
				size_of_file = file_length(fp);
				num_of_delete++;
				fp.clear();
				fp.seekg(itemloc1, ios::beg);
				find_item_flag = 0;
			}
		}
		file_resize(filename, fp, itemloc1);
	}
	else
	{
		while (!fp.eof())
		{
			if (!fp.getline(groupcheck, sizeof(groupcheck)))
				break;
			alltrim(groupcheck);
			if (strcmp(groupcheck, groupname) == 0)           //找到要删除的组名   继续寻找项目名
			{
				while (!fp.eof())
				{
					itemloc1 = int(fp.tellg());
					if (!fp.getline(checkitem, sizeof(checkitem)) || fp.eof())
					{
						lastline = 1;
						break;
					}
					alltrim(checkitem);

					if (strstr(checkitem, item_name))
					{
						find_item_flag = 1;
						itemloc2 = int(fp.tellg());
					}
					if (find_item_flag == 1)
					{
						fp.read(filelast, size_of_file - itemloc2);
						fp.seekg(itemloc1, ios::beg);
						fp.write(filelast, size_of_file - itemloc2);
						file_resize(filename, fp, size_of_file - (itemloc2 - itemloc1));
						size_of_file = file_length(fp);
						num_of_delete++;
						fp.clear();
						fp.seekg(itemloc1, ios::beg);
						find_item_flag = 0;
					}
					if (strstr(checkitem, "[") != NULL && strstr(checkitem, "]") != NULL)
					{
						group_flag = 1;
						break;
					}
				}
				if (group_flag == 0)
					file_resize(filename, fp, itemloc1);
				else
					break;
			}
		}
	}
	delete filelast;
	fp.clear();
	return num_of_delete;
}

int item_update(fstream &fp, const char *filename, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	int item_add(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
	int item_del(fstream &fp, const char *filename, const char *group_name, const char *item_name);
	fp.seekg(0, ios::beg);
	int find_group = 0;
	int group_flag = 0;
	int find_first_item = 0;
	int itemloc1 = -1;                         //记录需要更新的位置
	int itemloc2 = -1;
	int size_of_file = file_length(fp);
	char *filelast = new char[size_of_file];//动态申请文件大小的空间
	char groupname[64] = { 0 };
	char groupcheck[64] = { 0 };
	char checkitem[64] = { 0 };
	strcpy(groupname, "[");
	strcat(groupname, group_name);
	strcat(groupname, "]");
	fp.clear();
	fp.seekg(0, ios::beg);
	while (!fp.eof())
	{
		/*从文件中一行一行读取*/
		if (!fp.getline(groupcheck, sizeof(groupcheck)))
			break;
		alltrim(groupcheck);
		if (strcmp(groupcheck, groupname) == 0)           //找到要更新的组名   继续寻找项目名
		{
			find_group = 1;
			while (!fp.eof())
			{
				itemloc1 = int(fp.tellg());
				if (!fp.getline(checkitem, sizeof(checkitem)))
					break;
				alltrim(checkitem);
				if (strstr(checkitem, item_name))
				{
					itemloc2 = int(fp.tellg());
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
		item_del(fp, filename, group_name, item_name);
		size_of_file = file_length(fp);
		fp.clear();
		fp.seekg(itemloc1, ios::beg);
		fp.read(filelast, size_of_file - itemloc1);

		fp.clear();
		fp.seekp(itemloc1, ios::beg);
		fp << item_name << "=";
		if (item_type == TYPE_INT)
		{
			int value = *(int*)(item_value);
			fp << value;
		}
		if (item_type == TYPE_DOUBLE)
		{
			double value = *(double*)(item_value);
			fp << value;
		}
		if (item_type == TYPE_STRING)
		{
			char value[64] = { 0 };
			strcpy(value, (char*)(item_value));
			fp << value;
		}
		if (item_type == TYPE_CHARACTER)
		{
			char value = *(char*)(item_value);
			fp << value;
		}
		if (item_type == TYPE_NULL)
		{
		}
		fp << "\r\n";
		fp.write(filelast, size_of_file - itemloc1);
	}
	if (find_first_item == 0)
	{
		fp.clear();
		item_add(fp, group_name, item_name, item_value, item_type);
	}
	return 1;
}

int item_get_value(fstream &fp, const char *group_name, const char *item_name, void *item_value, const enum ITEM_TYPE item_type)
{

	char groupname[128];
	groupname[0] = '\0';
	strcat(groupname, "[");
	strcat(groupname, group_name);
	strcat(groupname, "]");

	fp.clear();
	fp.seekg(0, ios::beg);//每次从头开始查找

	char groupcheck[128];
	char itemchaeck[128];
	char itemvalue[128];

	long before_location;
	int group_flag = 0;
	int item_flag = 0;
	while (fp.peek() != EOF)// !fp.eof()
	{
		fp.getline(groupcheck, 128, '\n');
		alltrim(groupcheck);//去除注释
		if (strstr(groupcheck, groupname))
		{
			while (fp.peek() != EOF)//!fp.eof()
			{

				before_location = (long)fp.tellg();
				fp.getline(itemchaeck, 128, '\n'); //读取一行信息

				strcpy(itemvalue, itemchaeck);
				alltrim_item(itemchaeck);

				if (strcmp(itemchaeck, item_name) == 0)//找到项目
				{
					item_flag = 1;
					item_trim(itemvalue);
					switch (item_type)
					{
						case TYPE_INT:
						{
							*(int *)item_value = atoi(itemvalue);
							break;
						}
						case TYPE_DOUBLE:
						{
							double value;
							sscanf(itemvalue, "%lf", &value);
							*(double *)item_value = value;
							break;
						}
						case TYPE_STRING:
						{
							strcpy((char *)item_value, itemvalue);
							break;
						}
						case TYPE_CHARACTER:
						{
							*(char *)item_value = *itemvalue;
							break;
						}
						case TYPE_NULL:
						{
							break;
						}
						default:
							break;
					}
					return item_flag;
				}
			}
			break;
		}
	}
	fp.clear();
	return item_flag;
}
