/*朱世轩 计2 1752528*/
#pragma once
#include <Windows.h>
#include "../common/cmd_console_tools.h"

#define MAX_MODULESIZE	  177 // 模块数最大值177*177
#define MAX_ALLCODEWORD	 3706 // 码字总数最大值3706（版本40）
#define MAX_DATACODEWORD 2956 // 数据码字最大值（版本40-L）
#define MAX_CODEBLOCK	  153 // 模块数据码字数最大值（包括RS码字）
#define COUNTCODE  10          //字符计数符位数
#define MODECODE   5         //模式指示符位数

#define QR_SIZE	10        // 生成二维码的字号大小

// 纠错级别
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

#define OK 1
#define FAILE -1
#define WIDETH_OF_QR 2

const int MAX_LENTH = 100;

void StrToBinary(char c[], char binary[]);                       //十进制串转为二进制
unsigned char* RS_Code(int n, int k, unsigned char *data_codewords);  //获取RS码字
char* G2U(const char* gb2312);                                 //转换编码至utf8


struct QREncode                          //定义结构体存放二维码相关信息
{
public:
	int m_nLevel;		// 纠错等级
	int m_nVersion;		// 版本
	int m_nMaskingNo;	// 纠错等级

	int m_nSymbleSize;                                    //图形大小
	BYTE m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; // 最终需要填充的矩阵

	int m_ncDataCodeWordBit; //输入数据长度
	//以下是二进制串相关数组
	char m_byWordDatapre[MAX_DATACODEWORD * 8];    //二进制01  数据码字转换后的数组
	char m_byWordData[MAX_DATACODEWORD * 8];    //二进制01  数据码字加入模式码 计数码信息后的数组
	char m_byRSData[MAX_DATACODEWORD * 8];    //二进制01  纠错码字转换后的数组
	char m_byAllData[MAX_ALLCODEWORD * 8];     //二进制01  所有数据（数据码字+纠错码）转换后数组
	char m_ModeCode[MODECODE];               //模式指示符
	char m_CountCode[COUNTCODE];               //字符计数符



	//以下是原串相关数组
	char m_byDatepre[MAX_DATACODEWORD];        //原始转utf8后的数据串
	BYTE m_byDataCodeWord[MAX_DATACODEWORD]; //数据码字数组（原串）
	int m_ncDataBlock;                      //数据块数

	//以下是存放相关信息的变量
	int m_ncAllCodeWord; //所有编码数据长度
	BYTE m_byAllCodeWord[MAX_ALLCODEWORD]; //所有数据数组
	BYTE m_byRSWork[MAX_CODEBLOCK]; // RS纠错码数组
	int ncDataCodeWord;//数据分块长度

	//获取编码数据
	/**************************************************************************************/
	int GetVersion(int nLevel, const char* lpsSource, int ncLength);//通过输入字符长度和选择的纠错等级 取得编码版本信息 level为纠错等级  lpsSource为传入字符串 ncLength为字符长度
	void GetCountCode(const char*data);        //获取字符计数符
	void GetEncodeInfo();                     //整合编码信息
	void InsertBit();                        //补位
	void prt_binary();               //将二进制串转成十进制串
	//void prt_dec();                  //将十进制串转成二进制串
	//void GetRSCodeWord(LPBYTE lpbyRSWork, int ncDataCodeWord, int ncRSCodeWord);//纠错码
	void BlockstoCode();                           //将数据和纠错码分块并存放至m_byAllCodeWord数组中
	/**************************************************************************************/

	//填充矩阵
	/**************************************************************************************/
	void FillMartrixCode();//编码信息
	void FillMartrixFunction();//功能模块 将定位信息和数据信息等填入矩阵 （调用下面的函数）
	void SetFinderPattern(int x, int y);//填充寻像图形
	void SetAlignmentPattern(int x, int y);//填充校正图形      
	void SetVersionPattern();//版本信息
	/**************************************************************************************/

	//掩模
	/**************************************************************************************/
	void Masking();//设置掩模图形
	void SetFormatInfoPattern();
	void FilltheMatrix();  //将最终结果写入矩阵
	/**************************************************************************************/

	//打印二维码
	/**************************************************************************************/
	int printQR(); //打印二维码函数 
	/**************************************************************************************/
};

void printMartrix(QREncode data);                               //打印出数据矩阵 测试用
//RS码数据结构
typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock;		// 纠错块数
	int ncAllCodeWord;	// 块内码字数
	int ncDataCodeWord;	// 数据码字数（码字数-RS码字数）

} RS_BLOCKINFO;


//QRcode版本相关信息
typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   // 版本号1-40
	int ncAllCodeWord; // 总码字数
	int ncDataCodeWord[4];	// 数据码字（总码字-RS码字）

	int ncAlignPoint;	// 校正点数
	int nAlignPoint[6];	// 校正图形中心坐标

	RS_BLOCKINFO RS_BlockInfo1[4]; // 纠错块部分信息
	RS_BLOCKINFO RS_BlockInfo2[4]; // 纠错块部分信息

} QR_VERSIONINFO;


/*二维码各个版本与各种信息量的关系*/        //匹配版本号的时候要用到
const int DataNum[41][4] = {
	{ 0 },
	{ 17,14,11,7 },
	{ 32,26,20,14 },
	{ 53,42,32,24 },
	{ 78,62,46,34 },
	{ 106,84,60,44 },
	{ 134,106,74,58 },
	{ 154,122,86,64 },
	{ 192,152,108,84 },
	{ 230,180,130,98 },
	{ 271,213,151,119 },
	{ 321,251,177,137 }
};
//不同版本和纠错级别下二维码相关信息
const QR_VERSIONINFO QR_VersonInfo[] = { { 0 }, // Ver.0
{ 1, // Ver.1
26,   19,   16,   13,    9,
0,   0,   0,   0,   0,   0,   0,
1,  26,  19,
1,  26,  16,
1,  26,  13,
1,  26,   9,
0,   0,   0,
0,   0,   0,
0,   0,   0,
0,   0,   0 },
{ 2, // Ver.2
44,   34,   28,   22,   16,
1,  18,   0,   0,   0,   0,   0,
1,  44,  34,
1,  44,  28,
1,  44,  22,
1,  44,  16,
0,   0,   0,
0,   0,   0,
0,   0,   0,
0,   0,   0 },
{ 3, // Ver.3
70,   55,   44,   34,   26,
1,  22,   0,   0,   0,   0,   0,
1,  70,  55,
1,  70,  44,
2,  35,  17,
2,  35,  13,
0,   0,   0,
0,   0,   0,
0,   0,   0,
0,   0,   0 },
{ 4, // Ver.4
100,   80,   64,   48,   36,
1,  26,   0,   0,   0,   0,   0,
1, 100,  80,
2,  50,  32,
2,  50,  24,
4,  25,   9,
0,   0,   0,
0,   0,   0,
0,   0,   0,
0,   0,   0 },
{ 5, // Ver.5
134,  108,   86,   62,   46,
1,  30,   0,   0,   0,   0,   0,
1, 134, 108,
2,  67,  43,
2,  33,  15,
2,  33,  11,
0,   0,   0,
0,   0,   0,
2,  34,  16,
2,  34,  12 },
{ 6, // Ver.6
172,  136,  108,   76,   60,
1,  34,   0,   0,   0,   0,   0,
2,  86,  68,
4,  43,  27,
4,  43,  19,
4,  43,  15,
0,   0,   0,
0,   0,   0,
0,   0,   0,
0,   0,   0 },
{ 7, // Ver.7
196,  156,  124,   88,   66,
2,  22,  38,   0,   0,   0,   0,
2,  98,  78,
4,  49,  31,
2,  32,  14,
4,  39,  13,
0,   0,   0,
0,   0,   0,
4,  33,  15,
1,  40,  14 },
{ 8, // Ver.8
242,  194,  154,  110,   86,
2,  24,  42,   0,   0,   0,   0,
2, 121,  97,
2,  60,  38,
4,  40,  18,
4,  40,  14,
0,   0,   0,
2,  61,  39,
2,  41,  19,
2,  41,  15 },
{ 9, // Ver.9
292,  232,  182,  132,  100,
2,  26,  46,   0,   0,   0,   0,
2, 146, 116,
3,  58,  36,
4,  36,  16,
4,  36,  12,
0,   0,   0,
2,  59,  37,
4,  37,  17,
4,  37,  13 }
};


