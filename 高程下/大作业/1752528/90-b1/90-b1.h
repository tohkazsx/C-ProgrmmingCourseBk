#pragma once
char Narray(char c, int game, char last, int & lasta, int & lastb);
void location(int a, int b, char * point, char W[12][12], int N[12][12]);                                 //定位
void resetarray(char W[12][12], int N[12][12], int a, int b);                                            //重新输入前重置数组
int End();                                                                                              //判断结束
char YNQ(int a, int b);                                                                                 //选择
void compound(char W[12][12], int N[12][12], char xh, int a, int b, char choose, int a1, int b1, int & score, int & max);     //完成一次合成
int ENTER();                                                                                            //按enter继续
void newfillin(int max, int N[12][12], int a, int b);                                                   //填充
void frame(int a, int b, char c);                                                                        //改变窗口大小
void border(int a, int b, char c, int & nx, int & ny);                                                  //打印伪图形框架
void blocks(int nx, int ny, int z);                                                                     //打印方块
void  cursor(int nx, int ny, int num);                                                                  //打印光标
char compound_cmd(char W[12][12], int N[12][12], int a, int b, char choose, int a1, int b1, int & score, int game);   //伪图形完成一次消除
