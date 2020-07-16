#include"head.h"

int flag;

int speed;

int score;
//最高分数
struct Hscore {
	int HeightScore;
	char name[30];
};
//人物坐标和状态
struct FirePer {
	int x;
	int y;
	int stat; //1 跳 0 跑 -1 滚
}fireper;
//障碍物坐标
struct Barrier {
	int x;
	int y;

}bars;

/*
	人物动作图片
*/
IMAGE roll[8];
IMAGE move[8];
IMAGE jump;

/*
	障碍物和云朵图片
*/
IMAGE barrier[5];
IMAGE could[2];

/*
	游戏结束 和 重新开始图片
*/
IMAGE run_over[2];
IMAGE restart[2];

/*
	图片加载
*/
/*加载图片资源*/
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
/*放置图片和销毁图片*/
void putAnddesImage(int x1, int y1, int x2, int y2, IMAGE* img) {

	solidrectangle(x1, y1, x2, y2);

	putimage(x1, y1, img);
	Sleep(50);

	clearrectangle(x1, y1, x2, y2);
}

/*

	描述人物动作

*/

/*移动*/
void role_move(int frameNum) {
	fireper.stat = 0;
	int i = 0;
	while (i < frameNum) {
		//cleardevice();
	//	solidrectangle(fireper.x, fireper.y, fireper.x + 180, 442);
		putimage(fireper.x, fireper.y, move + i);
		//时间间隔0.05ms
		Sleep(50);
		i++;
	}
	if (fireper.x > 50) {
		//自动往后退
		fireper.x -= 10;
	}
}
/*翻滚*/
void role_roll(int frameNum) {
	fireper.stat = -1;
	int i = 0;
	clearrectangle(fireper.x, fireper.y, fireper.x + 180, 442);
	//人物向下滚 y坐标增加
	fireper.y += 117;
	while (i < frameNum) {
		putAnddesImage(fireper.x + i * 5, fireper.y, fireper.x + 130 + i * 5, 442, roll + i);
		i++;
	}
	fireper.y -= 117;
	//向前移动
	fireper.x += 35;
}
/*跳*/
void role_jump() {
	fireper.stat = 1;
	clearrectangle(fireper.x, fireper.y, fireper.x + 180, 442);
	//	rectangle(50,34,265,262);
	for (int i = 1; i < 10; i++) {
		//向上跳 x  坐标 增加 y减小
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
		//往下掉 x坐标增加 y增加
		putAnddesImage(fireper.x + i * 12, fireper.y + i * 12, fireper.x + 180, 322 + i * 12, &jump);

	}
	//不能超出界面窗口
	if (fireper.x > 950) {
		fireper.x = 950;
	}
	else {
		fireper.x += 120;
	}
	fireper.y += 120;
}
/*前进*/
void role_forward(int frameNum) {
	//人物状态
	fireper.stat = 0;
	int i = 0, f = 0;
	if (fireper.x == 800) {
		return;
	}
	while (i < frameNum) {
		//不能超过最大值
		if (fireper.x + i * 10 > 800) {
			f = 1;
			return;
		}
		//x坐标增加
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
/*后退*/
void role_back(int frameNum) {
	fireper.stat = 0;
	int i = 0, f = 0;
	if (fireper.x == 50) {
		return;
	}
	while (i < frameNum) {
		//不能低于最小坐标
		if (fireper.x - i * 10 < 60) {
			f = 1;
			return;
		}
		//x坐标减小 10
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
/*按键响应*/
void keyDown() {
	char key = _getch();
	switch (key) {
	case 's'://翻滚
	case 'S':
		role_roll(8); break;
	case ' '://跳跃
		role_jump(); break;
	case 'a'://后退
	case 'A':
		role_back(8); break;
	case 'd'://前进
	case 'D':
		role_forward(8); break;
	default:
		break;
	}
}

/*
	多线程处理
*/

/*随机出现障碍物*/
DWORD WINAPI barrier_rand(LPVOID p) {
	srand((unsigned)time(NULL));
	//int frameNum = 4;
	int i = 0;
	
	while (1) {
		int temp = speed;  //存放速度的值
		//int frameNum = 4;
		int frameNum = rand() % 5;
		int height = 392;
		if (frameNum == 4) {
			height -= 142;
		}
		if (i % 100 == 0) {
			//空中障碍物  大小为90 * 39
			if (frameNum == 4) {
				BeginBatchDraw();//画图开始
				for (int i = 0; i < 1080 / temp; i++) {
					//画矩形存放障碍物
					rectangle(1080 - temp * i, height, 1170 - temp * i, height + 39);
					bars.x = 1080 - temp * i;
					bars.y = height;
					putimage(1080 - temp * i, height, barrier + frameNum);
					Sleep(25);
					if (isOver(NULL)) { //游戏结束判断
						break;
					}
					FlushBatchDraw(); //消除闪屏
					//消除矩形背景
					clearrectangle(1080 - temp * i, height, 1170 - temp * i, height + 39);
				}
				EndBatchDraw(); //画图结束
			}
			else {//地面障碍物 4中 大小为50*50
				BeginBatchDraw();
				for (int i = 0; i < 1080 / temp; i++) {
					rectangle(1080 - temp * i, height, 1130 - temp * i, height + 50);
					bars.x = 1080 - temp * i;
					bars.y = height;
					putimage(1080 - temp * i, height, barrier + frameNum);
					Sleep(25);
					if (isOver(NULL)) { //游戏结束判断
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
/*随机出现云朵*/
DWORD WINAPI could_rand(LPVOID p) {
	srand((unsigned)time(NULL));
	int i = 0;
	while (1) {
		int frameNum = rand() % 2;
		int height = 104;
		if (frameNum == 1) {
			height = 89;
		}//每隔1000出现一次云朵
		if (i % 1000 == 0) {
				//BeginBatchDraw();
			for (int i = 0; i < 520; i++) {
				rectangle(520 - i, 21, 691 - i, height + 21);
				putimage(520 - i, 21, could + frameNum);
				Sleep(100);
				if (isOver(NULL)) {
					break;
				}
					//FlushBatchDraw();无法消除闪屏
				clearrectangle(520 - i, 21, 691 - i, height + 21);

			}
			//	EndBatchDraw();
		}
		//游戏结束判断
		if (flag) {
			break;
		}
		i++;

	}
	return 0;
}
/*是否接触障碍物*/
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
/*创建播放音乐的线程*/
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
/*创建游戏结束背景音乐*/
DWORD WINAPI Bgm_over(LPVOID p) {
	mciSendStringA("open .\\bgm\\over.wav", 0, 0, 0);
	mciSendStringA("play .\\bgm\\over.wav wait", 0, 0, 0);
	mciSendStringA("close .\\bgm\\over.wav", 0, 0, 0);
	return 0;
}

/*
	游戏初始化，启动，重新开始
*/

/*初始化游戏界面*/
void initGame() {
	HWND  hwnd = initgraph(1080, 583, NULL);
	SetWindowTextA(hwnd, "洪洪快跑");
	//加载背景音乐
	HANDLE Bgmhwnd = CreateThread(NULL, NULL, Bgm, NULL, NULL, NULL);
	CloseHandle(Bgmhwnd);setbkcolor(WHITE);
	cleardevice();//用背景色来清空屏幕
	startModel();
	
	
	/*显示图片*/
	loadButton();
	loadResource();
	/*获取鼠标信息*/
	MOUSEMSG m;
	while (TRUE) {

		if (MouseHit()) {
			//获取鼠标消息
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				//进入游戏
				if (m.x > 534 && m.x < 801 && m.y > 204 && m.y < 277)
				{
					startGame();
					loadButton();
				}
				//退出游戏
				else if ((m.x > 534 && m.x < 801) && (m.y > 326 && m.y < 396))
				{
					exitModel();
					break;
				}
			}
			
		}
		if (_kbhit()) {
			//获取按键响应
			char ch = _getch();
				if (ch == 'j')//开始游戏
				{
					startGame();
					loadButton();
				}
				else if (ch == 'q') //结束游戏
				{
					exitModel();
					break;
				}


		}
	}

	closegraph();
}
/*加载首页按钮以及图示信息*/
void loadButton() {

	IMAGE img;
	/*加载图片*/
	loadimage(&img, "img\\start_bg.png");
	putimage(0, 0, &img);


	setlinecolor(RGB(0, 162, 232));
	setlinestyle(PS_SOLID, 5, 0, 0);
	settextcolor(RGB(0, 162, 232));
	settextstyle(28, 0, NULL);
	setfillcolor(WHITE);
	fillrectangle(534, 326, 801, 396);

	outtextxy(620, 355, "退出（q）");


	settextstyle(28, 0, NULL);
	fillrectangle(350, 440,1008 , 542);
	outtextxy(463, 483, "前进（d） 滚动（s） 后退（a） 跳跃（space）");

	setlinecolor(WHITE);
}
/*开始游戏*/
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
			//切换背景
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
		//提示框
	//	MessageBoxA(hwnd, "恭喜你取得最高分！", "破纪录啦", 0);
	}
	putimage(329, 300, restart, SRCAND);
	putimage(329, 300, restart + 1, SRCPAINT);
	restartGame();
}
/*重新开始游戏*/
void restartGame() {
	MOUSEMSG m;
	//等待输入时长，否则回到游戏开始界面
	int i = 100;

	while (i--) {

		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if ((m.x > 329 && m.x < 752) && (m.y > 300 && m.y < 390)) {
				//鼠标选择重新开始
				startGame();
				break;
			}
		}
		if (_kbhit())
		{
			if (_getch() == 'r') {
				//按键选择重新开始
				startGame();
				break;
			}
		}
	}
}

/*
	开机 关机动画
*/
/*开机游戏动画*/
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
	outtextxy(150, 230, "欢迎来到洪洪快跑");
	Sleep(1000);

}
/*退出游戏动画*/
void exitModel() {
	cleardevice();//用背景色来清空屏幕
	for (int x = 10; x > 0; x--)
	{
		int size = rand() % 28 + 28;
		//随机出现字体
		exitModel_font(rand() % 1080, rand() % 583, size);
		//随机画线
		exitModel_line();
		exitModel_line();
		if (x == 1) {
			//游戏结束 再见
			exitModel_font(500, 250, 100);
		}
	}
}
/*随机画圆*/
void setColor_cirl(int x, int y) {
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;

	setlinecolor(RGB(r, g, b));
	setfillcolor(RGB(r, g, b));
	fillcircle(x, y, 10);
}
/*随机画线*/
void setColor_line(int x1, int y1, int x2, int y2) {
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;

	setlinecolor(RGB(r, g, b));
	line(x1, y1, x2, y2);

}
/*退出动画线条显示*/
void exitModel_line() {
	int x = rand() % 1080;
	int y = rand() % 516;

	setColor_line(x, y, x, y + 50);

	setColor_line(x - 15, y + 5, x - 41, y + 35);

	setColor_line(x - 10, y - 10, x - 38, y - 38);

	setColor_line(x + 5, y - 15, x + 30, y - 38);

	setColor_line(x + 10, y - 5, x + 62, y - 10);
}
/*退出动画 文字显示*/
void exitModel_font(int x, int y,int size) {
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;
	setlinecolor(RGB(r, g, b));
	setcolor(RGB(r, g, r));

	settextstyle(size, 0, NULL);
	outtextxy(x, y, "再见");
	//outtextxy(900 - x, 200, "再见");
	// 延时
	Sleep(500);

	setcolor(BLACK);
	settextstyle(size, 0, NULL);
	outtextxy(x, y, "再见");
}

/*

	分数
*/

/*获取最高分*/
 int getHeightScore(struct Hscore *hscore) {

	FILE* file = NULL;
	fopen_s(&file, fileName, "rb+");//读取记录

	if (file == NULL) {
		return 0;
	}

//	fscanf_s(file, "%s", hscore->name);

	fscanf_s(file,"%d",&hscore->HeightScore);

	fclose(file);
	return 1;
}
 /*记录最高分*/
 void setHeightScore(struct Hscore* hscore) {
	 FILE* file = NULL;
	 fopen_s(&file, fileName, "wb+");  //打开文件

	 if (file == NULL) {
		 return;
	 }

	// fprintf_s(file, "%s", hscore->name);
	 fprintf_s(file, "%d", hscore->HeightScore);

	 fclose(file);
 
 }
 /*打印分数*/
 void printScore(struct Hscore *hscore) {
	 //获取当前分数是否大于最高分
	 int height = hscore->HeightScore > score ? hscore->HeightScore : score;
	 //选择字体颜色
	 settextcolor(BLUE);
	 char str[20];
	 solidrectangle(0, 0, 153, 81);
	 sprintf_s(str, "最高分 %d", height);
	 outtextxy(22, 15, str);
	 strcpy_s(str, "\0");
	 sprintf_s(str, "当前分 %d", score);
	 outtextxy(22, 52, str);
	 strcpy_s(str, "\0");
 }