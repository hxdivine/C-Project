#include<stdio.h>
#include<graphics.h>
#include<conio.h> //����ͷ�ļ�
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<string.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

/*
	ͼƬ����
*/

/*����ͼƬ��Դ*/
void loadResource();
/*����ͼƬ������ͼƬ*/
void putAnddesImage(int x1, int y1, int x2, int y2, IMAGE* img);

/*

	�������ﶯ��
	
*/
/*�ƶ�*/
void role_move(int frameNum);
/*����*/
void role_roll(int frameNum);
/*��*/
void role_jump();
/*ǰ��*/
void role_forward(int frameNum);
/*����*/
void role_back(int frameNum);
/*������Ӧ*/
void keyDown();

/*
	���̴߳���
*/

/*��������ϰ���*/
DWORD WINAPI barrier_rand(LPVOID p);
/*��������ƶ�*/
DWORD WINAPI could_rand(LPVOID p);
/*�Ƿ�Ӵ��ϰ���*/
DWORD WINAPI isOver(LPVOID p);
/*������������*/
DWORD WINAPI Bgm(LPVOID p);
/*������Ϸ������������*/
DWORD WINAPI Bgm_over(LPVOID p);

/*
	��Ϸ��ʼ�������������¿�ʼ	
*/

/*��ʼ����Ϸ����*/
void initGame();
/*������ҳ��ť�Լ�ͼʾ��Ϣ*/
void loadButton();
/*��ʼ��Ϸ*/
void startGame();
/*���¿�ʼ��Ϸ*/
void restartGame();

/*
	���� �ػ�����
*/

/*�˳���Ϸ����*/
void exitModel();
/*������Ϸ����*/
void startModel();
/*�����Բ*/
void setColor_cirl(int x, int y);
/*�������*/
void setColor_line(int x1, int y1, int x2, int y2);
/*�ػ�������ʾ����*/
void exitModel_font(int x, int y, int size);
/*�ػ���������*/
void exitModel_line();

/*

	����
*/

/*��ȡ��߷�*/
int getHeightScore(struct Hscore* hscore);
/*��¼��߷�*/
void setHeightScore(struct Hscore* hscore);
/*��ӡ����*/
void printScore(struct Hscore* hscore);

/*

	ȫ�ֱ���

*/

extern int flag; //�Ƿ������Ϸ 1 ����

extern int speed;  //���ٶ�

extern int score;  //����

const char fileName[] = "score.txt";