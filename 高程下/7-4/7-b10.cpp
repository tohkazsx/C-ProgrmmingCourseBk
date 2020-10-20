#include<iostream>
using namespace std;
int main(int arcg, char *argv[]) //1:检查学号 2:匹配学号 3:源文件名 4:阈值 5:输出
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
			cout << "匹配学号与检查学号相同" << endl;
			flag = 1;
		}
		for (int i = 0; i < 7; i++)
		{
			if (flag1==0&&(argv[1][i]<'0' || argv[1][i]>'9'))
			{
				cout << "检查学号错误" << endl;
				flag = 1;
				break;
			}
		}
		for (int i = 0; i < 7; i++)
		{
			if (flag2 == 0 && (argv[2][i]<'0' || argv[2][i]>'9'))
			{
				cout << "匹配学号错误" << endl;
				flag = 1;
				break;
			}
		}
		if (flag1 == 0 && check != 7)
		{
			cout << "检查学号不是7位"<<endl;
			flag = 1;
		}
		if (flag2 == 0 && search != 7)
		{
			cout << "匹配学号不是7位"<<endl;
			flag = 1;
		}
		if (flag3 == 0 && namelength1 > 32)
		{
			cout << "源程序文件名长度超过了32位"<<endl;
			flag = 1;
		}
		if (flag5 == 0 && namelength2 > 32)
		{
			cout << "输出文件名长度超过了32位"<<endl;
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
			cout << "参数检查通过" << endl;
			cout << "检查学号：" << argv[1] << endl;
			cout << "匹配学号：" << argv[2] << endl;
			cout << "源文件名：" << argv[3] << endl;
			cout << "匹配阈值：" << num4 << endl;
			cout << "输出目标：" << argv[5] << endl;
		}
	}
}

int usage(const char *procname)
{
	cout << "Usage: " << procname << " 要检查的学号/all 匹配学号/all 源程序名/all 相似度阀值(60-100) 输出(filename/screen)" << endl;
	cout << "               1759999          1759998      all          80                screen" << endl;
	cout << "               1759999          all          3-b3.cpp     75                result.txt" << endl;
	cout << "               all              all          3-b3.cpp     80                check.dat" << endl;
	cout << "               all              all          all          85                screen" << endl;

	return 0;
}