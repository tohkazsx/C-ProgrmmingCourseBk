/*������ ��2 1752528*/
#pragma once
#include <Windows.h>
#include "../common/cmd_console_tools.h"

#define MAX_MODULESIZE	  177 // ģ�������ֵ177*177
#define MAX_ALLCODEWORD	 3706 // �����������ֵ3706���汾40��
#define MAX_DATACODEWORD 2956 // �����������ֵ���汾40-L��
#define MAX_CODEBLOCK	  153 // ģ���������������ֵ������RS���֣�
#define COUNTCODE  10          //�ַ�������λ��
#define MODECODE   5         //ģʽָʾ��λ��

#define QR_SIZE	10        // ���ɶ�ά����ֺŴ�С

// ������
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

#define OK 1
#define FAILE -1
#define WIDETH_OF_QR 2

const int MAX_LENTH = 100;

void StrToBinary(char c[], char binary[]);                       //ʮ���ƴ�תΪ������
unsigned char* RS_Code(int n, int k, unsigned char *data_codewords);  //��ȡRS����
char* G2U(const char* gb2312);                                 //ת��������utf8


struct QREncode                          //����ṹ���Ŷ�ά�������Ϣ
{
public:
	int m_nLevel;		// ����ȼ�
	int m_nVersion;		// �汾
	int m_nMaskingNo;	// ����ȼ�

	int m_nSymbleSize;                                    //ͼ�δ�С
	BYTE m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; // ������Ҫ���ľ���

	int m_ncDataCodeWordBit; //�������ݳ���
	//�����Ƕ����ƴ��������
	char m_byWordDatapre[MAX_DATACODEWORD * 8];    //������01  ��������ת���������
	char m_byWordData[MAX_DATACODEWORD * 8];    //������01  �������ּ���ģʽ�� ��������Ϣ�������
	char m_byRSData[MAX_DATACODEWORD * 8];    //������01  ��������ת���������
	char m_byAllData[MAX_ALLCODEWORD * 8];     //������01  �������ݣ���������+�����룩ת��������
	char m_ModeCode[MODECODE];               //ģʽָʾ��
	char m_CountCode[COUNTCODE];               //�ַ�������



	//������ԭ���������
	char m_byDatepre[MAX_DATACODEWORD];        //ԭʼתutf8������ݴ�
	BYTE m_byDataCodeWord[MAX_DATACODEWORD]; //�����������飨ԭ����
	int m_ncDataBlock;                      //���ݿ���

	//�����Ǵ�������Ϣ�ı���
	int m_ncAllCodeWord; //���б������ݳ���
	BYTE m_byAllCodeWord[MAX_ALLCODEWORD]; //������������
	BYTE m_byRSWork[MAX_CODEBLOCK]; // RS����������
	int ncDataCodeWord;//���ݷֿ鳤��

	//��ȡ��������
	/**************************************************************************************/
	int GetVersion(int nLevel, const char* lpsSource, int ncLength);//ͨ�������ַ����Ⱥ�ѡ��ľ���ȼ� ȡ�ñ���汾��Ϣ levelΪ����ȼ�  lpsSourceΪ�����ַ��� ncLengthΪ�ַ�����
	void GetCountCode(const char*data);        //��ȡ�ַ�������
	void GetEncodeInfo();                     //���ϱ�����Ϣ
	void InsertBit();                        //��λ
	void prt_binary();               //�������ƴ�ת��ʮ���ƴ�
	//void prt_dec();                  //��ʮ���ƴ�ת�ɶ����ƴ�
	//void GetRSCodeWord(LPBYTE lpbyRSWork, int ncDataCodeWord, int ncRSCodeWord);//������
	void BlockstoCode();                           //�����ݺ;�����ֿ鲢�����m_byAllCodeWord������
	/**************************************************************************************/

	//������
	/**************************************************************************************/
	void FillMartrixCode();//������Ϣ
	void FillMartrixFunction();//����ģ�� ����λ��Ϣ��������Ϣ��������� ����������ĺ�����
	void SetFinderPattern(int x, int y);//���Ѱ��ͼ��
	void SetAlignmentPattern(int x, int y);//���У��ͼ��      
	void SetVersionPattern();//�汾��Ϣ
	/**************************************************************************************/

	//��ģ
	/**************************************************************************************/
	void Masking();//������ģͼ��
	void SetFormatInfoPattern();
	void FilltheMatrix();  //�����ս��д�����
	/**************************************************************************************/

	//��ӡ��ά��
	/**************************************************************************************/
	int printQR(); //��ӡ��ά�뺯�� 
	/**************************************************************************************/
};

void printMartrix(QREncode data);                               //��ӡ�����ݾ��� ������
//RS�����ݽṹ
typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock;		// �������
	int ncAllCodeWord;	// ����������
	int ncDataCodeWord;	// ������������������-RS��������

} RS_BLOCKINFO;


//QRcode�汾�����Ϣ
typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   // �汾��1-40
	int ncAllCodeWord; // ��������
	int ncDataCodeWord[4];	// �������֣�������-RS���֣�

	int ncAlignPoint;	// У������
	int nAlignPoint[6];	// У��ͼ����������

	RS_BLOCKINFO RS_BlockInfo1[4]; // ����鲿����Ϣ
	RS_BLOCKINFO RS_BlockInfo2[4]; // ����鲿����Ϣ

} QR_VERSIONINFO;


/*��ά������汾�������Ϣ���Ĺ�ϵ*/        //ƥ��汾�ŵ�ʱ��Ҫ�õ�
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
//��ͬ�汾�;������¶�ά�������Ϣ
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


