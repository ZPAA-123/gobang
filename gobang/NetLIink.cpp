#pragma once
#include "NetLink.h"
using namespace std;


int MINkey(iplist* ip)
{
	int R = 0;
	for (int i = 0; i < 4; i++)
	{
		ip[i].count<= ip[i + 1].count ? R : R = i + 1;
	}
	return R;
}


//服务端的处理
int open_server(SOCKET& socketServer, SOCKET& socketClient)
{
	// 1.开启网络库
	WORD wVersionRequird = MAKEWORD(2, 2);	// MAKEWORD(主版本,副版本)
	WSADATA wdScokMsg;
	switch (WSAStartup(wVersionRequird, &wdScokMsg))
	{
	case WSASYSNOTREADY:
		cout << "重启电脑试试，或者检查网络库" << endl;
		return -1;

	case WSAVERNOTSUPPORTED:
		cout << "请更新网络库\n";
		return -1;

	case WSAEPROCLIM:
		cout << "请尝试关掉不必要的软件，以为当前网络运行提供充足的资源\n";
		return -1;

	case WSAEINPROGRESS:
		cout << "请重新启动\n";
		return -1;
	}
	cout << "网络库开启成功" << endl;
	//2、校验版本
	if (2 != HIBYTE(wdScokMsg.wVersion) || 2 != LOBYTE(wdScokMsg.wVersion))
	{
		cout << "版本不存在\n";
		WSACleanup();
		return -1;
	}
	cout << "版本校验成功" << endl;
	//3、创建服务器socket(监听套接字)
	socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//TCP连接
	if (INVALID_SOCKET == socketServer)
	{
		cout << "创建socket失败 error:" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "创建服务器成功" << endl;
	//4、绑定地址和端口


	//将文件中的IP列表读取到所建立的结构体中
	iplist ip[5];	
	//读取文件
	FILE* IP;
	if (fopen_s(&IP, "./data/iplist.txt", "rb+"))
	{
		cout << "读取文件错误！";
		exit(0);
	}
	fseek(IP, 0, SEEK_SET);
	for (int i = 0; i < 5; i++)
	{
		fread(&ip[i], sizeof(iplist), 1, IP);
	}
	fclose(IP);
	//fwrite(ip, sizeof(iplist), 5, IP);
	//展示所储存的IP地址
	for (int i = 0; i < 5; i++)
	{
		cout << ip[i].key << " " << ip[i].ip << endl;
	}
	//判断是否需要更新IP列表或是直接使用ip
	char iptemp[20];
	cout << "请输入对方的IP/或是输入上方所展示的IP编号" << endl;
	cin >> iptemp;
	int len = strlen(iptemp);
	if (len > 1)
	{
		int flash = 0;
		while (1)
		{
			if (iptemp == ip[flash].ip)
			{
				ip[flash].count+=1;
				break;
			}
			flash++;
			if (flash == 5)
			{
				flash = MINkey(ip);
				strcpy_s(ip[flash].ip, sizeof(ip[flash].ip), iptemp);
				ip[flash].count += 1;
				break;
			}
		}
	}
	else
	{
		int temp = iptemp[0];
		strcpy_s(iptemp, sizeof(iptemp), ip[temp].ip);
	}
	//重新写入ip链表到文件中
	FILE* IPW;
	if (fopen_s(&IPW, "./data/iplist.txt", "wb+"))
	{
		cout << "写入文件错误！";
		exit(0);
	}
	fseek(IP, 0, SEEK_SET);
	for (int i = 0; i < 5; i++)
	{
		fwrite(&ip[i], sizeof(iplist), 1, IP);
	}

	fclose(IPW);

	// 绑定地址
	SOCKADDR_IN sockAddress;
	struct in_addr p;
	sockAddress.sin_family = AF_INET;
	inet_pton(AF_INET, iptemp, &p);
	sockAddress.sin_addr = p;
	sockAddress.sin_port = htons(6666);
	if (SOCKET_ERROR == bind(socketServer, (struct sockaddr*)&sockAddress, sizeof(sockAddress)))
	{
		cout << "bind 失败 error:" << WSAGetLastError() << endl;
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}
	cout << "绑定地址成功" << endl;
	// 5、开始监听
	if (SOCKET_ERROR == listen(socketServer, SOMAXCONN))
	{
		cout << "listen 失败 error:" << WSAGetLastError() << endl;
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}
	cout << "正在监听。。。";
	// 6、接受链接
	SOCKADDR_IN sockClient;
	int nLen = sizeof(sockClient);
	socketClient = accept(socketServer, (struct sockaddr*)&sockClient, &nLen);
	if (INVALID_SOCKET == socketClient)
	{
		cout << "accept 失败 error:" << WSAGetLastError() << endl;
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}
	cout << "客户端连接成功\n";
}

//客户端的处理
int open_client(SOCKET& socketServer, SOCKET& socketClient)
{
	// 1.开启网络库
	WORD wVersionRequird = MAKEWORD(2, 2);	// MAKEWORD(主版本,副版本)
	WSADATA wdScokMsg;
	switch (WSAStartup(wVersionRequird, &wdScokMsg))
	{
	case WSASYSNOTREADY:
		cout << "重启电脑试试，或者检查网络库\n";
		return -1;

	case WSAVERNOTSUPPORTED:
		cout << "请更新网络库\n";
		return -1;

	case WSAEPROCLIM:
		cout << "请尝试关掉不必要的软件，以为当前网络运行提供充足的资源\n";
		return -1;

	case WSAEINPROGRESS:
		cout << "请重新启动\n";
		return -1;
	}
	cout << "网络库开启成功" << endl;
	//2、校验版本
	if (2 != HIBYTE(wdScokMsg.wVersion) || 2 != LOBYTE(wdScokMsg.wVersion))
	{
		cout << "版本不存在\n";
		WSACleanup();
		return -1;
	}
	cout << "版本校验成功" << endl;
	//3、创建socket
	socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//TCP连接
	if (INVALID_SOCKET == socketClient)
	{
		cout << "创建socket失败 error:" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "创建连接成功" << endl;


	//将文件中的IP列表读取到所建立的结构体中
	iplist ip[5];
	for (int i = 1; i < 6; i++)
	{
		ip[i - 1].key = i;
	}
	//读取文件
	FILE* IP;
	if (fopen_s(&IP, "./data/iplist.txt", "wb+"))
	{
		cout << "读取文件错误！";
		exit(0);
	}
	for (int i = 0; i < 5; i++)
	{
		fread(&ip[i], sizeof(iplist), 1, IP);
	}

	//fwrite(ip, sizeof(iplist), 5, IP);
	//展示所储存的IP地址
	for (int i = 0; i < 5; i++)
	{
		cout << ip[i].key << " " << ip[i].ip << endl;
	}
	//判断是否需要更新IP列表或是直接使用ip
	char iptemp[20];
	cout << "请输入对方的IP/或是输入上方所展示的IP编号" << endl;
	cin >> iptemp;
	int len = strlen(iptemp);
	if (len > 1)
	{
		int flash = 0;
		while (1)
		{
			if (iptemp == ip[flash].ip)
			{
				ip[flash].count++;
				break;
			}
			flash++;
			if (flash == 5)
			{
				flash = MINkey(ip);
				strcpy_s(ip[flash].ip, sizeof(ip[flash].ip), iptemp);
				ip[flash].count = 1;
				break;
			}
		}
	}
	else
	{
		int temp = iptemp[0];
		strcpy_s(iptemp, sizeof(iptemp), ip[temp].ip);
	}
	//重新写入ip链表到文件中
	for (int i = 0; i < 5; i++)
	{
		fwrite(&ip[i], sizeof(iplist), 1, IP);
	}

	fclose(IP);
	// 4、连接服务器
	SOCKADDR_IN sockAddress;
	sockAddress.sin_family = AF_INET;
	inet_pton(AF_INET, iptemp, &sockAddress.sin_addr);
	sockAddress.sin_port = htons(6666);
	if (SOCKET_ERROR == connect(socketClient, (struct sockaddr*)&sockAddress, sizeof(sockAddress)))
	{
		cout << "connect 失败 error:" << WSAGetLastError() << endl;
		closesocket(socketClient);
		WSACleanup();
		return -1;
	}
	cout << "连接到服务器" << endl;
}

//网络连接时黑子的下棋操作
int BB_net(pieces(&game))
{
	if (game.back)
		return Back(game);
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
//网络连接时的白棋的下棋操作
int WB_net(pieces(&game))
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
			if (m.x < 800 && m.x>780 && m.y > 0 && m.y < 20)
			{
				game.back = 1;
				return Back(game) + 1;
			}
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
//客户端的消息收发与游戏的进行
void client_start(pieces& gamemod1, SOCKET& socketServer, SOCKET& socketClient)
{
	Draw_map();
	BeginBatchDraw();
	int g = 1;
	while (g)
	{
		// 缓冲区
		char szRecvBuffer[3];
		char szSendBuffer[3];

		//先手发送消息
		g = WB_net(gamemod1);
		szSendBuffer[0] = gamemod1.chessx;
		szSendBuffer[1] = gamemod1.chessy;
		szSendBuffer[2] = gamemod1.back;


		int result = recv(socketClient, szRecvBuffer, sizeof(szRecvBuffer), 0);

		if (0 == result)	// 服务端正常关闭
		{
			printf("客户端正常下线\n");
			break;	// 因为这个例子只接受一次客户端请求所以服务器关闭
		}
		else if (SOCKET_ERROR == result)	// recv出错
		{
			printf("recv 失败 error:%d\n", WSAGetLastError());
			break;
		}
		else	// 给服务端发消息
		{
			// 接收到服务端消息 
			gamemod1.chessx = szRecvBuffer[0];
			gamemod1.chessy = szRecvBuffer[1];
			gamemod1.back = szRecvBuffer[2];
			g = BB_net(gamemod1);

			if (SOCKET_ERROR == send(socketClient, szSendBuffer, strlen(szSendBuffer) + 1, 0))
			{
				printf("send 失败 error:%d\n", WSAGetLastError());
				break;
			}
		}
	}
	EndBatchDraw();
}
//服务端的消息收发与游戏的进行
void server_start(pieces& gamemod1, SOCKET& socketServer, SOCKET& socketClient)
{
	Draw_map();
	BeginBatchDraw();
	int g = 1;
	// 与客户端收发消息
	while (g)    //先手接受消息消息
	{
		// 缓冲区
		char szRecvBuffer[3];
		char szSendBuffer[3];

		int result = recv(socketClient, szRecvBuffer, sizeof(szRecvBuffer), 0);

		if (0 == result)	// 客户端正常关闭
		{
			printf("客户端正常下线\n");
			break;	// 因为这个例子只接受一次客户端请求所以服务器关闭
		}
		else if (SOCKET_ERROR == result)	// recv出错
		{
			printf("recv 失败 error:%d\n", WSAGetLastError());
			break;
		}
		else	// 给客户端发消息
		{
			// 接收到客户端消息 
			gamemod1.chessx = szRecvBuffer[0];
			gamemod1.chessy = szRecvBuffer[1];
			gamemod1.back = szRecvBuffer[2];
			g = BB_net(gamemod1);

			// 给客户回信
			g = WB_net(gamemod1);
			szSendBuffer[0] = gamemod1.chessx;
			szSendBuffer[1] = gamemod1.chessy;
			szSendBuffer[2] = gamemod1.back;
			if (SOCKET_ERROR == send(socketClient, szSendBuffer, strlen(szSendBuffer) + 1, 0))
			{
				printf("send 失败 error:%d\n", WSAGetLastError());
				break;
			}
		}
	}
	EndBatchDraw();
}
