/*������ ��2 1752528*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <io.h>
#include<stdlib.h>
#include <conio.h>
#include<string.h>

#include "common_cfgfile_tools.h"
/***************************************************************************
�������ƣ�double_to_str
��    �ܣ�ȥ�������ַ���ǰ��Ŀո�س�
���������
�� �� ֵ��ȥ������ַ���
˵    ����
***************************************************************************/
static char *deletezero(char *buf)
{
	char *p;
	/*ȥ��β���ո�*/
	p = &buf[strlen(buf) - 1];
	while (*p &&*p == '0')
		p--;
	*(p + 1) = 0;
	return buf;
}


/***************************************************************************
�������ƣ�alltrim
��    �ܣ�ȥ�������ַ���ǰ��Ŀո�س�
���������
�� �� ֵ��ȥ������ַ���
˵    ����
***************************************************************************/
static char *alltrim(char *buf)
{
	char *p;
	/*ȥ��β���ո�*/
	p = &buf[strlen(buf) - 1];
	while (*p && (*p == 0x0d || *p == 0x0a || *p == 0x20 || *p == 0x09))
		p--;
	*(p + 1) = 0;
	/*ȥ��ͷ���ո�*/
	p = &buf[0];
	while (*p && (*p == 0x0d || *p == 0x0a || *p == 0x20 || *p == 0x09))
		p++;
	/*p�ƶ���buf����β��*/
	if (p != buf)
		memmove(buf, p, strlen(p) + 1);

	return buf;
}
/***************************************************************************
�������ƣ�
��    �ܣ�
���������
�� �� ֵ��
˵    �����˺�������ŵ� common_cfgfile_tools.c ����Ϊ�ڲ����ߺ���
***************************************************************************/
static int file_length(FILE *fp)
{
	int file_len, now_pos;

	/* ȡfp��ǰָ��λ�� */
	now_pos = ftell(fp);

	/* ���ļ�ָ���ƶ�����󣬴�ʱtellp�Ľ�������ļ���С */
	fseek(fp, 0, SEEK_END);
	file_len = ftell(fp);

	/* ָ���ƶ��غ�������ǰ��ԭλ�� */
	fseek(fp, now_pos, SEEK_SET);

	return file_len;
}

/***************************************************************************
�������ƣ�
��    �ܣ�
���������
�� �� ֵ��
˵    �����˺�������ŵ� common_cfgfile_tools.c ����Ϊ�ڲ����ߺ���
***************************************************************************/
static int file_resize(FILE *fp, int newsize)
{
	int now_pos = ftell(fp);
	/* �����С�Ǹ�����ֱ�ӷ���-1 */
	if (newsize < 0)
		return -1;

	_chsize(_fileno(fp), newsize);

	/* �����ǰ�ļ�ָ�볬�����ļ���С����rewind */
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
	char *filelast = (char*)malloc(size_of_file);//��̬�����ļ���С�Ŀռ�
	if (filelast == NULL)
	{
		fprintf(stdout, "%s", "����ʧ��");
	}
	int headloc = -1;                   //��¼Ҫɾ������λ��
	int tailloc = -1;                  //��¼��һ����������λ��
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
		if (strcmp(groupcheck, groupname) == 0)           //�ҵ�Ҫɾ��������   ����Ѱ����һ������
		{
			num_of_delete++;
			while (!feof(fp))               //������ȡ  ֱ���ҵ���һ������
			{
				tailloc = (int)(ftell(fp));
				fgets(nextgroup, sizeof(nextgroup), fp);
				alltrim(nextgroup);
				if (strstr(nextgroup, "[") && strstr(nextgroup, "]"))
					break;
			}
			if (!feof(fp))               //�ҵ�����һ������ ��û�����ļ�β
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
				file_resize(fp, headloc);//û�ҵ���һ������ tailloc���ļ���β
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
	char *filelast = (char*)malloc(size_of_file);//��̬�����ļ���С�Ŀռ�
	if (filelast == NULL)
	{
		fprintf(stdout, "%s", "����ʧ��");
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
		/*���ļ���һ��һ�ж�ȡ*/
		if (fgets(groupcheck, sizeof(groupcheck), fp) == NULL)
			break;
		alltrim(groupcheck);
		if (strcmp(groupcheck, groupname) == 0)
		{
			headloc = (int)(ftell(fp));            //Ҫ����λ��
			suc_fail = 1;
			break;
		}
	}
	fseek(fp, headloc, SEEK_SET);
	while (!feof(fp))                               //�ж��Ƿ��Ѿ�������
	{
		/*���ļ���һ��һ�ж�ȡ*/
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
	char *filelast = (char*)malloc(size_of_file);//��̬�����ļ���С�Ŀռ�
	if (filelast == NULL)
	{
		fprintf(stdout, "%s", "����ʧ��");
	}
	int itemloc1 = -1;                   //��¼Ҫɾ������λ��
	int itemloc2 = -1;                   //��¼��ʼ��ȡʣ�����ݵ�λ��
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
			if (strcmp(groupcheck, groupname) == 0)           //�ҵ�Ҫɾ��������   ����Ѱ����Ŀ��
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
	int itemloc1 = -1;                         //��¼��Ҫ���µ�λ��
	int itemloc2 = -1;
	int size_of_file = file_length(fp);
	char *filelast = (char*)malloc(size_of_file);//��̬�����ļ���С�Ŀռ�
	char groupname[64] = { 0 };
	char groupcheck[64] = { 0 };
	char checkitem[64] = { 0 };
	strcpy(groupname, "[");
	strcat(groupname, group_name);
	strcat(groupname, "]");
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		/*���ļ���һ��һ�ж�ȡ*/
		if (fgets(groupcheck, sizeof(groupcheck), fp) == NULL)
			break;
		alltrim(groupcheck);
		if (strcmp(groupcheck, groupname) == 0)           //�ҵ�Ҫ���µ�����   ����Ѱ����Ŀ��
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
	char *filelast = (char*)malloc(size_of_file);//��̬�����ļ���С�Ŀռ�

	char groupname[64] = { 0 };
	char groupcheck[64] = { 0 };
	char itemcheck[64] = { 0 };
	strcpy(groupname, "[");
	strcat(groupname, group_name);
	strcat(groupname, "]");
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		/*���ļ���һ��һ�ж�ȡ*/
		fgets(groupcheck, sizeof(groupcheck), fp);
		alltrim(groupcheck);
		if (strcmp(groupcheck, groupname) == 0)
		{
			suc_fail = 1;
			break;
		}
	}
	if (suc_fail == 1)                                 //���������
	{
		while (!feof(fp))                               //�ҵ�Ҫ���ҵ���
		{
			/*���ļ���һ��һ�ж�ȡ*/
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
		/*p�ƶ���buf����β��*/
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

