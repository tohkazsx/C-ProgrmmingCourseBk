/* 1752528 计2 朱世轩 */
#pragma once
#define YL 20
#define XL 17
#define ar 12
char cd(char menu[12][60], int game);                                                           //菜单函数
void CIN(int*s, int a, int b);
void search(int x, char W[ar][ar], int a, int b);
void search_dg(int x, char W[ar][ar], int a, int b);
void highlight(char W[ar][ar], int N[ar][ar], int a, int b, int game);
void printarray(char W[ar][ar], int N[ar][ar], int a, int b, int game, const int mode);
void location(int a, int b, char * point, char W[ar][ar], int N[ar][ar]);
void free_border(int a, int b, int & nx, int & ny, const int mode, const int style);
void free_blocks(int nx, int ny, int z, int game);
void free_cursor(int nx, int ny, int num, int game);
char gameover(int row, int col, int Narray[ar][ar], char Warray[ar][ar], int game);
void blocksmove(int N[ar][ar], char W[ar][ar], int a, int b, char c, int nx, int ny, int & m, int & n, int game, int mode);
void fall(int map[YL][XL], int blocks[5][3], int game, int & row, int & col, int & endflag);                              //数字方块下落
void turn_right(int map[YL][XL], int blocks[5][3], int game, int & row, int & col);                          //数字方块右移
void turn_left(int map[YL][XL], int blocks[5][3], int game, int & row, int & col);                            //数字方块左移
int spin(int map[YL][XL], int blocks[5][3], int game, int & row, int & col, int & spinflag);                      //数字方块旋转
void mapfall(int map[YL][XL], int & row, int & col, int nr, int game);                                       //消除后下落
void tips(int a, int b, int num, int score, const int length, const int wide, const int mode);