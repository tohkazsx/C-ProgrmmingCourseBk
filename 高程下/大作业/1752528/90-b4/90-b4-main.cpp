/*朱世轩 计2 1752528*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string.h>
#include "90-b4.h"
#include "../common/cmd_console_tools.h"
using namespace std;

int main()
{
	char input[MAX_LENTH], correct = 0;
	int version = 0, level;                         //分别为版本号  纠错等级
	QREncode QRdata;

	cout << "请输入一串字符(至多100字节): ";
	cin.get(input, MAX_LENTH, '\n');
	while (correct != 'L' && correct != 'M' && correct != 'Q' && correct != 'H' && correct != '0')
	{

		cout << "请选择纠错级别[L(7%), M(%15), Q(25%) or H(30%)](若输入了汉字，请选择L纠错级别，否则可能无法识别): ";
		cin >> correct;
		if (correct <= 'z'&&correct >= 'a')
			correct -= 32;
	}
	int inputLength = int(strlen(input));
	//给纠错级别变量赋值
	if (correct == 'L')
	{
		level = 0;
	}
	if (correct == 'M')
	{
		level = 1;
	}
	if (correct == 'Q')
	{
		level = 2;
	}
	if (correct == 'H')
	{
		level = 3;
	}
	else
		level = 0;
	/***第一部分 获取数据编码***/
	char*UTF8input = G2U(input);
	inputLength = int(strlen(UTF8input));
	QRdata.m_nVersion = QRdata.GetVersion(level, UTF8input, inputLength); //给结构体中版本号赋值
	QRdata.m_nLevel = level;                                             //给结构体中纠错级别赋值
	QRdata.m_ncDataCodeWordBit = inputLength;                           //给结构体中输入数据长度赋值
	strcpy(QRdata.m_byDatepre, UTF8input);                             //给结构体中待处理字符串赋值
	QRdata.GetCountCode(UTF8input);                                   //取得编码信息
	StrToBinary(UTF8input, QRdata.m_byWordDatapre);                  //获得最初的二进制数据串
	QRdata.GetEncodeInfo();                                         //加入编码信息 处理后的数据都保存在m_byWordData
	QRdata.InsertBit();                                            //补位         处理后的数据都保存在m_byWordData中
    QRdata.m_ncAllCodeWord = QR_VersonInfo[QRdata.m_nVersion].ncAllCodeWord;                  //写入必要信息
	QRdata.ncDataCodeWord = QR_VersonInfo[QRdata.m_nVersion].ncDataCodeWord[QRdata.m_nLevel];
  /***第二部分 获取纠错（RS）编码***/
	QRdata.prt_binary();                                        //将二进制数据串转成十进制
	for (int i = 0; i < QR_VersonInfo[QRdata.m_nVersion].ncDataCodeWord[QRdata.m_nLevel]; i++) //output test 
	{
		cout << int(QRdata.m_byDataCodeWord[i]) << " ";
	}
	cout << endl;
	//调用多项式计算函数 生成纠错码字赋值给data.m_byRSWork
	strcpy((char*)QRdata.m_byRSWork, (char*)(RS_Code(QRdata.m_ncAllCodeWord, QR_VersonInfo[QRdata.m_nVersion].ncDataCodeWord[QRdata.m_nLevel], QRdata.m_byDataCodeWord)));
	cout << "纠错码：";                                    //output test 按十进制打印出纠错码                                         
	for (int i = 0; i < QRdata.m_ncAllCodeWord - QR_VersonInfo[QRdata.m_nVersion].ncDataCodeWord[QRdata.m_nLevel]; i++)
	{
		cout << int(QRdata.m_byRSWork[i]) << " ";
	}
	cout << endl;
	QRdata.BlockstoCode();                              //对数据与纠错码进行分块
	cout << "所有数据数组";                               //output test   按十进制打印出所有数据数组  
	for (int i = 0; i < QRdata.m_ncAllCodeWord; i++)
	{
		cout << int(QRdata.m_byAllCodeWord[i]) << " ";
	}
	cout << endl;

	/***第三部分 填充 掩模***/
	  //prt((char*)data.m_byAllCodeWord, data.m_byAllData);       //将所有数据的十进制码字串转为二进制串
	QRdata.m_nSymbleSize = QRdata.m_nVersion * 4 + 17;           // 通过版本号计算图形边长
	//cout << QRdata.m_nSymbleSize;                             //output test
	QRdata.FillMartrixFunction();                             //将定位信息和数据等填充进入矩阵
	QRdata.FillMartrixCode();
	//printMartrix(QRdata);
	//开始掩模
	QRdata.Masking();               //使用000掩模图形进行掩模
    QRdata.SetFormatInfoPattern(); // 设置格式信息
	QRdata.FilltheMatrix();       //将最终结果写入矩阵
	
	/***第四部分 打印二维码***/
	QRdata.printQR();

}