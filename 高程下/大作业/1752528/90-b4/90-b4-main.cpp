/*������ ��2 1752528*/
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
	int version = 0, level;                         //�ֱ�Ϊ�汾��  ����ȼ�
	QREncode QRdata;

	cout << "������һ���ַ�(����100�ֽ�): ";
	cin.get(input, MAX_LENTH, '\n');
	while (correct != 'L' && correct != 'M' && correct != 'Q' && correct != 'H' && correct != '0')
	{

		cout << "��ѡ�������[L(7%), M(%15), Q(25%) or H(30%)](�������˺��֣���ѡ��L�����𣬷�������޷�ʶ��): ";
		cin >> correct;
		if (correct <= 'z'&&correct >= 'a')
			correct -= 32;
	}
	int inputLength = int(strlen(input));
	//�������������ֵ
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
	/***��һ���� ��ȡ���ݱ���***/
	char*UTF8input = G2U(input);
	inputLength = int(strlen(UTF8input));
	QRdata.m_nVersion = QRdata.GetVersion(level, UTF8input, inputLength); //���ṹ���а汾�Ÿ�ֵ
	QRdata.m_nLevel = level;                                             //���ṹ���о�����ֵ
	QRdata.m_ncDataCodeWordBit = inputLength;                           //���ṹ�����������ݳ��ȸ�ֵ
	strcpy(QRdata.m_byDatepre, UTF8input);                             //���ṹ���д������ַ�����ֵ
	QRdata.GetCountCode(UTF8input);                                   //ȡ�ñ�����Ϣ
	StrToBinary(UTF8input, QRdata.m_byWordDatapre);                  //�������Ķ��������ݴ�
	QRdata.GetEncodeInfo();                                         //���������Ϣ ���������ݶ�������m_byWordData
	QRdata.InsertBit();                                            //��λ         ���������ݶ�������m_byWordData��
    QRdata.m_ncAllCodeWord = QR_VersonInfo[QRdata.m_nVersion].ncAllCodeWord;                  //д���Ҫ��Ϣ
	QRdata.ncDataCodeWord = QR_VersonInfo[QRdata.m_nVersion].ncDataCodeWord[QRdata.m_nLevel];
  /***�ڶ����� ��ȡ����RS������***/
	QRdata.prt_binary();                                        //�����������ݴ�ת��ʮ����
	for (int i = 0; i < QR_VersonInfo[QRdata.m_nVersion].ncDataCodeWord[QRdata.m_nLevel]; i++) //output test 
	{
		cout << int(QRdata.m_byDataCodeWord[i]) << " ";
	}
	cout << endl;
	//���ö���ʽ���㺯�� ���ɾ������ָ�ֵ��data.m_byRSWork
	strcpy((char*)QRdata.m_byRSWork, (char*)(RS_Code(QRdata.m_ncAllCodeWord, QR_VersonInfo[QRdata.m_nVersion].ncDataCodeWord[QRdata.m_nLevel], QRdata.m_byDataCodeWord)));
	cout << "�����룺";                                    //output test ��ʮ���ƴ�ӡ��������                                         
	for (int i = 0; i < QRdata.m_ncAllCodeWord - QR_VersonInfo[QRdata.m_nVersion].ncDataCodeWord[QRdata.m_nLevel]; i++)
	{
		cout << int(QRdata.m_byRSWork[i]) << " ";
	}
	cout << endl;
	QRdata.BlockstoCode();                              //���������������зֿ�
	cout << "������������";                               //output test   ��ʮ���ƴ�ӡ��������������  
	for (int i = 0; i < QRdata.m_ncAllCodeWord; i++)
	{
		cout << int(QRdata.m_byAllCodeWord[i]) << " ";
	}
	cout << endl;

	/***�������� ��� ��ģ***/
	  //prt((char*)data.m_byAllCodeWord, data.m_byAllData);       //���������ݵ�ʮ�������ִ�תΪ�����ƴ�
	QRdata.m_nSymbleSize = QRdata.m_nVersion * 4 + 17;           // ͨ���汾�ż���ͼ�α߳�
	//cout << QRdata.m_nSymbleSize;                             //output test
	QRdata.FillMartrixFunction();                             //����λ��Ϣ�����ݵ����������
	QRdata.FillMartrixCode();
	//printMartrix(QRdata);
	//��ʼ��ģ
	QRdata.Masking();               //ʹ��000��ģͼ�ν�����ģ
    QRdata.SetFormatInfoPattern(); // ���ø�ʽ��Ϣ
	QRdata.FilltheMatrix();       //�����ս��д�����
	
	/***���Ĳ��� ��ӡ��ά��***/
	QRdata.printQR();

}