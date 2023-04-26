#pragma once
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <easyx.h>
#include "main.h"

using namespace std;

void Draw(int(&xt), int(&yt));
int Back(pieces& game);
int WB(pieces(&game));
int BB(pieces &game, int& xt, int& yt);