#include<stdio.h>
#include<graphics.h>
#include<conio.h> //按键头文件
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<string.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

/*
	图片加载
*/

/*加载图片资源*/
void loadResource();
/*放置图片和销毁图片*/
void putAnddesImage(int x1, int y1, int x2, int y2, IMAGE* img);

/*

	描述人物动作
	
*/
/*移动*/
void role_move(int frameNum);
/*翻滚*/
void role_roll(int frameNum);
/*跳*/
void role_jump();
/*前进*/
void role_forward(int frameNum);
/*后退*/
void role_back(int frameNum);
/*按键响应*/
void keyDown();

/*
	多线程处理
*/

/*随机出现障碍物*/
DWORD WINAPI barrier_rand(LPVOID p);
/*随机出现云朵*/
DWORD WINAPI could_rand(LPVOID p);
/*是否接触障碍物*/
DWORD WINAPI isOver(LPVOID p);
/*创建背景音乐*/
DWORD WINAPI Bgm(LPVOID p);
/*创建游戏结束背景音乐*/
DWORD WINAPI Bgm_over(LPVOID p);

/*
	游戏初始化，启动，重新开始	
*/

/*初始化游戏界面*/
void initGame();
/*加载首页按钮以及图示信息*/
void loadButton();
/*开始游戏*/
void startGame();
/*重新开始游戏*/
void restartGame();

/*
	开机 关机动画
*/

/*退出游戏动画*/
void exitModel();
/*开机游戏动画*/
void startModel();
/*随机画圆*/
void setColor_cirl(int x, int y);
/*随机画线*/
void setColor_line(int x1, int y1, int x2, int y2);
/*关机动画显示文字*/
void exitModel_font(int x, int y, int size);
/*关机动画画线*/
void exitModel_line();

/*

	分数
*/

/*获取最高分*/
int getHeightScore(struct Hscore* hscore);
/*记录最高分*/
void setHeightScore(struct Hscore* hscore);
/*打印分数*/
void printScore(struct Hscore* hscore);

/*

	全局变量

*/

extern int flag; //是否结束游戏 1 结束

extern int speed;  //加速度

extern int score;  //分数

const char fileName[] = "score.txt";