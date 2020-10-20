#define _CRT_SECURE_NO_WARNINGS
#if defined(_MSC_VER)
#include<cstring>
#include <iostream>
#include <fstream>
#include<string.h>
#include <io.h>
struct student {
	char num[8];
	char name[8];
	char class1[12];
	char class2[12];
};
using namespace std;

int main(int arcg, char *argv[])
{
	int m = 0;
	int mode = 0;
	int count = 0;
	int hz = 0;   //.��λ��
	char zs[15] = { 0 };
	ifstream in;
	struct student info[20] = { 0 };
	struct student info_check = { 0 };
	char stuchecked[100][30] = { 0 };
	char checkfile[5][15] = { {"1-5.cpp"}, { "3-13-1.cpp" } ,{"3-13-2.cpp"}, {"3-b3.cpp"}, {"6-b6.cpp"} };
	if (arcg < 4)
	{
		cout << "��������" << endl;
		return -1;
	}
	if (strcmp(argv[1], "-checktitle") != 0)
	{
		cout << argv[1];
		cout << "��������" << endl;
		return -1;
	}
	char*classnum = argv[2];
	char*filename = argv[3];
	char studentnum[20] = { 0 };
	unsigned int i1;
	for ( i1= 0; i1 < strlen(filename); i1++)
	{
		if (filename[i1] == '.')
			hz = i1;
	}
	if ((filename[hz + 1] != 'c' && filename[hz + 1] != 'h' || filename[hz + 1] == '\0') && (strcmp(filename, "all") != 0))
	{
		cout << "����Դ�����ļ�" << endl;
		return -1;
	}
	if ((filename[hz + 1] == 'c'&&filename[hz + 2] != 'p'&& filename[hz + 2] != '\0') && (strcmp(filename, "all") != 0))
	{
		cout << "����Դ�����ļ�" << endl;
		return -1;
	}
	if ((filename[hz + 1] == 'c' && filename[hz + 2] == 'p' &&filename[hz + 3] != 'p') && (strcmp(filename, "all") != 0))
	{
		cout << "����Դ�����ļ�" << endl;
		return -1;
	}
	if (strcmp(filename, "all") == 0)
	{
		mode = 1;
	}
	/*��ȡ��Ӧ�κ�ѧ����Ϣ*/
	char filefold[100] = { 0 };
	strcpy(filefold, "./source/");
	strcat(filefold, classnum);
	strcat(filefold, ".dat");

	in.open(filefold, ios::in);
	if (!in.is_open())
	{
		cout << "�κŶ�Ӧ�ļ��в�����" << endl;
		return -1;
	}
	while (!in.eof())
	{
		in >> info[m].num;
		in >> info[m].name;
		in >> info[m].class1;
		in >> info[m].class2;
		m++;
	}
	cout << "Ӧ���ѧ����Ϣ:" << endl;
	for (int i = 0; i < m; i++)
	{
		cout << info[i].num << " ";
		cout << info[i].name << " ";
		cout << info[i].class1 << " ";
		cout << info[i].class2 << endl;
	}
	
	in.close();


	/*�ݹ����*/
	void dfsFolder(char* folderPath, struct student info[20], struct student info_check, char*filename, char*classnum, char*studentnum, char stuchecked[100][30],char checkfile[5][15],int & count, int mode);
	char path[100] = { 0 };
	strcpy(path, ".\\source");
	dfsFolder(path, info, info_check, filename, classnum, studentnum,stuchecked,checkfile,count, mode);
	if (mode == 0)
	{
		for (int i = 0; i < m; i++)
		{
			int cflag = 0;
			for (int j = 0; j < 100; j++)
			{
				if (strncmp(info[i].num, stuchecked[j], 7) == 0)
					cflag = 1;
			}
			if (cflag == 0)
			{
				cout << info[i].name << "  " << info[i].num << "  " << info[i].class1 << "  ";
				for (int k = 7; k < 20; k++)
				{
					if (stuchecked[i][k] != '\0')
						cout << stuchecked[i][k];
				}
				cout << "  δ�ύ" << endl;
			}
		}
	}
	if (mode == 1)
	{
		cout << "����δ�ύ" << endl;
	}
	return 0;
}
void dfsFolder(char* folderPath, struct student info[20], struct student info_check, char*filename, char*classnum, char*studentnum, char stuchecked[100][30], char checkfile[5][15], int & count, int mode) //mode 0Ϊ���ĳ��Դ�ļ� 1Ϊ�������
{
	_finddata_t FileInfo;
	int count_doc = 0;
	int count_stu = 0;
	int flag_check = 0;        //��鵥�����

	int if_up = 0;
	char strfind[100] = { '\0' };
	char document[15][100] = { '\0' };
	strcpy(strfind, folderPath);
	strcat(strfind, "\\*");
	if (mode == 0)
	{
		long Handle = _findfirst(strfind, &FileInfo);
		if (Handle == -1L)
		{
			cerr << "can not match the folder path" << endl;
			exit(-1);
		}

		do {
			//�ж��Ƿ�����Ŀ¼
			if ((FileInfo.attrib & _A_SUBDIR) && (strncmp(classnum, FileInfo.name, 6) == 0))
			{
				if ((strcmp(FileInfo.name, ".") != 0) && (strcmp(FileInfo.name, "..") != 0))
				{
					char newPath[100] = { '\0' };
					strcpy(newPath, folderPath);
					strcat(newPath, "\\");
					strcat(newPath, FileInfo.name);
					for (int i = 0; i < 7; i++)
					{
						studentnum[i] = FileInfo.name[i + 7];
					}
					dfsFolder(newPath, info, info_check, filename, classnum, studentnum, stuchecked, checkfile, count, mode);
				}
			}
			else
			{
				if (mode == 0)
				{
					if (strcmp(FileInfo.name, filename) == 0)
					{
						char pd[3];
						char check[4][20];
						int flag = 0;  //�ж��Ƿ�����Ѿ���������ȷ
						int flag1 = 0;
						int flag2 = 0;
						int flag_check_num = 0;    //��¼������Ŀ
						int flag_check_name = 0;
						int flag_check_class = 0;
						int stunum;    //��¼��׼ѧ�Ŷ�Ӧѧ��
						char filePath[100] = { '\0' };
						strcpy(filePath, folderPath);
						strcat(filePath, "\\");
						strcat(filePath, FileInfo.name);
						cout << filePath << endl;
						ifstream in;

						in.open(filePath, ios::in);
						if (!in.is_open())
						{
							cout << "�޷���Դ�ļ�" << endl;
						}
						char ch;
						while (1)                                     //�ж�ǰһ���Ƿ�Ϊ/*��//
						{
							ch = in.get();

							if (ch == '/')
							{

								ch = in.get();
								if (ch == '*')
								{
									flag1 = 1;
									break;
								}
								if (ch == '/')
								{
									flag1 = 2;
									break;
								}
							}
							if (ch != '\n'&&ch != '\r'&&ch != '\t'&&ch != ' ')
								break;
						}
						if (flag1 == 1)     //��ǰһ��Ϊ/*���ж��Ƿ�պ�
						{
							while (1)
							{
								ch = in.get();
								if (ch == '\n' || ch == '\r')
									break;
								if (ch == '*')
								{
									ch = in.get();
									if (ch == '/')
									{
										flag2 = 1;
									}
								}
							}
						}
						if (flag1 == 0 || (flag1 == 1 && flag2 == 0))
						{
							cout << "flag1=" << flag1 << endl;
							cout << "flag2=" << flag2 << endl;
							flag = 1;
							cout << "δȡ��������Ϣ" << endl;
						}
						in.close();

						in.open(filePath, ios::in);
						if (!in.is_open())
						{
							cout << "�޷���Դ�ļ�" << endl;
						}
						while (1)
						{
							ch = in.get();
							if (ch != ' '&&ch != '\t'&&ch != '\n'&&ch != '\r')
								break;
						}
						in.get(pd, 2);
						/*if (strcmp(pd, "/") != 0 && strcmp(pd, "*") != 0)
						{
							cout << "δȡ��������Ϣ" << endl;
							flag = 1;
						}*/

						if (strcmp(pd, "/") == 0)
						{
							for (int i = 0; i < 4; i++)
							{
								in >> check[i];
							}
							int count_cs = 4;
							for (int i = 0; i < 4; i++)
							{
								if (check[i][0] == '#' || check[i][0] == '*')
								{
									count_cs = i;
									break;
								}
							}
							if (count_cs < 3)
							{
								cout << "������Ϣ��ȫ" << endl;
								flag = 1;
							}                           //���������Ϣ����
							if (count_cs > 3)
							{
								cout << "������Ϣ����" << endl;
								flag = 1;
							}
						}
						if (strcmp(pd, "*") == 0)
						{
							int count_cs = 4;
							for (int i = 0; i < 4; i++)
							{
								in >> check[i];
							}
							for (int i = 0; i < 4; i++)
							{
								if (strstr(check[i], "*/") && strcmp(check[i], "*/") != 0)
								{
									count_cs = i;
									check[i][strlen(check[i]) - 2] = '\0';
								}
								if (strstr(check[i], "*/") && strcmp(check[i], "*/") == 0)
								{
									count_cs = i - 1;
								}
							}
							if (count_cs < 2)
							{
								cout << "������Ϣ��ȫ" << endl;
								flag = 1;
							}                           //���������Ϣ����
							if (count_cs > 2)
							{
								cout << "������Ϣ����" << endl;
								flag = 1;
							}
						}

						//////////////////////////////////////////////
						for (int j = 0; j < 20; j++)                   //��׼ѧ����dat�ж�Ӧ��ѧ��
						{
							if (strcmp(studentnum, info[j].num) == 0)
							{
								stunum = j;
							}
						}
						strcpy(stuchecked[count], info[stunum].num);
						strcat(stuchecked[count], FileInfo.name);
						count++;
						cout << "��׼ѧ��:" << info[stunum].num << endl;
						cout << "��׼����:" << info[stunum].name << endl;
						cout << "��׼�༶:" << info[stunum].class1 << "/" << info[stunum].class2 << endl;
						for (int i = 0; i < 4; i++)                            //ѧ�ż��
						{
							if (strcmp(check[i], info[stunum].num) == 0)
							{
								flag_check_num = 1;
							}
						}
						if (flag == 0 && flag_check_num == 0)
							cout << "ѧ�Ų�ƥ��" << endl;
						for (int i = 0; i < 4; i++)                            //�������
						{
							if (strcmp(check[i], info[stunum].name) == 0)
							{
								flag_check_name = 1;
							}
						}
						if (flag == 0 && flag_check_name == 0)
							cout << "������ƥ��" << endl;
						for (int i = 0; i < 4; i++)                           //�༶���
						{
							const char *class1 = info[stunum].class1;
							const char *class2 = info[stunum].class2;
							if (strstr(check[i], class1) || strstr(check[i], class2))
							{
								flag_check_class = 1;
							}
						}
						if (flag == 0 && flag_check_class == 0)
							cout << "�༶��ƥ��" << endl;
						if (flag_check_num == 1 && flag_check_name == 1 && flag_check_class == 1)
							cout << "���ͨ��" << endl;
						cout << endl;
						///////////////////////////////////////////////
						in.close();
					}
				}
			}
		} while (_findnext(Handle, &FileInfo) == 0);
		_findclose(Handle);
	}
	if (mode == 1)
	{
		long Handle = _findfirst(strfind, &FileInfo);
		if (Handle == -1L)
		{
			cerr << "can not match the folder path" << endl;
			exit(-1);
		}
		for (int ct = 0; ct < 5; ct++)
		{
			int upflag = 0;
			do {
				//�ж��Ƿ�����Ŀ¼
				if ((FileInfo.attrib & _A_SUBDIR) && (strncmp(classnum, FileInfo.name, 6) == 0))
				{
					if ((strcmp(FileInfo.name, ".") != 0) && (strcmp(FileInfo.name, "..") != 0))
					{
						char newPath[100] = { '\0' };
						strcpy(newPath, folderPath);
						strcat(newPath, "\\");
						strcat(newPath, FileInfo.name);
						for (int i = 0; i < 7; i++)
						{
							studentnum[i] = FileInfo.name[i + 7];
						}
					
						dfsFolder(newPath, info, info_check, filename, classnum, studentnum, stuchecked, checkfile, count, mode);
							if (upflag == 0)
						{
							for (int i = 0; i < 20; i++)
							{
								if (strcmp(studentnum, info[i].num) == 0)
									cout << info[i].name << "  " << checkfile[ct] << "  " << "δ�ύ" << endl;
							}
						}
						else
							upflag = 0;
					}
				}
				else
				{
					if (strcmp(FileInfo.name, checkfile[ct]) == 0)
					{
						upflag = 1;
						char pd[3];
						char check[4][20];
						int flag = 0;  //�ж��Ƿ�����Ѿ���������ȷ
						int flag1 = 0;
						int flag2 = 0;
						int flag_check_num = 0;    //��¼������Ŀ
						int flag_check_name = 0;
						int flag_check_class = 0;
						int stunum;    //��¼��׼ѧ�Ŷ�Ӧѧ��
						char filePath[100] = { '\0' };
						strcpy(filePath, folderPath);
						strcat(filePath, "\\");
						strcat(filePath, FileInfo.name);
						cout << filePath << endl;
						ifstream in;

						in.open(filePath, ios::in);
						if (!in.is_open())
						{
							cout << "�޷���Դ�ļ�" << endl;
						}
						char ch;
						while (1)                                     //�ж�ǰһ���Ƿ�Ϊ/*��//
						{
							ch = in.get();

							if (ch == '/')
							{

								ch = in.get();
								if (ch == '*')
								{
									flag1 = 1;
									break;
								}
								if (ch == '/')
								{
									flag1 = 2;
									break;
								}
							}
							if (ch != '\n'&&ch != '\r'&&ch != '\t'&&ch != ' ')
								break;
						}
						if (flag1 == 1)     //��ǰһ��Ϊ/*���ж��Ƿ�պ�
						{
							while (1)
							{
								ch = in.get();
								if (ch == '\n' || ch == '\r')
									break;
								if (ch == '*')
								{
									ch = in.get();
									if (ch == '/')
									{
										flag2 = 1;
									}
								}
							}
						}
						if (flag1 == 0 || (flag1 == 1 && flag2 == 0))
						{
							cout << "flag1=" << flag1 << endl;
							cout << "flag2=" << flag2 << endl;
							flag = 1;
							cout << "δȡ��������Ϣ" << endl;
						}
						in.close();

						in.open(filePath, ios::in);
						if (!in.is_open())
						{
							cout << "�޷���Դ�ļ�" << endl;
						}
						while (1)
						{
							ch = in.get();
							if (ch != ' '&&ch != '\t'&&ch != '\n'&&ch != '\r')
								break;
						}
						in.get(pd, 2);
						/*if (strcmp(pd, "/") != 0 && strcmp(pd, "*") != 0)
						{
						cout << "δȡ��������Ϣ" << endl;
						flag = 1;
						}*/

						if (strcmp(pd, "/") == 0)
						{
							for (int i = 0; i < 4; i++)
							{
								in >> check[i];
							}
							int count_cs = 4;
							for (int i = 0; i < 4; i++)
							{
								if (check[i][0] == '#' || check[i][0] == '*')
								{
									count_cs = i;
									break;
								}
							}
							if (count_cs < 3)
							{
								cout << "������Ϣ��ȫ" << endl;
								flag = 1;
							}                           //���������Ϣ����
							if (count_cs > 3)
							{
								cout << "������Ϣ����" << endl;
								flag = 1;
							}
						}
						if (strcmp(pd, "*") == 0)
						{
							int count_cs = 4;
							for (int i = 0; i < 4; i++)
							{
								in >> check[i];
							}
							for (int i = 0; i < 4; i++)
							{
								if (strstr(check[i], "*/") && strcmp(check[i], "*/") != 0)
								{
									count_cs = i;
									check[i][strlen(check[i]) - 2] = '\0';
								}
								if (strstr(check[i], "*/") && strcmp(check[i], "*/") == 0)
								{
									count_cs = i - 1;
								}
							}
							if (count_cs < 2)
							{
								cout << "������Ϣ��ȫ" << endl;
								flag = 1;
							}                           //���������Ϣ����
							if (count_cs > 2)
							{
								cout << "������Ϣ����" << endl;
								flag = 1;
							}
						}

						//////////////////////////////////////////////
						for (int j = 0; j < 20; j++)                   //��׼ѧ����dat�ж�Ӧ��ѧ��
						{
							if (strcmp(studentnum, info[j].num) == 0)
							{
								stunum = j;
							}
						}
						strcpy(stuchecked[count], info[stunum].num);
						strcat(stuchecked[count], FileInfo.name);
						count++;
						cout << "��׼ѧ��:" << info[stunum].num << endl;
						cout << "��׼����:" << info[stunum].name << endl;
						cout << "��׼�༶:" << info[stunum].class1 << "/" << info[stunum].class2 << endl;
						for (int i = 0; i < 4; i++)                            //ѧ�ż��
						{
							if (strcmp(check[i], info[stunum].num) == 0)
							{
								flag_check_num = 1;
							}
						}
						if (flag == 0 && flag_check_num == 0)
							cout << "ѧ�Ų�ƥ��" << endl;
						for (int i = 0; i < 4; i++)                            //�������
						{
							if (strcmp(check[i], info[stunum].name) == 0)
							{
								flag_check_name = 1;
							}
						}
						if (flag == 0 && flag_check_name == 0)
							cout << "������ƥ��" << endl;
						for (int i = 0; i < 4; i++)                           //�༶���
						{
							const char *class1 = info[stunum].class1;
							const char *class2 = info[stunum].class2;
							if (strstr(check[i], class1) || strstr(check[i], class2))
							{
								flag_check_class = 1;
							}
						}
						if (flag == 0 && flag_check_class == 0)
							cout << "�༶��ƥ��" << endl;
						if (flag_check_num == 1 && flag_check_name == 1 && flag_check_class == 1)
							cout << "���ͨ��" << endl;
						cout << endl;
						///////////////////////////////////////////////
						in.close();
					}
				}
			} while (_findnext(Handle, &FileInfo) == 0);
		}
		_findclose(Handle);
	}
}

#elif defined(__linux) || defined(__linux__)

#include <iostream>
#include <fstream>
#include <unistd.h> 
#include <stdlib.h>  
#include<string.h>
#include <sys/stat.h>   
#include <sys/types.h>
#include <dirent.h>
struct student {
	char num[8];
	char name[8];
	char class1[12];
	char class2[12];
};
using namespace std;

int main(int arcg, char *argv[])
{
	int m = 0;
	int mode = 0;
	int count = 0;
	int hz = 0;   //.��λ��
	char zs[15] = { 0 };
	ifstream in;
	struct student info[20] = { 0 };
	struct student info_check = { 0 };
	char stuchecked[100][30] = { 0 };
	char checkfile[5][15] = { { "1-5.cpp" },{ "3-13-1.cpp" } ,{ "3-13-2.cpp" },{ "3-b3.cpp" },{ "6-b6.cpp" } };
	if (arcg < 4)
	{
		cout << "��������" << endl;
		return -1;
	}
	if (strcmp(argv[1], "-checktitle") != 0)
	{
		cout << argv[1];
		cout << "��������" << endl;
		return -1;
	}
	char*classnum = argv[2];
	char*filename = argv[3];
	char studentnum[20] = { 0 };
	for (int i = 0; i < strlen(filename); i++)
	{
		if (filename[i] == '.')
			hz = i;
	}
	if ((filename[hz + 1] != 'c' && filename[hz + 1] != 'h' || filename[hz + 1] == '\0') && (strcmp(filename, "all") != 0))
	{
		cout << "����Դ�����ļ�" << endl;
		return -1;
	}
	if ((filename[hz + 1] == 'c'&&filename[hz + 2] != 'p'&& filename[hz + 2] != '\0') && (strcmp(filename, "all") != 0))
	{
		cout << "����Դ�����ļ�" << endl;
		return -1;
	}
	if ((filename[hz + 1] == 'c' && filename[hz + 2] == 'p' &&filename[hz + 3] != 'p') && (strcmp(filename, "all") != 0))
	{
		cout << "����Դ�����ļ�" << endl;
		return -1;
	}
	if (strcmp(filename, "all") == 0)
	{
		mode = 1;
	}
	/*��ȡ��Ӧ�κ�ѧ����Ϣ*/
	char filefold[100] = { 0 };
	strcpy(filefold, "./source/");
	strcat(filefold, classnum);
	strcat(filefold, ".dat");

	in.open(filefold, ios::in);
	if (!in.is_open())
	{
		cout << "�κŶ�Ӧ�ļ��в�����" << endl;
		return -1;
	}
	while (!in.eof())
	{
		in >> info[m].num;
		in >> info[m].name;
		in >> info[m].class1;
		in >> info[m].class2;
		m++;
	}
	cout << "Ӧ���ѧ����Ϣ:" << endl;
	for (int i = 0; i < m; i++)
	{
		cout << info[i].num << " ";
		cout << info[i].name << " ";
		cout << info[i].class1 << " ";
		cout << info[i].class2 << endl;
	}
	in.close();


	void dfsFolder(char* folderPath, struct student info[20], struct student info_check, char*filename, char*classnum, char*studentnum, char stuchecked[100][30], int & count, int mode);
	char path[100] = { 0 };
	strcpy(path, "./source");
	dfsFolder(path, info, info_check, filename, classnum, studentnum,stuchecked,count, mode);
	if (mode == 0)
	{
		for (int i = 0; i < m; i++)
		{
			int cflag = 0;
			for (int j = 0; j < 100; j++)
			{
				if (strncmp(info[i].num, stuchecked[j], 7) == 0)
					cflag = 1;
			}
			if (cflag == 0)
			{
				cout << info[i].name << "  " << info[i].num << "  " << info[i].class1 << "  ";
				for (int k = 7; k < 20; k++)
				{
					if (stuchecked[i][k] != '\0')
						cout << stuchecked[i][k];
				}
				cout << "  δ�ύ" << endl;
			}
		}
	}
	if (mode == 1)
	{
		cout << "����δ�ύ" << endl;
	}
	return 0;
}
void dfsFolder(char* folderPath, struct student info[20], struct student info_check, char*filename, char*classnum, char*studentnum, char stuchecked[100][30], int & count, int mode)
{
	DIR            *dir;
	struct stat statbuf;
	struct dirent  *node;
	
	/* ��Linux��  Ŀ¼ */
	if ((dir = opendir(folderPath)) == NULL)
		cout<<"��ʧ��";
	/* ѭ��ɨ���Ŀ¼�µ������ļ� */
	while ((node = readdir(dir)) != NULL)
	{
		char newPath[100] = { '\0' };
		strcpy(newPath, folderPath);
		strcat(newPath, "/");
		strcat(newPath, node->d_name);
		stat(newPath, &statbuf);
		if (S_ISDIR(statbuf.st_mode) && (strncmp(classnum, node->d_name, 6) == 0))
		{
			if (strcmp(node->d_name, ".") == 0 || strcmp(node->d_name, "..") == 0)
				continue;
			for (int i = 0; i < 7; i++)
			{
				studentnum[i] = node->d_name[i + 7];
			}
		dfsFolder(newPath, info, info_check, filename, classnum, studentnum,stuchecked,count, mode);
		}
		else
		{
			if (mode == 0)
			{
				if (strcmp(node->d_name, filename) == 0)
				{
					char pd[3];
					char check[4][20];
					int flag = 0;  //�ж��Ƿ�����Ѿ���������ȷ
					int flag1 = 0;
					int flag2 = 0;
					int flag_check_num = 0;    //��¼������Ŀ
					int flag_check_name = 0;
					int flag_check_class = 0;
					int stunum;    //��¼��׼ѧ�Ŷ�Ӧѧ��
					char filePath[100] = { '\0' };
					strcpy(filePath, folderPath);
					strcat(filePath, "/");
					strcat(filePath, node->d_name);
					cout <<"λ��:"<< filePath << endl;
					ifstream in;

					in.open(filePath, ios::in);
						if (!in.is_open())
						{
							cout << "�޷���Դ�ļ�" << endl;
						}
						char ch;
						while (1)                                     //�ж�ǰһ���Ƿ�Ϊ/*��//
						{
							ch = in.get();

							if (ch == '/')
							{

								ch = in.get();
								if (ch == '*')
								{
									flag1 = 1;
									break;
								}
								if (ch == '/')
								{
									flag1 = 2;
									break;
								}
							}
							if (ch != '\n'&&ch != '\r'&&ch != '\t'&&ch != ' ')
								break;
						}
						if (flag1 == 1)     //��ǰһ��Ϊ/*���ж��Ƿ�պ�
						{
							while (1)
							{
								ch = in.get();
								if (ch == '\n' || ch == '\r')
									break;
								if (ch == '*')
								{
									ch = in.get();
									if (ch == '/')
									{
										flag2 = 1;
									}
								}
							}
						}
						if (flag1 == 0 || (flag1 == 1 && flag2 == 0))
						{
							cout << "flag1=" << flag1 << endl;
							cout << "flag2=" << flag2 << endl;
							flag = 1;
							cout << "δȡ��������Ϣ" << endl;
						}
						in.close();


					in.open(filePath, ios::in);
					if (!in.is_open())
					{
						cout << "�޷���Դ�ļ�" << endl;
					}
					
					while (1)
					{
						ch = in.get();
						if (ch != ' '&&ch != '\t'&&ch != '\n'&&ch != '\r')
							break;
					}
					in.get(pd, 2);
					/*if (strcmp(pd, "/") != 0 && strcmp(pd, "*") != 0)
					{
						cout << "δȡ��������Ϣ" << endl;
						flag = 1;
					}*/

					if (strcmp(pd, "/") == 0)
					{
						for (int i = 0; i < 4; i++)
						{
							in >> check[i];
						}
						/*for (int i = 0; i < 3; i++)
						{
							cout << check[i] << endl;
						}*/
						int count_cs = 4;
						for (int i = 0; i < 4; i++)
						{
							if (check[i][0] == '#' || check[i][0] == '*')
							{
								count_cs = i;
								break;
							}
						}
						if (count_cs < 3)
						{
							cout << "������Ϣ��ȫ" << endl;
							flag = 1;
						}                           //���������Ϣ����
						if (count_cs > 3)
						{
							cout << "������Ϣ����" << endl;
							flag = 1;
						}
					}
					if (strcmp(pd, "*") == 0)
					{
						int count_cs = 4;
						for (int i = 0; i < 4; i++)
						{
							in >> check[i];
						}
						for (int i = 0; i < 4; i++)
						{
							if (strstr(check[i], "*/") && strcmp(check[i], "*/") != 0)
							{
								count_cs = i;
								check[i][strlen(check[i]) - 2] = '\0';
							}
							if (strstr(check[i], "*/") && strcmp(check[i], "*/") == 0)
							{
								count_cs = i - 1;
							}
						}
						if (count_cs < 2)
						{
							cout << "������Ϣ��ȫ" << endl;
							//flag = 1;
						}                           //���������Ϣ����
						if (count_cs > 2)
						{
							cout << "������Ϣ����" << endl;
							//flag = 1;
						}
						/*for (int i = 0; i < 3; i++)
						{
							cout << check[i] << endl;
						}*/
					}

					//////////////////////////////////////////////
					for (int j = 0; j < 20; j++)                   //��׼ѧ����dat�ж�Ӧ��ѧ��
					{
						if (strcmp(studentnum, info[j].num) == 0)
						{
							stunum = j;
						}
					}
					strcpy(stuchecked[count], info[stunum].num);
					strcat(stuchecked[count], node->d_name);
					count++;
					cout << "��׼ѧ��:" << info[stunum].num << endl;
					cout << "��׼����:" << info[stunum].name << endl;
					cout << "��׼�༶:" << info[stunum].class1 << "/" << info[stunum].class2 << endl;
					for (int i = 0; i < 4; i++)                            //ѧ�ż��
					{
						if (strcmp(check[i], info[stunum].num) == 0)
						{
							flag_check_num = 1;
						}
					}
					if (flag == 0 && flag_check_num == 0)
						cout << "ѧ�Ų�ƥ��" << endl;
					for (int i = 0; i < 4; i++)                            //�������
					{
						if (strcmp(check[i], info[stunum].name) == 0)
						{
							flag_check_name = 1;
						}
					}
					if (flag == 0 && flag_check_name == 0)
						cout << "������ƥ��" << endl;
					for (int i = 0; i < 4; i++)                           //�༶���
					{
						const char *class1 = info[stunum].class1;
						const char *class2 = info[stunum].class2;
						if (strstr(check[i], class1) || strstr(check[i], class2))
						{
							flag_check_class = 1;
						}
					}
					if (flag == 0 && flag_check_class == 0)
						cout << "�༶��ƥ��" << endl;
					if (flag_check_num == 1 && flag_check_name == 1 && flag_check_class == 1)
						cout << "���ͨ��" << endl;
					cout << endl;
					///////////////////////////////////////////////
					in.close();
				}
				}
			if (mode == 1)
			{
				int xsd = 0;   //.��λ��
				int opflag = 0;
				for (int i = 0; i < strlen(node->d_name); i++)
				{
					if (node->d_name[i] == '.')
						xsd = i;
				}
				if (node->d_name[xsd + 1] != 'c' && node->d_name[xsd + 1] != 'h' || node->d_name[xsd + 1] == '\0')
				{
					opflag = 1;
				}
				if (node->d_name[xsd + 1] == 'c'&&node->d_name[xsd + 2] != 'p'&& node->d_name[xsd + 2] != '\0')
				{
					opflag = 1;
				}
				if (node->d_name[xsd + 1] == 'c' && node->d_name[xsd + 2] == 'p' &&node->d_name[xsd + 3] != 'p')
				{
					opflag = 1;
				}
				if (opflag == 0)
				{
					char pd[3];
					char check[4][20];
					int flag = 0;  //�ж��Ƿ�����Ѿ���������ȷ
					int flag1 = 0;
					int flag2 = 0;
					int flag_check_num = 0;    //��¼������Ŀ
					int flag_check_name = 0;
					int flag_check_class = 0;
					int stunum;    //��¼��׼ѧ�Ŷ�Ӧѧ��
					char filePath[100] = { '\0' };
					strcpy(filePath, folderPath);
					strcat(filePath, "/");
					strcat(filePath, node->d_name);
					cout << filePath << endl;
					ifstream in;

					in.open(filePath, ios::in);
					if (!in.is_open())
					{
						cout << "�޷���Դ�ļ�" << endl;
					}
					char ch;
					while (1)                                     //�ж�ǰһ���Ƿ�Ϊ/*��//
					{
						ch = in.get();

						if (ch == '/')
						{

							ch = in.get();
							if (ch == '*')
							{
								flag1 = 1;
								break;
							}
							if (ch == '/')
							{
								flag1 = 2;
								break;
							}
						}
						if (ch != '\n'&&ch != '\r'&&ch != '\t'&&ch != ' ')
							break;
					}
					if (flag1 == 1)     //��ǰһ��Ϊ/*���ж��Ƿ�պ�
					{
						while (1)
						{
							ch = in.get();
							if (ch == '\n' || ch == '\r')
								break;
							if (ch == '*')
							{
								ch = in.get();
								if (ch == '/')
								{
									flag2 = 1;
								}
							}
						}
					}
					if (flag1 == 0 || (flag1 == 1 && flag2 == 0))
					{
						cout << "flag1=" << flag1 << endl;
						cout << "flag2=" << flag2 << endl;
						flag = 1;
						cout << "δȡ��������Ϣ" << endl;
					}
					in.close();


					in.open(filePath, ios::in);
					if (!in.is_open())
					{
						cout << "�޷���Դ�ļ�" << endl;
					}
					while (1)
					{
						ch = in.get();
						if (ch != ' '&&ch != '\t'&&ch != '\n'&&ch != '\r')
							break;
					}
					in.get(pd, 2);
					if (strcmp(pd, "/") != 0 && strcmp(pd, "*") != 0)
					{
						cout << "δȡ��������Ϣ" << endl;
						flag = 1;
					}

					if (strcmp(pd, "/") == 0)
					{
						for (int i = 0; i < 4; i++)
						{
							in >> check[i];
						}
						for (int i = 0; i < 3; i++)
						{
							cout << check[i] << endl;
						}
						int count_cs = 4;
						for (int i = 0; i < 4; i++)
						{
							if (check[i][0] == '#' || check[i][0] == '*')
							{
								count_cs = i;
								break;
							}
						}
						if (count_cs < 3)
						{
							cout << "������Ϣ��ȫ" << endl;
							flag = 1;
						}                           //���������Ϣ����
						if (count_cs > 3)
						{
							cout << "������Ϣ����" << endl;
							flag = 1;
						}
					}
					if (strcmp(pd, "*") == 0)
					{
						int count_cs = 4;
						for (int i = 0; i < 4; i++)
						{
							in >> check[i];
						}
						for (int i = 0; i < 4; i++)
						{
							if (strstr(check[i], "*/") && strcmp(check[i], "*/") != 0)
							{
								count_cs = i;
								check[i][strlen(check[i]) - 2] = '\0';
							}
							if (strstr(check[i], "*/") && strcmp(check[i], "*/") == 0)
							{
								count_cs = i - 1;
							}
						}
						if (count_cs < 2)
						{
							cout << "������Ϣ��ȫ" << endl;
							//flag = 1;
						}                           //���������Ϣ����
						if (count_cs > 2)
						{
							cout << "������Ϣ����" << endl;
							//flag = 1;
						}
						for (int i = 0; i < 3; i++)
						{
							cout << check[i] << endl;
						}
					}

					//////////////////////////////////////////////
					for (int j = 0; j < 20; j++)                   //��׼ѧ����dat�ж�Ӧ��ѧ��
					{
						if (strcmp(studentnum, info[j].num) == 0)
						{
							stunum = j;
						}
					}
					strcpy(stuchecked[count], info[stunum].num);
					strcat(stuchecked[count], node->d_name);
					count++;
					cout << "��׼ѧ��:" << info[stunum].num << endl;
					cout << "��׼����:" << info[stunum].name << endl;
					cout << "��׼�༶:" << info[stunum].class1 << "/" << info[stunum].class2 << endl;
					for (int i = 0; i < 4; i++)                            //ѧ�ż��
					{
						if (strcmp(check[i], info[stunum].num) == 0)
						{
							flag_check_num = 1;
						}
					}
					if (flag == 0 && flag_check_num == 0)
						cout << "ѧ�Ų�ƥ��" << endl;
					for (int i = 0; i < 4; i++)                            //�������
					{
						if (strcmp(check[i], info[stunum].name) == 0)
						{
							flag_check_name = 1;
						}
					}
					if (flag == 0 && flag_check_name == 0)
						cout << "������ƥ��" << endl;
					for (int i = 0; i < 4; i++)                           //�༶���
					{
						const char *class1 = info[stunum].class1;
						const char *class2 = info[stunum].class2;
						if (strstr(check[i], class1) || strstr(check[i], class2))
						{
							flag_check_class = 1;
						}
					}
					if (flag == 0 && flag_check_class == 0)
						cout << "�༶��ƥ��" << endl;
					if (flag_check_num == 1 && flag_check_name == 1 && flag_check_class == 1)
						cout << "���ͨ��" << endl;
					cout << endl;
					///////////////////////////////////////////////
					in.close();
				}
			}
		}
	 }//end of whileɨ��
	 /* �ر� Ŀ¼ */
	closedir(dir);
}
#endif

