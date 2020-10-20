#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <conio.h>
using namespace std;

#include "../common/common_cfgfile_tools.hpp"
/*extern "C"
{
#include "../common/common_cfgfile_tools.h"
}*/

union cfg_value {
	int ivalue;
	double dvalue;
	char svalue[128];
	char cvalue;
	void *value;
};

struct cfg_item {
	const char *cfg_item_name;
	enum ITEM_TYPE cfg_item_type;
	union cfg_value cfg_item_value;
};

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾ��ʾ��Ϣ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void to_be_continued(const char *prompt)
{
	if (prompt)
		cout << prompt << "�����س�������...";
	else
		cout << "���س�������...";

	/* ���Գ��س�������������루ע�⣺_getch�Ļس���\r����getchar��\n��*/
	while (_getch() != '\r')
		;
	cout << endl;

	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���Ϊcfg_item�к��й����壬������ֻ�ܳ�ʼ����һ�����ú�����ʼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void set_item(struct cfg_item *item)
{
	item[0].cfg_item_value.ivalue = 123;
	item[1].cfg_item_value.dvalue = 123.45;
	strcpy(item[2].cfg_item_value.svalue, "Hello");
	item[3].cfg_item_value.cvalue = 'Y';
	//	item[4].cfg_item_value.ivalue = 0;
	item[5].cfg_item_value.ivalue = 99999;
	//	item[6].cfg_item_value.ivalue = 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
#if 0
int test_readconfig_c(const char *cfgname, const char **group_name, struct cfg_item *item)
{
	FILE *fp;
	int ret, i, j;
	char tmp[256];

	/* ��һ��ģ�⣬��������� */
	if (1) {
		remove(cfgname); //ɾ���ļ�

		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
			}

		for (i = 0; group_name[i]; i++) {
			if ((ret = group_add(fp, group_name[i])) <= 0)
				printf("����[%s]ʧ��.\n", group_name[i]);
			else
				printf("����[%s]�ɹ�.\n", group_name[i]);
		}
		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��Ƿ����8������", cfgname);
		to_be_continued(tmp);
	}

	/* �ڶ���ģ�⣬ÿ����������� */
	if (1) {
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}

		for (i = 0; group_name[i]; i++) {
			for (j = 0; item[j].cfg_item_name; j++) {
				sprintf(tmp, "%s-%s", group_name[i], item[j].cfg_item_name);
				/* ˵����item_add�ĵ�3��������void*����˲���ʲô���ͣ�������union��һ����Ա�ĵ�ַ����������Ա��ַ */
				if ((ret = item_add(fp, group_name[i], tmp, &(item[j].cfg_item_value.ivalue), item[j].cfg_item_type)) <= 0)
					printf("����[%s]/%s ʧ��.\n", group_name[i], tmp);
				else
					printf("����[%s]/%s �ɹ�.\n", group_name[i], tmp);
			}
		}
		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��Ƿ����8�������6��������", cfgname);
		to_be_continued(tmp);
	}

	/* ������ģ�⣬ɾ���鼰�� */
	if (1) {
		sprintf(tmp, "��������ļ�%s����[test3]�������ɷݣ�test2-itemB�������ɷݣ��Һ����ֵ���Ͳ�ͬ", cfgname);
		to_be_continued(tmp);

		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}

		printf("ɾ��[test3]��%d��\n", group_del(fp, "test3"));
		printf("ɾ��[test5]��%d��\n", group_del(fp, "test5"));

		printf("ɾ��<test2-itemB>��%d��\n", item_del(fp, "test2", "test2-itemB"));

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲�[test3]/[test5]/<test2-itemB>�Ƿ��ѱ�ɾ��", cfgname);
		to_be_continued(tmp);
	}

	/* ���Ĵ�ģ�⣬�޸��� */
	if (1) {
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}

		int a = 54321;
		double b = 1023.4567;
		char c = 'N';

		/* �Ѵ�������� */
		item_update(fp, "test4", "test4-itemB", &a, TYPE_INT);
		item_update(fp, "test1", "test1-itemD", "helloworld", TYPE_STRING);
		item_update(fp, "test8", "test8-itemE", &b, TYPE_DOUBLE);
		item_update(fp, "test6", "test6-itemF", NULL, TYPE_NULL);
		item_update(fp, "test7", "test7-itemC", &c, TYPE_CHARACTER);

		/* ����������� */
		item_update(fp, "test6", "test6-itemU", NULL, TYPE_NULL);
		item_update(fp, "test7", "test7-itemV", &c, TYPE_CHARACTER);
		item_update(fp, "test7", "test6-itemW", NULL, TYPE_NULL);
		item_update(fp, "test4", "test4-itemX", &a, TYPE_INT);
		item_update(fp, "test1", "test1-itemY", "helloworld", TYPE_STRING);
		item_update(fp, "test8", "test8-itemZ", &b, TYPE_DOUBLE);

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲����������Ƿ����޸�", cfgname);
		to_be_continued(tmp);
	}

	/* �����ģ�⣬�� */
	if (1) {
		fp = open_cfgfile(cfgname, OPEN_OPT_RDONLY);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}

		int a;
		double b;
		char c, s[80];

		/* �Ѵ�������� */
		if (item_get_value(fp, "test4", "test4-itemB", &a, TYPE_INT)>0)
			printf("[test4]/test4-itemB=%d\n", a);
		if (item_get_value(fp, "test1", "test1-itemF", &a, TYPE_INT)>0)
			printf("[test1]/test1-itemF=%d\n", a);
		if (item_get_value(fp, "test6", "test6-itemD", &c, TYPE_CHARACTER)>0)
			printf("[test6]/test6-itemD=%c\n", c);
		if (item_get_value(fp, "test8", "test8-itemC", s, TYPE_STRING)>0)
			printf("[test8]/test8-itemC=%s\n", s);
		if (item_get_value(fp, "test7", "test7-itemE", NULL, TYPE_NULL)>0)
			printf("[test7]/test7-itemE=<NULL>\n");
		if (item_get_value(fp, "test6", "test6-itemB", &b, TYPE_DOUBLE)>0)
			printf("[test6]/test6-itemB=%f\n", b);
		if (item_get_value(fp, "test1", "item100", NULL, TYPE_NULL)>0)
			printf("[test1]/item100=<NULL>\n");
		else
			printf("[test1]/item100 ������\n");

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��������ö�ȡ�Ƿ���ȷ", cfgname);
		to_be_continued(tmp);
	}

	return 0;
}
#endif

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int test_readconfig_cpp(const char *cfgname, const char **group_name, struct cfg_item *item)
{
	fstream fp;
	int ret, i;
	char tmp[256];

	/* ��һ��ģ�⣬��������� */
	if (1) {
		remove(cfgname); //ɾ���ļ�*/

		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR)==0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}
		for (i = 0; group_name[i]; i++) {
			if ((ret = group_add(fp, group_name[i])) <= 0)
				cout << "����[" << group_name[i] << "]ʧ��." << endl;
			else
				cout << "����[" << group_name[i] << "]�ɹ�." << endl;
		}
		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��Ƿ����8������", cfgname);
		to_be_continued(tmp);
	}

	/* �ڶ���ģ�⣬ÿ����������� */
	if (1) {
		int j;
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}

		for (i = 0; group_name[i]; i++) {
			for (j = 0; item[j].cfg_item_name; j++) {
				sprintf(tmp, "%s-%s", group_name[i], item[j].cfg_item_name);
				/* ˵����item_add�ĵ�3��������void*����˲���ʲô���ͣ�������union��һ����Ա�ĵ�ַ����������Ա��ַ */
				if ((ret = item_add(fp, group_name[i], tmp, &(item[j].cfg_item_value.ivalue), item[j].cfg_item_type)) <= 0)
					cout << "����[" << group_name[i] << "]/" << tmp << "ʧ��." << endl;
				else
					cout << "����[" << group_name[i] << "]/" << tmp << "�ɹ�." << endl;
			}
		}
		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��Ƿ����8�������6��������", cfgname);
		to_be_continued(tmp);
	}

	/* ������ģ�⣬ɾ���鼰�� */
	if (1) {
		sprintf(tmp, "��������ļ�%s����[test3]�������ɷݣ�test2-itemB�������ɷݣ��Һ����ֵ���Ͳ�ͬ", cfgname);
		to_be_continued(tmp);

		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}

		cout << "ɾ��[test3]��" << group_del(fp, cfgname, "test3")<< "��" << endl;
		cout << "ɾ��[test5]��" << group_del(fp, cfgname, "test5") << "��" << endl;

		cout << "ɾ��<test2-itemB>��" << item_del(fp, cfgname, "test2", "test2-itemB") << "��" << endl;

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲�[test3]/[test5]/<test2-itemB>�Ƿ��ѱ�ɾ��", cfgname);
		to_be_continued(tmp);
	}

	/* ���Ĵ�ģ�⣬�޸��� */
	if (1) {
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}

		int a = 54321;
		double b = 1023.4567;
		char c = 'N';

		/* �Ѵ�������� */
		item_update(fp, cfgname, "test4", "test4-itemB", &a, TYPE_INT);
		item_update(fp, cfgname, "test1", "test1-itemD", "helloworld", TYPE_STRING);
		item_update(fp, cfgname, "test8", "test8-itemE", &b, TYPE_DOUBLE);
		item_update(fp, cfgname, "test6", "test6-itemF", NULL, TYPE_NULL);
		item_update(fp, cfgname, "test7", "test7-itemC", &c, TYPE_CHARACTER);

		/* ����������� */
		item_update(fp, cfgname, "test6", "test6-itemU", NULL, TYPE_NULL);
		item_update(fp, cfgname, "test7", "test7-itemV", &c, TYPE_CHARACTER);
		item_update(fp, cfgname, "test7", "test6-itemW", NULL, TYPE_NULL);
		item_update(fp, cfgname, "test4", "test4-itemX", &a, TYPE_INT);
		item_update(fp, cfgname, "test1", "test1-itemY", "helloworld", TYPE_STRING);
		item_update(fp, cfgname, "test8", "test8-itemZ", &b, TYPE_DOUBLE);

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲����������Ƿ����޸�", cfgname);
		to_be_continued(tmp);
	}

	/* �����ģ�⣬�� */
	if (1) {
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDONLY) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}

		int a;
		double b;
		char c, s[80];

		/* �Ѵ�������� */
		if (item_get_value(fp, "test4", "test4-itemB", &a, TYPE_INT)>0)
			printf("[test4]/test4-itemB=%d\n", a);
		if (item_get_value(fp, "test1", "test1-itemF", &a, TYPE_INT)>0)
			printf("[test1]/test1-itemF=%d\n", a);
		if (item_get_value(fp, "test6", "test6-itemD", &c, TYPE_CHARACTER)>0)
			printf("[test6]/test6-itemD=%c\n", c);
		if (item_get_value(fp, "test8", "test8-itemC", s, TYPE_STRING)>0)
			printf("[test8]/test8-itemC=%s\n", s);
		if (item_get_value(fp, "test7", "test7-itemE", NULL, TYPE_NULL)>0)
			printf("[test7]/test7-itemE=<NULL>\n");
		if (item_get_value(fp, "test6", "test6-itemB", &b, TYPE_DOUBLE)>0)
			printf("[test6]/test6-itemB=%f\n", b);
		if (item_get_value(fp, "test1", "item100", NULL, TYPE_NULL)>0)
			printf("[test1]/item100=<NULL>\n");
		else
			printf("[test1]/item100 ������\n");

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��������ö�ȡ�Ƿ���ȷ", cfgname);
		to_be_continued(tmp);
	}

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	const char *cfgname = "c1.cfg";
	const char *group_name[] = {
		"test1",
		"test2",
		"test3",
		"test4",
		"test5",
		"test6",
		"test7",
		"test8",
		NULL
	};

	struct cfg_item item[] =
	{
		{ "itemA",TYPE_INT, 0 },		//������union�ĳ�ʼ����ֻ�ܳ�ʼ����һ��Ԫ��
		{ "itemB", TYPE_DOUBLE, 0 },
		{ "itemC",TYPE_STRING, 0 },
		{ "itemD",TYPE_CHARACTER, 0 },
		{ "itemE", TYPE_NULL, 0 },
		{ "itemF",TYPE_INT, 0 },
		{ NULL,TYPE_NULL, 0 }
	};
	set_item(item); //��union����ֵ

	test_readconfig_cpp(cfgname, group_name, item);
//	test_readconfig_c(cfgname, group_name, item);

	return 0;
}