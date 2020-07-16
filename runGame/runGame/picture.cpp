#include"head.h"

int flag;

int speed;

int score;
//��߷���
struct Hscore {
	int HeightScore;
	char name[30];
};
//���������״̬
struct FirePer {
	int x;
	int y;
	int stat; //1 �� 0 �� -1 ��
}fireper;
//�ϰ�������
struct Barrier {
	int x;
	int y;

}bars;

/*
	���ﶯ��ͼƬ
*/
IMAGE roll[8];
IMAGE move[8];
IMAGE jump;

/*
	�ϰ�����ƶ�ͼƬ
*/
IMAGE barrier[5];
IMAGE could[2];

/*
	��Ϸ���� �� ���¿�ʼͼƬ
*/
IMAGE run_over[2];
IMAGE restart[2];

/*
	ͼƬ����
*/
/*����ͼƬ��Դ*/
void loadResource() {
	loadimage(&jump, ".\\img\\jump.png", 180, 230);
	loadimage(could, ".\\img\\could_1.png", 171, 104);
	loadimage(could + 1, ".\\img\\could_2.png", 122, 89);

	loadimage(run_over, ".\\img\\run_over.png", 400, 105);
	loadimage(run_over + 1, ".\\img\\run_over1.png", 400, 105);

	loadimage(restart, ".\\img\\restart.png", 423, 90);
	loadimage(restart + 1, ".\\img\\restart_1.png", 423, 90);
	for (int i = 1; i <= 8; i++) {
		char fileName[50] = "";
		sprintf_s(fileName, ".\\img\\gun_%d.png", i);
		loadimage(roll + i - 1, fileName, 130, 113);
		sprintf_s(fileName, ".\\img\\move_%d.png", i);
		loadimage(move + i - 1, fileName, 180, 230);
		if (i < 5) {
			sprintf_s(fileName, ".\\img\\barrier_%d.png", i);
			loadimage(barrier + i - 1, fileName, 50, 50);
		}
	}
	loadimage(barrier + 4, ".\\img\\barrier_5.png", 90, 39);
}
/*����ͼƬ������ͼƬ*/
void putAnddesImage(int x1, int y1, int x2, int y2, IMAGE* img) {

	solidrectangle(x1, y1, x2, y2);

	putimage(x1, y1, img);
	Sleep(50);

	clearrectangle(x1, y1, x2, y2);
}

/*

	�������ﶯ��

*/

/*�ƶ�*/
void role_move(int frameNum) {
	fireper.stat = 0;
	int i = 0;
	while (i < frameNum) {
		//cleardevice();
	//	solidrectangle(fireper.x, fireper.y, fireper.x + 180, 442);
		putimage(fireper.x, fireper.y, move + i);
		//ʱ����0.05ms
		Sleep(50);
		i++;
	}
	if (fireper.x > 50) {
		//�Զ�������
		fireper.x -= 10;
	}
}
/*����*/
void role_roll(int frameNum) {
	fireper.stat = -1;
	int i = 0;
	clearrectangle(fireper.x, fireper.y, fireper.x + 180, 442);
	//�������¹� y��������
	fireper.y += 117;
	while (i < frameNum) {
		putAnddesImage(fireper.x + i * 5, fireper.y, fireper.x + 130 + i * 5, 442, roll + i);
		i++;
	}
	fireper.y -= 117;
	//��ǰ�ƶ�
	fireper.x += 35;
}
/*��*/
void role_jump() {
	fireper.stat = 1;
	clearrectangle(fireper.x, fireper.y, fireper.x + 180, 442);
	//	rectangle(50,34,265,262);
	for (int i = 1; i < 10; i++) {
		//������ x  ���� ���� y��С
		putAnddesImage(fireper.x + i * 12, fireper.y - i * 12, fireper.x + 180, 442 - i * 12, &jump);
	}
	if (fireper.x > 950) {
		fireper.x = 950;
	}
	else {
		fireper.x += 120;
	}
	fireper.y -= 120;
	for (int i = 1; i < 10; i++) {
		//���µ� x�������� y����
		putAnddesImage(fireper.x + i * 12, fireper.y + i * 12, fireper.x + 180, 322 + i * 12, &jump);

	}
	//���ܳ������洰��
	if (fireper.x > 950) {
		fireper.x = 950;
	}
	else {
		fireper.x += 120;
	}
	fireper.y += 120;
}
/*ǰ��*/
void role_forward(int frameNum) {
	//����״̬
	fireper.stat = 0;
	int i = 0, f = 0;
	if (fireper.x == 800) {
		return;
	}
	while (i < frameNum) {
		//���ܳ������ֵ
		if (fireper.x + i * 10 > 800) {
			f = 1;
			return;
		}
		//x��������
		putAnddesImage(fireper.x + i * 10, fireper.y, fireper.x + 180 + i * 10, 422, move + i);
		i++;
	}
	if (f) {
		fireper.x = 800;
	}
	else {
		fireper.x += 70;
	}
}
/*����*/
void role_back(int frameNum) {
	fireper.stat = 0;
	int i = 0, f = 0;
	if (fireper.x == 50) {
		return;
	}
	while (i < frameNum) {
		//���ܵ�����С����
		if (fireper.x - i * 10 < 60) {
			f = 1;
			return;
		}
		//x�����С 10
		putAnddesImage(fireper.x - i * 10, fireper.y, fireper.x + 180 - i * 10, 422, move + i);
		i++;
	}
	if (f) {
		fireper.x = 50;
	}
	else {
		fireper.x -= 70;
	}
}
/*������Ӧ*/
void keyDown() {
	char key = _getch();
	switch (key) {
	case 's'://����
	case 'S':
		role_roll(8); break;
	case ' '://��Ծ
		role_jump(); break;
	case 'a'://����
	case 'A':
		role_back(8); break;
	case 'd'://ǰ��
	case 'D':
		role_forward(8); break;
	default:
		break;
	}
}

/*
	���̴߳���
*/

/*��������ϰ���*/
DWORD WINAPI barrier_rand(LPVOID p) {
	srand((unsigned)time(NULL));
	//int frameNum = 4;
	int i = 0;
	
	while (1) {
		int temp = speed;  //����ٶȵ�ֵ
		//int frameNum = 4;
		int frameNum = rand() % 5;
		int height = 392;
		if (frameNum == 4) {
			height -= 142;
		}
		if (i % 100 == 0) {
			//�����ϰ���  ��СΪ90 * 39
			if (frameNum == 4) {
				BeginBatchDraw();//��ͼ��ʼ
				for (int i = 0; i < 1080 / temp; i++) {
					//�����δ���ϰ���
					rectangle(1080 - temp * i, height, 1170 - temp * i, height + 39);
					bars.x = 1080 - temp * i;
					bars.y = height;
					putimage(1080 - temp * i, height, barrier + frameNum);
					Sleep(25);
					if (isOver(NULL)) { //��Ϸ�����ж�
						break;
					}
					FlushBatchDraw(); //��������
					//�������α���
					clearrectangle(1080 - temp * i, height, 1170 - temp * i, height + 39);
				}
				EndBatchDraw(); //��ͼ����
			}
			else {//�����ϰ��� 4�� ��СΪ50*50
				BeginBatchDraw();
				for (int i = 0; i < 1080 / temp; i++) {
					rectangle(1080 - temp * i, height, 1130 - temp * i, height + 50);
					bars.x = 1080 - temp * i;
					bars.y = height;
					putimage(1080 - temp * i, height, barrier + frameNum);
					Sleep(25);
					if (isOver(NULL)) { //��Ϸ�����ж�
						break;
					}
					FlushBatchDraw();
					clearrectangle(1080 - temp * i, height, 1130 - temp * i, height + 50);
				}
				EndBatchDraw();
			}
		}
		if (flag) {
			break;
		}

		i++;
	}

	return 0;
}
/*��������ƶ�*/
DWORD WINAPI could_rand(LPVOID p) {
	srand((unsigned)time(NULL));
	int i = 0;
	while (1) {
		int frameNum = rand() % 2;
		int height = 104;
		if (frameNum == 1) {
			height = 89;
		}//ÿ��1000����һ���ƶ�
		if (i % 1000 == 0) {
				//BeginBatchDraw();
			for (int i = 0; i < 520; i++) {
				rectangle(520 - i, 21, 691 - i, height + 21);
				putimage(520 - i, 21, could + frameNum);
				Sleep(100);
				if (isOver(NULL)) {
					break;
				}
					//FlushBatchDraw();�޷���������
				clearrectangle(520 - i, 21, 691 - i, height + 21);

			}
			//	EndBatchDraw();
		}
		//��Ϸ�����ж�
		if (flag) {
			break;
		}
		i++;

	}
	return 0;
}
/*�Ƿ�Ӵ��ϰ���*/
DWORD WINAPI isOver(LPVOID p) {
	if (bars.y < 392) {
		if ((fireper.x + 170 > bars.x && fireper.x + 170 < bars.x + 90)) {
			if ((fireper.stat == 1) && (bars.y > fireper.y)) {
				flag = 1;
				
			}
			else if ((fireper.stat == 0) && (bars.y > fireper.y)) {
				flag = 1;
				
			}
		}
		else if ((fireper.x + 10 > bars.x && fireper.x + 10 < bars.x + 90) && (bars.y > fireper.y)) {
			if ((fireper.stat == 1) && (bars.y > fireper.y)) {
				flag = 1;
				
			}
			else if ((fireper.stat == 0) && (bars.y > fireper.y)) {
				flag = 1;
				
			}
		}
	}
	else {
		if ((fireper.x + 170 > bars.x && fireper.x + 170 < bars.x + 50) && (fireper.y + 230 > bars.y)) {
			flag = 1;
			
		}
		else if ((fireper.x + 10 > bars.x && fireper.x + 10 < bars.x + 50) && (fireper.y + 230 > bars.y)) {
			flag = 1;
			
		}
	}
	if (flag) {
		CreateThread(NULL, NULL, Bgm_over, NULL, NULL, NULL);
		return 1;
	}
	return 0;
}
/*�����������ֵ��߳�*/
DWORD WINAPI Bgm(LPVOID p)
{
	mciSendStringA("open .\\bgm\\bgm.mp3 ", 0, 0, 0);
	mciSendStringA("play .\\bgm\\bgm.mp3 wait", 0, 0, 0);
	mciSendStringA("close .\\bgm\\bgm.mp3", 0, 0, 0);

	Sleep(50000);

	mciSendStringA("open .\\bgm\\1.mp3 alias MP3", 0, 0, 0);
	mciSendStringA("play MP3 repeat", 0, 0, 0);
	mciSendStringA("close .\\bgm\\1.mp3", 0, 0, 0);
	return 0;
}
/*������Ϸ������������*/
DWORD WINAPI Bgm_over(LPVOID p) {
	mciSendStringA("open .\\bgm\\over.wav", 0, 0, 0);
	mciSendStringA("play .\\bgm\\over.wav wait", 0, 0, 0);
	mciSendStringA("close .\\bgm\\over.wav", 0, 0, 0);
	return 0;
}

/*
	��Ϸ��ʼ�������������¿�ʼ
*/

/*��ʼ����Ϸ����*/
void initGame() {
	HWND  hwnd = initgraph(1080, 583, NULL);
	SetWindowTextA(hwnd, "������");
	//���ر�������
	HANDLE Bgmhwnd = CreateThread(NULL, NULL, Bgm, NULL, NULL, NULL);
	CloseHandle(Bgmhwnd);setbkcolor(WHITE);
	cleardevice();//�ñ���ɫ�������Ļ
	startModel();
	
	
	/*��ʾͼƬ*/
	loadButton();
	loadResource();
	/*��ȡ�����Ϣ*/
	MOUSEMSG m;
	while (TRUE) {

		if (MouseHit()) {
			//��ȡ�����Ϣ
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				//������Ϸ
				if (m.x > 534 && m.x < 801 && m.y > 204 && m.y < 277)
				{
					startGame();
					loadButton();
				}
				//�˳���Ϸ
				else if ((m.x > 534 && m.x < 801) && (m.y > 326 && m.y < 396))
				{
					exitModel();
					break;
				}
			}
			
		}
		if (_kbhit()) {
			//��ȡ������Ӧ
			char ch = _getch();
				if (ch == 'j')//��ʼ��Ϸ
				{
					startGame();
					loadButton();
				}
				else if (ch == 'q') //������Ϸ
				{
					exitModel();
					break;
				}


		}
	}

	closegraph();
}
/*������ҳ��ť�Լ�ͼʾ��Ϣ*/
void loadButton() {

	IMAGE img;
	/*����ͼƬ*/
	loadimage(&img, "img\\start_bg.png");
	putimage(0, 0, &img);


	setlinecolor(RGB(0, 162, 232));
	setlinestyle(PS_SOLID, 5, 0, 0);
	settextcolor(RGB(0, 162, 232));
	settextstyle(28, 0, NULL);
	setfillcolor(WHITE);
	fillrectangle(534, 326, 801, 396);

	outtextxy(620, 355, "�˳���q��");


	settextstyle(28, 0, NULL);
	fillrectangle(350, 440,1008 , 542);
	outtextxy(463, 483, "ǰ����d�� ������s�� ���ˣ�a�� ��Ծ��space��");

	setlinecolor(WHITE);
}
/*��ʼ��Ϸ*/
void startGame() {
	flag = 0;
	speed = 2;
	score = 0;
	IMAGE img,img1;
	loadimage(&img, ".\\img\\run_bg.png");
	loadimage(&img1, ".\\img\\run_bg1.png");

	putimage(0, 0, &img);

	int i = 1;
	//	barrier_rand();
	struct Hscore* hscore = (struct Hscore*)malloc(sizeof(struct Hscore));

	if (!getHeightScore(hscore)) {
		hscore->HeightScore = 0;
		//strcpy_s(hscore->name,"0");
	}

	fireper.x = 50;
	fireper.y = 214;
	fireper.stat = 0;


	HANDLE threadHand1 = CreateThread(NULL, NULL, could_rand, NULL, NULL, NULL);
	HANDLE threadHand2 = CreateThread(NULL, NULL, barrier_rand, NULL, NULL, NULL);
	while (1) {
		printScore(hscore);
		score++;
		if (i % 100 == 0) {
			speed *= 2;
			//�л�����
			putimage(0, 0, &img1);
		}


		if (i % 200 == 0) {
			putimage(0, 0, &img);
		}
		//role_roll(8);
		if (_kbhit()) {
			keyDown();
		}
		else {
			role_move(8);
		}
		HANDLE handles = CreateThread(NULL, NULL, isOver, NULL, NULL, NULL);
		if (flag) {
			CloseHandle(handles);

			break;
		}
		i++;

	}
	CloseHandle(threadHand1);
	CloseHandle(threadHand2);

	putimage(340, 182, run_over, SRCAND);
	putimage(340, 182, run_over + 1, SRCPAINT);
	Sleep(3000);
	if (score > hscore->HeightScore) {
	//	HWND hwnd = GetConsoleWindow();
		hscore->HeightScore = score;
		setHeightScore(hscore);
		//��ʾ��
	//	MessageBoxA(hwnd, "��ϲ��ȡ����߷֣�", "�Ƽ�¼��", 0);
	}
	putimage(329, 300, restart, SRCAND);
	putimage(329, 300, restart + 1, SRCPAINT);
	restartGame();
}
/*���¿�ʼ��Ϸ*/
void restartGame() {
	MOUSEMSG m;
	//�ȴ�����ʱ��������ص���Ϸ��ʼ����
	int i = 100;

	while (i--) {

		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if ((m.x > 329 && m.x < 752) && (m.y > 300 && m.y < 390)) {
				//���ѡ�����¿�ʼ
				startGame();
				break;
			}
		}
		if (_kbhit())
		{
			if (_getch() == 'r') {
				//����ѡ�����¿�ʼ
				startGame();
				break;
			}
		}
	}
}

/*
	���� �ػ�����
*/
/*������Ϸ����*/
void startModel() {
	int x;
	int y;
	for (int i = 100; i > 0; i--) {
		x = rand() % 1080;
		y = rand() % 516;
		setColor_cirl(x, y);

		Sleep(50);

	}
	settextstyle(101, 0, NULL);
	setcolor(RGB(0, 192, 182));
	outtextxy(150, 230, "��ӭ����������");
	Sleep(1000);

}
/*�˳���Ϸ����*/
void exitModel() {
	cleardevice();//�ñ���ɫ�������Ļ
	for (int x = 10; x > 0; x--)
	{
		int size = rand() % 28 + 28;
		//�����������
		exitModel_font(rand() % 1080, rand() % 583, size);
		//�������
		exitModel_line();
		exitModel_line();
		if (x == 1) {
			//��Ϸ���� �ټ�
			exitModel_font(500, 250, 100);
		}
	}
}
/*�����Բ*/
void setColor_cirl(int x, int y) {
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;

	setlinecolor(RGB(r, g, b));
	setfillcolor(RGB(r, g, b));
	fillcircle(x, y, 10);
}
/*�������*/
void setColor_line(int x1, int y1, int x2, int y2) {
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;

	setlinecolor(RGB(r, g, b));
	line(x1, y1, x2, y2);

}
/*�˳�����������ʾ*/
void exitModel_line() {
	int x = rand() % 1080;
	int y = rand() % 516;

	setColor_line(x, y, x, y + 50);

	setColor_line(x - 15, y + 5, x - 41, y + 35);

	setColor_line(x - 10, y - 10, x - 38, y - 38);

	setColor_line(x + 5, y - 15, x + 30, y - 38);

	setColor_line(x + 10, y - 5, x + 62, y - 10);
}
/*�˳����� ������ʾ*/
void exitModel_font(int x, int y,int size) {
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;
	setlinecolor(RGB(r, g, b));
	setcolor(RGB(r, g, r));

	settextstyle(size, 0, NULL);
	outtextxy(x, y, "�ټ�");
	//outtextxy(900 - x, 200, "�ټ�");
	// ��ʱ
	Sleep(500);

	setcolor(BLACK);
	settextstyle(size, 0, NULL);
	outtextxy(x, y, "�ټ�");
}

/*

	����
*/

/*��ȡ��߷�*/
 int getHeightScore(struct Hscore *hscore) {

	FILE* file = NULL;
	fopen_s(&file, fileName, "rb+");//��ȡ��¼

	if (file == NULL) {
		return 0;
	}

//	fscanf_s(file, "%s", hscore->name);

	fscanf_s(file,"%d",&hscore->HeightScore);

	fclose(file);
	return 1;
}
 /*��¼��߷�*/
 void setHeightScore(struct Hscore* hscore) {
	 FILE* file = NULL;
	 fopen_s(&file, fileName, "wb+");  //���ļ�

	 if (file == NULL) {
		 return;
	 }

	// fprintf_s(file, "%s", hscore->name);
	 fprintf_s(file, "%d", hscore->HeightScore);

	 fclose(file);
 
 }
 /*��ӡ����*/
 void printScore(struct Hscore *hscore) {
	 //��ȡ��ǰ�����Ƿ������߷�
	 int height = hscore->HeightScore > score ? hscore->HeightScore : score;
	 //ѡ��������ɫ
	 settextcolor(BLUE);
	 char str[20];
	 solidrectangle(0, 0, 153, 81);
	 sprintf_s(str, "��߷� %d", height);
	 outtextxy(22, 15, str);
	 strcpy_s(str, "\0");
	 sprintf_s(str, "��ǰ�� %d", score);
	 outtextxy(22, 52, str);
	 strcpy_s(str, "\0");
 }