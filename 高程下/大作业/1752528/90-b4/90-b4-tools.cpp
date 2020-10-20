/*朱世轩 计2 1752528*/
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include<iostream>
#include <atlconv.h>
#include <stdio.h>
#include<iomanip>
#include "90-b4.h"
#include "../common/cmd_console_tools.h"
using namespace std;
/*工具函数*/
/****************************************************************/
//UTF-8到GB2312的转换
char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

//GB2312到UTF-8的转换                                   //转码用
char* G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

//将UTF8串转化为二进制串
void StrToBinary(char c[], char binary[])
{
	int count = 0;
	for (int i = 0; c[i]; i++)
	{
		for (int j = 7; j >= 0; j--)
		{
			cout << ((c[i] & 1 << j) != 0);
			binary[count] = ((c[i] & 1 << j) != 0) + '0';
			count++;
		}
		cout << " ";
	}
	binary[count] = 0;
}

//将二进制串转成十进制码字
void QREncode::prt_binary()
{
	unsigned char *code = new unsigned char[QR_VersonInfo[m_nVersion].ncAllCodeWord];
	int i, j;
	for (i = 0; i < QR_VersonInfo[m_nVersion].ncAllCodeWord; i++)
	{
		code[i] = 0;
		for (j = 8 * i; j < 8 * i + 8; j++)
			code[i] = code[i] + (m_byWordData[j] - '0')*(1 << (7 - j % 8));
	}
	for (i = 0; i < QR_VersonInfo[m_nVersion].ncDataCodeWord[m_nLevel]; i++)
	{
		m_byDataCodeWord[i] = code[i];
	}
	//加尾零
	m_byDataCodeWord[QR_VersonInfo[m_nVersion].ncAllCodeWord] = '\0';
	delete code;
}

//将十进制串转成二进制码字
/*void QREncode::prt_dec()
{
	int count = 0;
	for (int i = 0;i<nc; i++)
	{
		for (int j = 7; j >= 0; j--)
		{
			cout << ((c[i] & 1 << j) != 0);
			binary[count] = ((c[i] & 1 << j) != 0) + '0';
			count++;
		}
		cout << " ";
	}
	binary[count] = 0;
}*/

/*取得编码信息 计算纠错码*/
/****************************************************************/
//取得字符计数码
void QREncode::GetCountCode(const char*data)
{
	int countdata = int(strlen(data));
	cout << countdata << endl;     //test
	for (int i = 7; i >= 0; i--)
	{
		m_CountCode[7 - i] = ((countdata >> i) & 1) + '0';
	}
	m_CountCode[8] = 0;
}

//整合编码信息
void QREncode::GetEncodeInfo()
{
	int count = 0;
	int datalength = int(strlen((char*)(m_byWordData)));
	m_ModeCode[0] = '0';
	m_ModeCode[1] = '1';
	m_ModeCode[2] = '0';
	m_ModeCode[3] = '0';
	for (int i = 0; i < 4; i++)
	{
		m_byWordData[count] = m_ModeCode[i];
		count++;
	}
	for (int i = 0; i < 8; i++)
	{
		m_byWordData[count] = m_CountCode[i];
		count++;
	}
	for (int i = 0; i < datalength; i++)
	{
		m_byWordData[count] = m_byWordDatapre[i];
		count++;
	}
}

//对编码信息进行补位  待处理数据在m_byWordData中
void QREncode::InsertBit()
{
	int count = 0;
	int count_insert = 0;
	int flag = 0;
	int datalength = int(strlen(m_byWordData));                         //取得未补位时的长度
	cout << datalength << endl;                                      //test
	int Maxlength = QR_VersonInfo[m_nVersion].ncDataCodeWord[m_nLevel];       //取得应该补到的长度
	cout << Maxlength << endl;
	m_ncAllCodeWord = QR_VersonInfo[m_nVersion].ncAllCodeWord;
	char Bit[2][10] = {                                                //预置补位数组
		{ "11101100" } ,
		{ "00010001" },
	};
	for (int i = datalength; i < Maxlength * 8; i++)            //补0至被8整除
	{
		m_byWordData[i] = '0';
		count++;
		if ((i + 1) % 8 == 0)
			break;
	}
	datalength = datalength + count;                         //更新数据长度
	cout << datalength << endl;
	for (int i = datalength; i < Maxlength * 8; i = i + 8)   //交替补码串直到最大长度
	{
		for (int j = 0; j < 8; j++)
		{
			if (flag % 2 == 0)
				m_byWordData[i + j] = Bit[0][j];
			else
				m_byWordData[i + j] = Bit[1][j];

		}
		count_insert = count_insert + 8;
		flag++;
	}
	datalength = datalength + count_insert;                      //更新数据长度
	cout << datalength << endl;
	m_byWordData[datalength] = 0;
}

//通过转化后的字符串大小 获取对应版本号
int QREncode::GetVersion(int nLevel, const char* lpsSource, int ncLength)
{

	for (int i = 1; i < 41; i++)
	{
		if (DataNum[i][nLevel] > ncLength)
		{
			m_nVersion = i;
			break;
		}
	}
	return m_nVersion;
}

//通过多项式计算获取RS码字 n是总码字数 k是数据码字数
unsigned char* RS_Code(int n, int k, unsigned char *data_codewords)
{
	//GF(2^8) α^(0 ~ 254), 令 0 = α^255
	unsigned char GF_2_8[256] = { 1,   2,   4,   8,  16,  32,  64, 128,  29,  58, 116, 232, 205, 135,  19,  38,
		76, 152,  45,  90, 180, 117, 234, 201, 143,   3,   6,  12,  24,  48,  96, 192,
		157,  39,  78, 156,  37,  74, 148,  53, 106, 212, 181, 119, 238, 193, 159,  35,
		70, 140,   5,  10,  20,  40,  80, 160,  93, 186, 105, 210, 185, 111, 222, 161,
		95, 190,  97, 194, 153,  47,  94, 188, 101, 202, 137,  15,  30,  60, 120, 240,
		253, 231, 211, 187, 107, 214, 177, 127, 254, 225, 223, 163,  91, 182, 113, 226,
		217, 175,  67, 134,  17,  34,  68, 136,  13,  26,  52, 104, 208, 189, 103, 206,
		129,  31,  62, 124, 248, 237, 199, 147,  59, 118, 236, 197, 151,  51, 102, 204,
		133,  23,  46,  92, 184, 109, 218, 169,  79, 158,  33,  66, 132,  21,  42,  84,
		168,  77, 154,  41,  82, 164,  85, 170,  73, 146,  57, 114, 228, 213, 183, 115,
		230, 209, 191,  99, 198, 145,  63, 126, 252, 229, 215, 179, 123, 246, 241, 255,
		227, 219, 171,  75, 150,  49,  98, 196, 149,  55, 110, 220, 165,  87, 174,  65,
		130,  25,  50, 100, 200, 141,   7,  14,  28,  56, 112, 224, 221, 167,  83, 166,
		81, 162,  89, 178, 121, 242, 249, 239, 195, 155,  43,  86, 172,  69, 138,   9,
		18,  36,  72, 144,  61, 122, 244, 245, 247, 243, 251, 235, 203, 139,  11,  22,
		44,  88, 176, 125, 250, 233, 207, 131,  27,  54, 108, 216, 173,  71, 142,   0 };
	//查表
	unsigned char _GF_2_8[256] = { 255,   0,   1,  25,   2,  50,  26, 198,   3, 223,  51, 238,  27, 104, 199,  75,
		4, 100, 224,  14,  52, 141, 239, 129,  28, 193, 105, 248, 200,   8,  76, 113,
		5, 138, 101,  47, 225,  36,  15,  33,  53, 147, 142, 218, 240,  18, 130,  69,
		29, 181, 194, 125, 106,  39, 249, 185, 201, 154,   9, 120,  77, 228, 114, 166,
		6, 191, 139,  98, 102, 221,  48, 253, 226, 152,  37, 179,  16, 145,  34, 136,
		54, 208, 148, 206, 143, 150, 219, 189, 241, 210,  19,  92, 131,  56,  70,  64,
		30,  66, 182, 163, 195,  72, 126, 110, 107,  58,  40,  84, 250, 133, 186,  61,
		202,  94, 155, 159,  10,  21, 121,  43,  78, 212, 229, 172, 115, 243, 167,  87,
		7, 112, 192, 247, 140, 128,  99,  13, 103,  74, 222, 237,  49, 197, 254,  24,
		227, 165, 153, 119,  38, 184, 180, 124,  17,  68, 146, 217,  35,  32, 137,  46,
		55,  63, 209,  91, 149, 188, 207, 205, 144, 135, 151, 178, 220, 252, 190,  97,
		242,  86, 211, 171,  20,  42,  93, 158, 132,  60,  57,  83,  71, 109,  65, 162,
		31,  45,  67, 216, 183, 123, 164, 118, 196,  23,  73, 236, 127,  12, 111, 246,
		108, 161,  59,  82,  41, 157,  85, 170, 251,  96, 134, 177, 187, 204,  62,  90,
		203,  89,  95, 176, 156, 169, 160,  81,  11, 245,  22, 235, 122, 117,  44, 215,
		79, 174, 213, 233, 230, 231, 173, 232, 116, 214, 244, 234, 168,  80,  88, 175 };

	short i, j;
	//Generator polynomial
	unsigned char *Gx = new(nothrow) unsigned char[n - k + 1];//only 8 bit per coefficient
	if (!Gx)
	{
		cerr << "内存申请失败\n";
		return NULL;
	}

	memset(Gx, 0, n - k + 1);

	Gx[n - k - 1] = 1;
	Gx[n - k] = GF_2_8[0];
	for (i = 1; i < n - k; i++)
	{
		//multiply by x
		for (j = 1; j < n - k + 1; j++)
			Gx[j - 1] = Gx[j];
		Gx[j - 1] = 0;
		//multiply by a^i
		for (j = n - k; j >= n - k - i; j--)
			Gx[j] = Gx[j] ^ GF_2_8[(_GF_2_8[Gx[j - 1]] + i) % 255];
	}

	//error correction codewords
	//message
	unsigned char *Mx = new(nothrow) unsigned char[n];//n = k + (n - k)
	if (!Mx)
	{
		cerr << "内存申请失败\n";
		return NULL;
	}

	for (i = 0; i < k; i++)
		Mx[i] = data_codewords[i];
	for (; i < n; i++)
		Mx[i] = 0;

	unsigned char *polynomial = new unsigned char[n];
	memset(polynomial, 0, n);
	short n_g = n - k + 1, n_p = n;// n = k + (n - k)

	for (--n_p; n_p >= n_g - 1;)
	{
		//multiply by Mx[n - 1 - n_p] and (n_p - n_g)
		for (i = n - 1 - n_p, j = 0; j < n_g; ++i, ++j)
			polynomial[i] = GF_2_8[(_GF_2_8[Gx[j]] + _GF_2_8[Mx[n - 1 - n_p]]) % 255];
		//minus
		for (i = n - 1 - n_p; i < n; ++i)
			Mx[i] ^= polynomial[i];
		for (--n_p; !Mx[n - 1 - n_p]; --n_p)
			;
	}

	delete[]Gx;
	delete[]polynomial;

	unsigned char *error_correction_codewords = new(nothrow) unsigned char[n - k];//only 8 bit per coefficient
	if (!error_correction_codewords)
	{
		cerr << "内存申请失败\n";
		return NULL;
	}
	for (i = 0; i < n - k; i++)
		error_correction_codewords[i] = Mx[n - 1 - n_p + i];
	delete[]Mx;
	return error_correction_codewords;
}

//对数据和纠错码进行分块填入总数据数组
void QREncode::BlockstoCode()
{
	//对数据码字分块 写入总数组
	int i, j;
	int count = 0;
	//两组分块中每组的块数
	int Block1 = QR_VersonInfo[m_nVersion].RS_BlockInfo1[m_nLevel].ncRSBlock;
	int Block2 = QR_VersonInfo[m_nVersion].RS_BlockInfo2[m_nLevel].ncRSBlock;
	int BlockSum = Block1 + Block2;
	int BlockNum = 0; // 处理块数总和

	int DataClass1 = QR_VersonInfo[m_nVersion].RS_BlockInfo1[m_nLevel].ncDataCodeWord;
	int DataClass2 = QR_VersonInfo[m_nVersion].RS_BlockInfo2[m_nLevel].ncDataCodeWord;

	for (i = 0; i < Block1; i++)         
	{
		for (j = 0; j < DataClass1; j++)
		{
			m_byAllCodeWord[(BlockSum * j) + BlockNum] = m_byDataCodeWord[count];
			count++;
		}
		BlockNum++;
	}

	for (i = 0; i < Block2; i++)         
	{
		for (j = 0; j < DataClass2; j++)
		{
			if (j < DataClass1)
			{
				m_byAllCodeWord[(BlockSum * j) + BlockNum] = m_byDataCodeWord[count];
				count++;
			}
			else
			{
				m_byAllCodeWord[(BlockSum * DataClass1) + i] = m_byDataCodeWord[count];
				count++;
			}
		}

		BlockNum++;
	}
	/////////////////////////////////////////////////////////////////////////
		//对纠错码字分块 写入总数组 

	int RSClass1 = QR_VersonInfo[m_nVersion].RS_BlockInfo1[m_nLevel].ncAllCodeWord - DataClass1;
	int RSClass2 = QR_VersonInfo[m_nVersion].RS_BlockInfo2[m_nLevel].ncAllCodeWord - DataClass2;

	count = 0;
	BlockNum = 0;

	for (i = 0; i < Block1; i++)
	{
		for (j = 0; j < RSClass1; j++)
			m_byAllCodeWord[ncDataCodeWord + (BlockSum * j) + BlockNum] = m_byRSWork[j];

		count = count + DataClass1;
		BlockNum++;
	}

	for (i = 0; i < Block2; i++)
	{
		for (j = 0; j < RSClass2; j++)
			m_byAllCodeWord[ncDataCodeWord + (BlockSum * j) + BlockNum] = m_byRSWork[j];

		count = count + DataClass2;
		BlockNum++;
	}
}

/*向矩阵填充信息 掩模*/
/****************************************************************/
//向矩阵内写入数据信息
void QREncode::FillMartrixCode()
{
	//填入功能信息后 矩阵内现在有信息部分为0 无信息部分为空格
	int x = m_nSymbleSize;         //定位坐标到矩阵右下角          
	int y = m_nSymbleSize - 1;
	int x_flag = 1;                 //坐标状态标记 设置前进状态 初始都是前进状态
	int y_flag = 1;
	int length_of_code = m_ncAllCodeWord;  //要写入矩阵所有数据的长度
	for (int i = 0; i < length_of_code; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			do   //如果是空格循环填充
			{
				x = x + x_flag;      //x坐标移动一格
				x_flag = x_flag* -1;//标记改变符号 下次反向
				if (x_flag < 0)
				{
					y = y + y_flag;  //y坐标移动一格
					if (y < 0 || y == m_nSymbleSize) //如果前进到边界 y坐标置0 到左边一列填充 否则继续前进
					{
						if (y < 0)
							y = 0;
						else
							y = m_nSymbleSize - 1;
						x = x - 2;
						y_flag = y_flag * -1;//标记改变符号 下次反向

						if (x == 6)
							x--;
					}
				}
			} while (m_byModuleData[x][y] & 0x20);//while 
			unsigned char codeword = 0;
			if (m_byAllCodeWord[i] & (1 << (7 - j))) //获取每个码字8位的二进制码 1赋真0赋假
				codeword = 2;
			else
				codeword = 0;
			m_byModuleData[x][y] = codeword;
		}//for
	}//for 直到填完所有数据 跳出循环
}

//向矩阵内写入功能模块（除数据之外的信息）
void QREncode::FillMartrixFunction()
{
	int i, j;
	ZeroMemory(m_byModuleData, sizeof(m_byModuleData));
	SetFinderPattern(0, 0);                //左上角寻像图形
	SetFinderPattern(m_nSymbleSize - 7, 0);//右上角寻像图形
	SetFinderPattern(0, m_nSymbleSize - 7);//左下角寻像图形
	for (i = 0; i < 8; i++)
	{
		m_byModuleData[i][7] = m_byModuleData[7][i] = ' ';
		m_byModuleData[m_nSymbleSize - 8][i] = m_byModuleData[m_nSymbleSize - 8 + i][7] = ' ';
		m_byModuleData[i][m_nSymbleSize - 8] = m_byModuleData[7][m_nSymbleSize - 8 + i] = ' ';
	}
	for (i = 0; i < 9; i++)
	{
		m_byModuleData[i][8] = m_byModuleData[8][i] = ' ';
	}

	for (i = 0; i < 8; i++)
	{
		m_byModuleData[m_nSymbleSize - 8 + i][8] = m_byModuleData[8][m_nSymbleSize - 8 + i] = ' ';
	}
	SetVersionPattern();                           //写入版本信息 
	//写入定位信息
	for (i = 0; i < QR_VersonInfo[m_nVersion].ncAlignPoint; ++i)
	{
		SetAlignmentPattern(QR_VersonInfo[m_nVersion].nAlignPoint[i], 6);
		SetAlignmentPattern(6, QR_VersonInfo[m_nVersion].nAlignPoint[i]);

		for (j = 0; j < QR_VersonInfo[m_nVersion].ncAlignPoint; j++)
		{
			SetAlignmentPattern(QR_VersonInfo[m_nVersion].nAlignPoint[i], QR_VersonInfo[m_nVersion].nAlignPoint[j]);
		}
	}

	for (i = 8; i <= m_nSymbleSize - 9; i++)
	{
		m_byModuleData[i][6] = ((i % 2) == 0 ? '0' : ' ');  //i为奇数写入字符0 否则写入空格 方便后面填数据判断操作
		m_byModuleData[6][i] = ((i % 2) == 0 ? '0' : ' ');
	}
}
//下面四个函数向矩阵内写入信息
//向矩阵内写入寻像信息
void QREncode::SetFinderPattern(int x, int y)
{
	//传入要写入的坐标x y
	static BYTE Pattern[] = { 0x7f,  // 1111111b
		0x41,  // 1000001b
		0x5d,  // 1011101b
		0x5d,  // 1011101b
		0x5d,  // 1011101b
		0x41,  // 1000001b
		0x7f }; // 1111111b
	int i, j;

	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
			m_byModuleData[x + j][y + i] = (Pattern[i] & (1 << (6 - j))) ? '0' : ' ';
	}
}

//向矩阵内写入定位信息
void QREncode::SetAlignmentPattern(int x, int y)
{ 
	//预置定位信息数组
	static BYTE Pattern[] = {    
		0x1f,  // 11111b
		0x11,  // 10001b
		0x15,  // 10101b
		0x11,  // 10001b
		0x1f }; // 11111b
	int i, j;

	if (m_byModuleData[x][y] & 0x20)
		return;
	x = x - 2;
	y = y - 2;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
			m_byModuleData[x + j][y + i] = (Pattern[i] & (1 << (4 - j))) ? '0' : ' ';
	}
}

//向矩阵内写入版本信息
void QREncode::SetVersionPattern()
{
	if (m_nVersion <= 6)           //版本号小于6不需要写入 直接返回
		return;

	int i, j, nVerData = m_nVersion << 12;
	for (i = 0; i < 6; i++)
	{
		if (nVerData & (1 << (17 - i)))
			nVerData ^= (0x1f25 << (5 - i));
	}

	nVerData = nVerData + (m_nVersion << 12);

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 3; j++)
			m_byModuleData[m_nSymbleSize - 11 + j][i] = m_byModuleData[i][m_nSymbleSize - 11 + j] = (nVerData & (1 << (i * 3 + j))) ? '\x30' : '\x20';
	}
}

//掩模 选择第一种掩模图形
void QREncode::Masking()
{
	for (int i = 0; i < m_nSymbleSize; i++)
	{
		for (int j = 0; j < m_nSymbleSize; j++)
		{
			if (!(m_byModuleData[j][i] == ' '))
			{
				int Maskflag;
				Maskflag = ((i + j) % 2 == 0);      //满足反转条件置1 否则置0
				//将编码区域数据与掩模异或
				m_byModuleData[j][i] = (BYTE)((m_byModuleData[j][i] & 0xfe) | (((m_byModuleData[j][i] & 0x02) > 1) ^ Maskflag));
			}
		}
	}
}
//设置格式信息（使用了现成函数）
void QREncode::SetFormatInfoPattern()
{
	int nFormatInfo;
	int i;
	// 纠错等级选择
	switch (m_nLevel)
	{
		case QR_LEVEL_M:
			nFormatInfo = 0x00; // 00nnnb
			break;

		case QR_LEVEL_L:
			nFormatInfo = 0x08; // 01nnnb
			break;

		case QR_LEVEL_Q:
			nFormatInfo = 0x18; // 11nnnb
			break;

		default: // case QR_LEVEL_H:
			nFormatInfo = 0x10; // 10nnnb
			break;
	}
	int nFormatData = nFormatInfo << 10;
	for (i = 0; i < 5; i++)
	{
		if (nFormatData & (1 << (14 - i)))
		{
			nFormatData ^= (0x0537 << (4 - i)); // 10100110111b
		}
	}

	nFormatData += nFormatInfo << 10;

	//将15位格式信息与掩模图形101010000010010进行XOR运算
	nFormatData ^= 0x5412; // 101010000010010b

						   // 横向0-5模块
	for (i = 0; i <= 5; i++)
		m_byModuleData[8][i] = (nFormatData & (1 << i)) ? '0' : ' ';
	// 交汇处三个模块
	m_byModuleData[8][7] = (nFormatData & (1 << 6)) ? '0' : ' ';
	m_byModuleData[8][8] = (nFormatData & (1 << 7)) ? '0' : ' ';
	m_byModuleData[7][8] = (nFormatData & (1 << 8)) ? '0' : ' ';
	// 横向9-14模块
	for (i = 9; i <= 14; i++)
		m_byModuleData[14 - i][8] = (nFormatData & (1 << i)) ? '0' : ' ';

	// 竖直从上到下前8个模块
	for (i = 0; i <= 7; i++)
		m_byModuleData[m_nSymbleSize - 1 - i][8] = (nFormatData & (1 << i)) ? '0' : ' ';
	// 竖直第8个模块上一个为深色模块
	m_byModuleData[8][m_nSymbleSize - 8] = '0'; // 
	// 竖直8-14模块
	for (i = 8; i <= 14; i++)
		m_byModuleData[8][m_nSymbleSize - 15 + i] = (nFormatData & (1 << i)) ? '0' : ' ';
}

//将最终结果写入矩阵
void QREncode::FilltheMatrix()
{
	for (int i = 0; i < m_nSymbleSize; i++)
	{
		for (int j = 0; j < m_nSymbleSize; j++)
			m_byModuleData[i][j] = (BYTE)((m_byModuleData[i][j] & 0x11) != 0);
	}
}