#pragma once
#define WIN32_LEAN_AND_MEAN
#define 黑 100;
#define 白 101;

#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>//我们使用新版本第二版
#include<WS2tcpip.h>
#include<Windows.h>


#include <iostream>
#include "DrawBackground.h"
#include "PiecesMessager.h"
#include "AIStep.h"
#include "NetLink.h"
#include <fstream>
#include "main.h"

#include <cstdlib>
#include <set>
#include <vector>
#include <cmath>
#include <stack>
#include <cassert>



using namespace std;