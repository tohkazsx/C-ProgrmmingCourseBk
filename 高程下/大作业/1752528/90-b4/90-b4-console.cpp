#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include<iostream>
#include <atlconv.h>
#include <stdio.h>
#include <conio.h>
#include<iomanip>
#include "90-b4.h"
#include "../common/cmd_console_tools.h"
using namespace std;

//������ ��ӡ������
void printMartrix(QREncode data)
{
	for (int i = 0; i < data.m_nSymbleSize; i++)
	{
		for (int j = 0; j < data.m_nSymbleSize; j++)
			cout << setw(3)<<int(data.m_byModuleData[i][j])<<" ";
		cout << endl;
	}
}

//���س���������
static int ENTER()                                                        
{
	char next;
	next = _getch();
	if (next == '\r')
		return 0;
	else
		return 1;
}
//��ӡ��ά��ͼ��
int QREncode::printQR()
{
	setfontsize("����", QR_SIZE);
		setconsoleborder(100, 80);
	
	system("cls");
	for (int i = 0; i < WIDETH_OF_QR; i++)
	{
		setcolor(COLOR_WHITE, COLOR_BLACK);
		for (int i = 0; i < m_nSymbleSize + WIDETH_OF_QR*2; i++)
			cout << "  ";                       //��ӡ�ϱ߿�
		cout << endl;
		setcolor(COLOR_BLACK, COLOR_WHITE);
	}
	for (int i = 0; i < m_nSymbleSize; i++)
	{
		setcolor(COLOR_WHITE, COLOR_WHITE);
		for (int i = 0; i < WIDETH_OF_QR; i++)
			cout << "  ";                      //��ӡ��߿�

		for (int j = 0; j < m_nSymbleSize; j++)
		{
			if (m_byModuleData[i][j] == 1)        //��ӡ����
			{
				setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << "  ";
				setcolor(COLOR_BLACK, COLOR_WHITE);
			}
			else if(m_byModuleData[i][j] == 0)
			{
				setcolor(COLOR_HWHITE, COLOR_BLACK);
				cout << "  ";
				setcolor(COLOR_BLACK, COLOR_WHITE);
			}
		}
		setcolor(COLOR_WHITE, COLOR_BLACK);
		for (int i = 0; i < WIDETH_OF_QR; i++)
			cout << "  ";             //��ӡ�ұ߿�        

		setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << endl;
	}
	for (int i = 0; i < WIDETH_OF_QR; i++)
	{
		setcolor(COLOR_WHITE, COLOR_BLACK);
		for (int i = 0; i < m_nSymbleSize + WIDETH_OF_QR*2; i++)
			cout << "  ";                     //��ӡ�±߿�

		cout << endl;
		setcolor(COLOR_BLACK, COLOR_WHITE);
	}
	setcolor(COLOR_BLACK, COLOR_HYELLOW);
	cout << "���ɳɹ������س����˳�";
	while (1)
	{
		if (!ENTER())
			break;
	}
	return 0;
}

