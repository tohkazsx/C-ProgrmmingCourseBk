#include<iostream>
using namespace std;
int main(int arcg, char *argv[]) //1:���ѧ�� 2:ƥ��ѧ�� 3:Դ�ļ��� 4:��ֵ 5:���
{
	int usage(const char *procname);
	if(arcg==1)
	usage(argv[0]);
	else
	{
		int check=0;
		int search=0;
		int namelength1 = 0;
		int namelength2 = 0;
		int numlength = 0;
		int flag = 0;
		int flag1 = 0;
		int flag2 = 0;
		int flag3 = 0;
		int flag5 = 0;
		int num4 = 0;
		for (int i = 0; argv[1][i] != 0; i++)
			check++;
		for (int j = 0; argv[2][j] != 0; j++)
			search++;
		for (int k = 0; argv[3][k] != 0; k++)
			namelength1++;
		for (int k = 0; argv[4][k] != 0; k++)
			numlength++;
		for (int k = 0; argv[5][k] != 0; k++)
			namelength2++;
		if (argv[1][0] == 'a'&&argv[1][1] == 'l'&&argv[1][2] == 'l')
			flag1 = 1;
		if (argv[2][0] == 'a'&&argv[2][1] == 'l'&&argv[2][2] == 'l')
			flag2 = 1;
		if (argv[3][0] == 'a'&&argv[3][1] == 'l'&&argv[3][2] == 'l')
			flag3 = 1;
		if (argv[5][0] == 's'&&argv[5][1] == 'c'&&argv[5][2] == 'r'&&argv[5][0] == 'e'&&argv[5][1] == 'e'&&argv[5][2] == 'n')
			flag5 = 1;
		if (strcmp(argv[1], argv[2]) == 0&&flag1==0&&flag2==0)
		{
			cout << "ƥ��ѧ������ѧ����ͬ" << endl;
			flag = 1;
		}
		for (int i = 0; i < 7; i++)
		{
			if (flag1==0&&(argv[1][i]<'0' || argv[1][i]>'9'))
			{
				cout << "���ѧ�Ŵ���" << endl;
				flag = 1;
				break;
			}
		}
		for (int i = 0; i < 7; i++)
		{
			if (flag2 == 0 && (argv[2][i]<'0' || argv[2][i]>'9'))
			{
				cout << "ƥ��ѧ�Ŵ���" << endl;
				flag = 1;
				break;
			}
		}
		if (flag1 == 0 && check != 7)
		{
			cout << "���ѧ�Ų���7λ"<<endl;
			flag = 1;
		}
		if (flag2 == 0 && search != 7)
		{
			cout << "ƥ��ѧ�Ų���7λ"<<endl;
			flag = 1;
		}
		if (flag3 == 0 && namelength1 > 32)
		{
			cout << "Դ�����ļ������ȳ�����32λ"<<endl;
			flag = 1;
		}
		if (flag5 == 0 && namelength2 > 32)
		{
			cout << "����ļ������ȳ�����32λ"<<endl;
			flag = 1;
		}
		num4 = (argv[4][0] - '0') * 10 + (argv[4][1] - '0');
		if (numlength != 2 )
		{
			num4 = 80;
		}
		else if (num4 <= 60 || num4 >= 100)
		{
			num4 = 80;
		}

		if (flag == 0)
		{
			cout << "�������ͨ��" << endl;
			cout << "���ѧ�ţ�" << argv[1] << endl;
			cout << "ƥ��ѧ�ţ�" << argv[2] << endl;
			cout << "Դ�ļ�����" << argv[3] << endl;
			cout << "ƥ����ֵ��" << num4 << endl;
			cout << "���Ŀ�꣺" << argv[5] << endl;
		}
	}
}

int usage(const char *procname)
{
	cout << "Usage: " << procname << " Ҫ����ѧ��/all ƥ��ѧ��/all Դ������/all ���ƶȷ�ֵ(60-100) ���(filename/screen)" << endl;
	cout << "               1759999          1759998      all          80                screen" << endl;
	cout << "               1759999          all          3-b3.cpp     75                result.txt" << endl;
	cout << "               all              all          3-b3.cpp     80                check.dat" << endl;
	cout << "               all              all          all          85                screen" << endl;

	return 0;
}