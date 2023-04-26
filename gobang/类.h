#pragma once

#include<graphics.h>
class pieces
{

public:
	int chessx = 0, chessy = 0;
	int back = 0;
	int map[19][19] = { 0 };
	//设置所在点位的棋子颜色
	void setmap(int x, int y, int color)
	{
		map[x][y] = color;
	}

	//胜利判断
	int win(int x, int y, int color)
	{
		if (search(x, y, color))
		{
			WinShow(color);
			return 1;
		}
		return 0;
	}
	//胜利图文展示
	void WinShow(int color)
	{

		TCHAR s1[] = _TEXT("白棋获胜！");
		TCHAR s2[] = _TEXT("黑棋获胜！");
		switch (color)
		{
		case 101:
			settextcolor(WHITE);
			outtextxy(360, 360, s1);
			break;
		case 100:
			settextcolor(BLACK);
			outtextxy(360, 360, s2);
			break;

		default:
			break;
		}
		FlushBatchDraw();
		system("pause");
	}

	//搜寻周围的棋子
	int search(int x, int y, int color)
	{
		int a = 0;
		a = WIN_A(x, y, color) +
			WIN_B(x, y, color) +
			WIN_C(x, y, color) +
			WIN_D(x, y, color);
		if (a > 0)
			return 1;
		else
			return 0;
	}
	//竖线方向的判断
	int WIN_A(int x, int y, int color)
	{
		int count = 0;
		int xt = x, yt = y;
		while (x > -1)
		{
			if (map[x][y] != color)
				break;
			count++;
			x--;
		}
		x = xt, y = yt;
		while (x < 19)
		{
			if (map[x][y] != color)
				break;
			count++;
			x++;
		}
		count--;
		if (count >= 5)
			return 1;
		else
			return 0;
	}
	//横线方向的判断
	int WIN_B(int x, int y, int color)
	{
		int xt = x, yt = y;
		int count = 0;
		while (y > -1)
		{
			if (map[x][y] != color)
				break;
			count++;
			y--;
		}
		x = xt, y = yt;
		while (y < 19)
		{
			if (map[x][y] != color)
				break;
			count++;
			y++;
		}
		count--;
		if (count >= 5)
			return 1;
		else
			return 0;

	}
	//-45°方向的判断
	int WIN_C(int x, int y, int color)
	{
		int xt = x, yt = y;
		int count = 0;
		while (y > -1 && x > -1)
		{
			if (map[x][y] != color)
				break;
			count++;
			y--, x--;
		}
		x = xt, y = yt;
		while (y < 19 && x < 19)
		{
			if (map[x][y] != color)
				break;
			count++;
			y++, x++;
		}
		count--;
		if (count >= 5)
			return 1;
		else
			return 0;

	}
	//45°方向的判断
	int WIN_D(int x, int y, int color)
	{
		int xt = x, yt = y;
		int count = 0;
		while (y > -1 && x < 19)
		{
			if (map[x][y] != color)
				break;
			count++;
			y--, x++;
		}
		x = xt, y = yt;
		while (y < 19 && x > -1)
		{
			if (map[x][y] != color)
				break;
			count++;
			y++, x--;
		}
		count--;
		if (count >= 5)
			return 1;
		else
			return 0;

	}
};