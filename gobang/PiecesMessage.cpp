#include "PiecesMessager.h"
#include "main.h"

void Draw(int(&xt), int(&yt))
{
	POINT pts1[]{
		{xt * 40 + 20,yt * 40 + 30 },
		{xt * 40 + 20,yt * 40 + 20 },
		{xt * 40 + 30,yt * 40 + 20 },
	};
	POINT pts2[]{
		{xt * 40 + 50,yt * 40 + 20 },
		{xt * 40 + 60,yt * 40 + 20 },
		{xt * 40 + 60,yt * 40 + 30 },
	};
	POINT pts3[]{
		{xt * 40 + 60,yt * 40 + 50 },
		{xt * 40 + 60,yt * 40 + 60 },
		{xt * 40 + 50,yt * 40 + 60 },
	};
	POINT pts4[]{
		{xt * 40 + 30,yt * 40 + 60 },
		{xt * 40 + 20,yt * 40 + 60 },
		{xt * 40 + 20,yt * 40 + 50 },
	};
	polyline(pts1, 3);
	polyline(pts2, 3);
	polyline(pts3, 3);
	polyline(pts4, 3);
	FlushBatchDraw();

}

int Back(pieces& game)
{
	int xt, yt;
	xt = game.chessx;
	yt = game.chessy;
	game.map[xt][yt] = { 0 };
	setfillcolor(0x005498);
	solidrectangle(xt * 40 + 25, yt * 40 + 25, xt * 40 + 55, yt * 40 + 55);
	setlinecolor(BLACK);
	line(xt * 40 + 40, yt * 40 + 25, xt * 40 + 40, yt * 40 + 55);
	line(xt * 40 + 25, yt * 40 + 40, xt * 40 + 55, yt * 40 + 40);
	return 1;
}

int WB(pieces(&game))
{
	setfillcolor(WHITE);
	ExMessage m; // 定义鼠标消息
	while (1)
	{
		flushmessage();
		m = getmessage(EM_MOUSE);       // 获取一条鼠标消息
		if (m.lbutton)
		{
			int x = (m.x - 20) / 40;
			int y = (m.y - 20) / 40;
			if (m.x < 800 && m.x>780 && m.y > 0 && m.y < 20)
				return Back(game) + 1;
			if (game.map[x][y] == 0)
			{
				int x_temp = x * 40 + 40;
				int y_temp = y * 40 + 40;               //修正白棋的位置
				if (x_temp > 20 && x_temp < 770 && y_temp>20 && y_temp < 770)  //限制白棋的范围
				{
					game.chessx = x;
					game.chessy = y;
					game.map[x][y] = { 101 };
					setlinecolor(BLACK);
					fillcircle(x_temp, y_temp, 15);
					FlushBatchDraw();
					if (game.win(x, y, 101))
						return 0;
					else
						return 2;
				}
			}
		}
		FlushBatchDraw();
	}
}
int BB(pieces& game, int& xt, int& yt)
{
	Draw(xt, yt);
	FlushBatchDraw();
	ExMessage k;
	while (1)
	{
		flushmessage();
		k = getmessage(EM_KEY);
		if (k.message == WM_KEYDOWN)
		{
			setfillcolor(BLACK);
			setlinecolor(WHITE);
			switch (k.vkcode)
			{
			case VK_UP:
				if ((yt - 1) >= 0)
				{
					setlinecolor(0x005498);
					Draw(xt, yt);
					yt -= 1;
					setlinecolor(RED);
					Draw(xt, yt);
					break;
				}
				else
					break;
			case VK_DOWN:
				if ((yt + 1) <= 18)
				{
					setlinecolor(0x005498);
					Draw(xt, yt);
					yt += 1;
					setlinecolor(RED);
					Draw(xt, yt);
					break;
				}
				else
					break;
			case VK_LEFT:
				if ((xt - 1) >= 0)
				{
					setlinecolor(0x005498);
					Draw(xt, yt);
					xt -= 1;
					setlinecolor(RED);
					Draw(xt, yt);
					break;
				}
				else
					break;
			case VK_RIGHT:
				if ((xt + 1) <= 18)
				{
					setlinecolor(0x005498);
					Draw(xt, yt);
					xt += 1;
					setlinecolor(RED);
					Draw(xt, yt);
					break;
				}
				else
					break;
			case VK_SPACE:
				if (game.map[xt][yt] == 0)
				{
					Draw(xt, yt);
					game.chessx = xt;
					game.chessy = yt;
					game.map[xt][yt] = { 100 };
					setlinecolor(WHITE);
					setfillcolor(BLACK);
					fillcircle(xt * 40 + 40, yt * 40 + 40, 15);
					FlushBatchDraw();
					if (game.win(xt, yt, 100))
						return 0;
					else
						return 1;
				}
				else
					break;
			case 0x51:
			{
				return Back(game);
			}
			}
			FlushBatchDraw();
		}
	}
}
