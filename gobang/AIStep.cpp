#include "AIStep.h"

using namespace std;

int WBAI(pieces& game)
{
	setfillcolor(WHITE);
	ExMessage m;            // 定义鼠标消息	
	while (1)
	{
		flushmessage();
		m = getmessage(EM_MOUSE);       // 获取一条鼠标消息
		if (m.lbutton)
		{
			int x = (m.x - 20) / 40;
			int y = (m.y - 20) / 40;
			if (game.map[x][y] == 0)
			{
				int x_temp = x * 40 + 40;
				int y_temp = y * 40 + 40;               //修正白棋的位置
				if (x_temp > 20 && x_temp < 770 && y_temp>20 && y_temp < 770)  //限制白棋的范围
				{
					game.map[x][y] = { 101 };
					game.chessx = x;
					game.chessy = y;
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

int BBAI(pieces& game)
{
	int x_temp = game.chessx * 40 + 40;
	int y_temp = game.chessy * 40 + 40;
	game.map[game.chessx][game.chessy] = { 100 };
	setlinecolor(WHITE);
	setfillcolor(BLACK);
	fillcircle(x_temp, y_temp, 15);
	FlushBatchDraw();
	if (game.win(game.chessx, game.chessy, 100))
		return 0;
	else
		return 1;
}