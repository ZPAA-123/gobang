#include "DrawBackground.h"

void Draw_map()
{
	initgraph(800, 800);     //720x720 40  ���崰��
	SetBkcolor();    //���Ʊ���
	DrawBkline();    //��������
	DrawBkPoint();   //���ƶ�λ��
	DrawBack();       //���ƻ����־
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
	}//������
	for (int y = 40; y <= 760; y += 40)
	{
		line(40, y, 760, y);
	}
	//������
	line(39, 39, 39, 761);
	line(761, 39, 761, 761);
	line(39, 39, 761, 39);
	line(761, 761, 39, 761);
	//�Ӵ���Χ����
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
	//�Ӵֱ߿��ҷ��ñ�־ԭ��	
}

void DrawBack()
{
	setfillcolor(WHITE);
	solidrectangle(780, 0, 800, 20);
	TCHAR Back[] = _TEXT("����");
	settextcolor(RED);
	outtextxy(760, 0, Back);
}
