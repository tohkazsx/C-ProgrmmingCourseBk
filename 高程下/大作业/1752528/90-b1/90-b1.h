#pragma once
char Narray(char c, int game, char last, int & lasta, int & lastb);
void location(int a, int b, char * point, char W[12][12], int N[12][12]);                                 //��λ
void resetarray(char W[12][12], int N[12][12], int a, int b);                                            //��������ǰ��������
int End();                                                                                              //�жϽ���
char YNQ(int a, int b);                                                                                 //ѡ��
void compound(char W[12][12], int N[12][12], char xh, int a, int b, char choose, int a1, int b1, int & score, int & max);     //���һ�κϳ�
int ENTER();                                                                                            //��enter����
void newfillin(int max, int N[12][12], int a, int b);                                                   //���
void frame(int a, int b, char c);                                                                        //�ı䴰�ڴ�С
void border(int a, int b, char c, int & nx, int & ny);                                                  //��ӡαͼ�ο��
void blocks(int nx, int ny, int z);                                                                     //��ӡ����
void  cursor(int nx, int ny, int num);                                                                  //��ӡ���
char compound_cmd(char W[12][12], int N[12][12], int a, int b, char choose, int a1, int b1, int & score, int game);   //αͼ�����һ������
