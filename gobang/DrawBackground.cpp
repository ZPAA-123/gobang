#include "DrawBackground.h"

void Draw_map()
{
	initgraph(800, 800);     //720x720 40  定义窗口
	SetBkcolor();    //绘制背景
	DrawBkline();    //绘制线条
	DrawBkPoint();   //绘制定位点
	DrawBack();       //绘制悔棋标志
}

void SetBkcolor()
{
	setbkcolor(0x005498);
	cleardevice();
}

void DrawBkline()
{
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	for (int x = 40; x <= 760; x += 40)
	{
		line(x, 40, x, 760);
	}//画竖线
	for (int y = 40; y <= 760; y += 40)
	{
		line(40, y, 760, y);
	}
	//画横线
	line(39, 39, 39, 761);
	line(761, 39, 761, 761);
	line(39, 39, 761, 39);
	line(761, 761, 39, 761);
	//加粗周围的线
}

void DrawBkPoint()
{
	fillcircle(160, 160, 3);
	fillcircle(160, 400, 3);
	fillcircle(160, 600, 3);
	fillcircle(400, 400, 4);
	fillcircle(400, 160, 3);
	fillcircle(400, 600, 3);
	fillcircle(600, 160, 3);
	fillcircle(600, 400, 3);
	fillcircle(600, 600, 3);
	//加粗边框并且放置标志原点	
}

void DrawBack()
{
	setfillcolor(WHITE);
	solidrectangle(780, 0, 800, 20);
	TCHAR Back[] = _TEXT("悔棋");
	settextcolor(RED);
	outtextxy(760, 0, Back);
}
