/*������ ��2 1752528*/
#pragma once
void Narray(char c,int game,const char *filename);
void CIN(int*, int, int);
void resetarray(char W[12][12], int N[12][12], int a, int b);                                            //��������ǰ��������
int End();                                                                                              //�жϽ���
char YNQ(int a, int b);                                                                                 //ѡ��
void compound(char W[12][12], int N[12][12],char xh ,int a, int b, char choose, int a1, int b1, int & score, int goal, int & max);     //���һ�κϳ�
int ENTER();                                                                                            //��enter����
void newfillin(int max, int N[12][12], int a, int b);                                                   //���
void frame(int a, int b,char c);                                                                        //�ı䴰�ڴ�С
void border(int a, int b, char c, int & nx, int & ny);                                                  //��ӡαͼ�ο��
void blocks(int nx, int ny, int z);                                                                     //��ӡ����
void blocksmove(int N[12][12], char W[12][12], int a, int b, char c, int &nx, int &ny, int & m, int & n);                   //����ƶ� ѡ��
void  cursor(int nx, int ny, int num);                                                                  //��ӡ���
char compound_cmd(char W[12][12], int N[12][12], int a, int b, char choose, int a1, int b1, int & score, int goal, int & max);  //αͼ�����һ�κϳ�