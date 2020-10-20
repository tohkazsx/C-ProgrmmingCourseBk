#include<iostream>
#include <stdlib.h>
#include<string.h>
using namespace std;
int main(int arcg, char *argv[])
{
	int usage(const char *procname);
	int pf(const int ds, int sb);
	if (arcg == 1)
		usage(argv[0]);
	else
	{
		int flag = 0;
		int js = 0;
		int records = 0;
		int n = 100;
		int l = 128;
		int t = 0;
		int num[3], number = 0;
		int num_of_cs = 0;                                  //��¼��������
		int length_of_ip = 0;
		for (int i = 1; argv[i] != NULL; i++)
			num_of_cs++;
		for (int i = 0; argv[num_of_cs][i] != 0; i++)
			length_of_ip++;
		for (int i = 0; i <= length_of_ip; i++)
		{
			if (argv[num_of_cs][i] >= '0' && argv[num_of_cs][i] <= '9')
			{
				num[i - records] = argv[num_of_cs][i] - '0';
				js = js + 1;
				if (js > 3)
				{
					cout << "IP��ַ����"<<endl;
					flag = 1;
					break;
				}
			}
			if (argv[num_of_cs][i] == '.'|| argv[num_of_cs][i] == 0)
			{
				records = records + js + 1;
				for (int j = 0; j < js; j++)
				{
					number = number + pf(10, js-j-1)*num[j];
				}
				if (number > 256)
				{
					cout << "IP��ַ����"<<endl;
					flag = 1;
					break;
				}
				number = 0;
				js = 0;
			}
			if (argv[num_of_cs][i] != '.'&& argv[num_of_cs][i] != 0 && (argv[num_of_cs][i] < '0' || argv[num_of_cs][i] > '9'))
			{
				cout << "IP��ַ����" << endl;
				flag = 1;
				break;
			}
		}


		for (int i = 1; i <= num_of_cs; i++)
		{
			if (flag == 0)
			{
				if (strcmp(argv[i], "-l") == 0)
				{
					int a = atoi(argv[i + 1]);
					if (argv[i + 1][0] == '-' || i + 1 == num_of_cs)
					{
						cout << "����-lû�к�������"<<endl;
						flag = 1;
						break;
					}
					if (a >= 64 && a <= 64000)
					{
						l = a;
					}
				}
				if (strcmp(argv[i], "-n") == 0)
				{
					int a = atoi(argv[i + 1]);
					if (argv[i + 1][0] == '-'||i+1==num_of_cs)
					{
						cout << "����-nû�к�������" << endl;
						flag = 1;
						break;
					}
					if (a >= 1 && a <= 10000)
					{
						n = a;
					}
				}
				if (strcmp(argv[i], "-t") == 0)
				{
					if (argv[i + 1][0] != '-'&&( i + 1 != num_of_cs))
					{
						t = 1;
					}
				}
				if (argv[i][0] == '-'&&argv[i][1] != 'l'&&argv[i][1] != 'n'&&argv[i][1] != 't')
				{
					cout << "����" << argv[i] << "������" << endl;
					flag = 1;
					break;
				}
			}
	    }

		if (flag == 0)
		{
			cout << "�������ͨ��" << endl;
			cout << "-n����:" << n << endl;
			cout << "-l����:" << l << endl;
			cout << "-t����:" << t << endl;
			cout << "IP��ַ:" << argv[num_of_cs];
		}



	}
}
int usage(const char *procname)
{
	cout << "Usage: " << procname << "[-l ��С] [-n ����] [-t] IP��ַ" << endl;

	return 0;
}
int pf(const int ds, int sb)
{
	int result = 1;
	for (int i = 0; i < sb; i++)
	{
		result = result*ds;
	}
	return result;
}
