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


//����˵Ĵ���
int open_server(SOCKET& socketServer, SOCKET& socketClient)
{
	// 1.���������
	WORD wVersionRequird = MAKEWORD(2, 2);	// MAKEWORD(���汾,���汾)
	WSADATA wdScokMsg;
	switch (WSAStartup(wVersionRequird, &wdScokMsg))
	{
	case WSASYSNOTREADY:
		cout << "�����������ԣ����߼�������" << endl;
		return -1;

	case WSAVERNOTSUPPORTED:
		cout << "����������\n";
		return -1;

	case WSAEPROCLIM:
		cout << "�볢�Թص�����Ҫ���������Ϊ��ǰ���������ṩ�������Դ\n";
		return -1;

	case WSAEINPROGRESS:
		cout << "����������\n";
		return -1;
	}
	cout << "����⿪���ɹ�" << endl;
	//2��У��汾
	if (2 != HIBYTE(wdScokMsg.wVersion) || 2 != LOBYTE(wdScokMsg.wVersion))
	{
		cout << "�汾������\n";
		WSACleanup();
		return -1;
	}
	cout << "�汾У��ɹ�" << endl;
	//3������������socket(�����׽���)
	socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//TCP����
	if (INVALID_SOCKET == socketServer)
	{
		cout << "����socketʧ�� error:" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "�����������ɹ�" << endl;
	//4���󶨵�ַ�Ͷ˿�


	//���ļ��е�IP�б��ȡ���������Ľṹ����
	iplist ip[5];	
	//��ȡ�ļ�
	FILE* IP;
	if (fopen_s(&IP, "./data/iplist.txt", "rb+"))
	{
		cout << "��ȡ�ļ�����";
		exit(0);
	}
	fseek(IP, 0, SEEK_SET);
	for (int i = 0; i < 5; i++)
	{
		fread(&ip[i], sizeof(iplist), 1, IP);
	}
	fclose(IP);
	//fwrite(ip, sizeof(iplist), 5, IP);
	//չʾ�������IP��ַ
	for (int i = 0; i < 5; i++)
	{
		cout << ip[i].key << " " << ip[i].ip << endl;
	}
	//�ж��Ƿ���Ҫ����IP�б����ֱ��ʹ��ip
	char iptemp[20];
	cout << "������Է���IP/���������Ϸ���չʾ��IP���" << endl;
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
	//����д��ip�����ļ���
	FILE* IPW;
	if (fopen_s(&IPW, "./data/iplist.txt", "wb+"))
	{
		cout << "д���ļ�����";
		exit(0);
	}
	fseek(IP, 0, SEEK_SET);
	for (int i = 0; i < 5; i++)
	{
		fwrite(&ip[i], sizeof(iplist), 1, IP);
	}

	fclose(IPW);

	// �󶨵�ַ
	SOCKADDR_IN sockAddress;
	struct in_addr p;
	sockAddress.sin_family = AF_INET;
	inet_pton(AF_INET, iptemp, &p);
	sockAddress.sin_addr = p;
	sockAddress.sin_port = htons(6666);
	if (SOCKET_ERROR == bind(socketServer, (struct sockaddr*)&sockAddress, sizeof(sockAddress)))
	{
		cout << "bind ʧ�� error:" << WSAGetLastError() << endl;
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}
	cout << "�󶨵�ַ�ɹ�" << endl;
	// 5����ʼ����
	if (SOCKET_ERROR == listen(socketServer, SOMAXCONN))
	{
		cout << "listen ʧ�� error:" << WSAGetLastError() << endl;
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}
	cout << "���ڼ���������";
	// 6����������
	SOCKADDR_IN sockClient;
	int nLen = sizeof(sockClient);
	socketClient = accept(socketServer, (struct sockaddr*)&sockClient, &nLen);
	if (INVALID_SOCKET == socketClient)
	{
		cout << "accept ʧ�� error:" << WSAGetLastError() << endl;
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}
	cout << "�ͻ������ӳɹ�\n";
}

//�ͻ��˵Ĵ���
int open_client(SOCKET& socketServer, SOCKET& socketClient)
{
	// 1.���������
	WORD wVersionRequird = MAKEWORD(2, 2);	// MAKEWORD(���汾,���汾)
	WSADATA wdScokMsg;
	switch (WSAStartup(wVersionRequird, &wdScokMsg))
	{
	case WSASYSNOTREADY:
		cout << "�����������ԣ����߼�������\n";
		return -1;

	case WSAVERNOTSUPPORTED:
		cout << "����������\n";
		return -1;

	case WSAEPROCLIM:
		cout << "�볢�Թص�����Ҫ���������Ϊ��ǰ���������ṩ�������Դ\n";
		return -1;

	case WSAEINPROGRESS:
		cout << "����������\n";
		return -1;
	}
	cout << "����⿪���ɹ�" << endl;
	//2��У��汾
	if (2 != HIBYTE(wdScokMsg.wVersion) || 2 != LOBYTE(wdScokMsg.wVersion))
	{
		cout << "�汾������\n";
		WSACleanup();
		return -1;
	}
	cout << "�汾У��ɹ�" << endl;
	//3������socket
	socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//TCP����
	if (INVALID_SOCKET == socketClient)
	{
		cout << "����socketʧ�� error:" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "�������ӳɹ�" << endl;


	//���ļ��е�IP�б��ȡ���������Ľṹ����
	iplist ip[5];
	for (int i = 1; i < 6; i++)
	{
		ip[i - 1].key = i;
	}
	//��ȡ�ļ�
	FILE* IP;
	if (fopen_s(&IP, "./data/iplist.txt", "wb+"))
	{
		cout << "��ȡ�ļ�����";
		exit(0);
	}
	for (int i = 0; i < 5; i++)
	{
		fread(&ip[i], sizeof(iplist), 1, IP);
	}

	//fwrite(ip, sizeof(iplist), 5, IP);
	//չʾ�������IP��ַ
	for (int i = 0; i < 5; i++)
	{
		cout << ip[i].key << " " << ip[i].ip << endl;
	}
	//�ж��Ƿ���Ҫ����IP�б����ֱ��ʹ��ip
	char iptemp[20];
	cout << "������Է���IP/���������Ϸ���չʾ��IP���" << endl;
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
	//����д��ip�����ļ���
	for (int i = 0; i < 5; i++)
	{
		fwrite(&ip[i], sizeof(iplist), 1, IP);
	}

	fclose(IP);
	// 4�����ӷ�����
	SOCKADDR_IN sockAddress;
	sockAddress.sin_family = AF_INET;
	inet_pton(AF_INET, iptemp, &sockAddress.sin_addr);
	sockAddress.sin_port = htons(6666);
	if (SOCKET_ERROR == connect(socketClient, (struct sockaddr*)&sockAddress, sizeof(sockAddress)))
	{
		cout << "connect ʧ�� error:" << WSAGetLastError() << endl;
		closesocket(socketClient);
		WSACleanup();
		return -1;
	}
	cout << "���ӵ�������" << endl;
}

//��������ʱ���ӵ��������
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
//��������ʱ�İ�����������
int WB_net(pieces(&game))
{
	setfillcolor(WHITE);
	ExMessage m;            // ���������Ϣ	
	while (1)
	{
		flushmessage();
		m = getmessage(EM_MOUSE);       // ��ȡһ�������Ϣ
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
				int y_temp = y * 40 + 40;               //���������λ��
				if (x_temp > 20 && x_temp < 770 && y_temp>20 && y_temp < 770)  //���ư���ķ�Χ
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
//�ͻ��˵���Ϣ�շ�����Ϸ�Ľ���
void client_start(pieces& gamemod1, SOCKET& socketServer, SOCKET& socketClient)
{
	Draw_map();
	BeginBatchDraw();
	int g = 1;
	while (g)
	{
		// ������
		char szRecvBuffer[3];
		char szSendBuffer[3];

		//���ַ�����Ϣ
		g = WB_net(gamemod1);
		szSendBuffer[0] = gamemod1.chessx;
		szSendBuffer[1] = gamemod1.chessy;
		szSendBuffer[2] = gamemod1.back;


		int result = recv(socketClient, szRecvBuffer, sizeof(szRecvBuffer), 0);

		if (0 == result)	// ����������ر�
		{
			printf("�ͻ�����������\n");
			break;	// ��Ϊ�������ֻ����һ�οͻ����������Է������ر�
		}
		else if (SOCKET_ERROR == result)	// recv����
		{
			printf("recv ʧ�� error:%d\n", WSAGetLastError());
			break;
		}
		else	// ������˷���Ϣ
		{
			// ���յ��������Ϣ 
			gamemod1.chessx = szRecvBuffer[0];
			gamemod1.chessy = szRecvBuffer[1];
			gamemod1.back = szRecvBuffer[2];
			g = BB_net(gamemod1);

			if (SOCKET_ERROR == send(socketClient, szSendBuffer, strlen(szSendBuffer) + 1, 0))
			{
				printf("send ʧ�� error:%d\n", WSAGetLastError());
				break;
			}
		}
	}
	EndBatchDraw();
}
//����˵���Ϣ�շ�����Ϸ�Ľ���
void server_start(pieces& gamemod1, SOCKET& socketServer, SOCKET& socketClient)
{
	Draw_map();
	BeginBatchDraw();
	int g = 1;
	// ��ͻ����շ���Ϣ
	while (g)    //���ֽ�����Ϣ��Ϣ
	{
		// ������
		char szRecvBuffer[3];
		char szSendBuffer[3];

		int result = recv(socketClient, szRecvBuffer, sizeof(szRecvBuffer), 0);

		if (0 == result)	// �ͻ��������ر�
		{
			printf("�ͻ�����������\n");
			break;	// ��Ϊ�������ֻ����һ�οͻ����������Է������ر�
		}
		else if (SOCKET_ERROR == result)	// recv����
		{
			printf("recv ʧ�� error:%d\n", WSAGetLastError());
			break;
		}
		else	// ���ͻ��˷���Ϣ
		{
			// ���յ��ͻ�����Ϣ 
			gamemod1.chessx = szRecvBuffer[0];
			gamemod1.chessy = szRecvBuffer[1];
			gamemod1.back = szRecvBuffer[2];
			g = BB_net(gamemod1);

			// ���ͻ�����
			g = WB_net(gamemod1);
			szSendBuffer[0] = gamemod1.chessx;
			szSendBuffer[1] = gamemod1.chessy;
			szSendBuffer[2] = gamemod1.back;
			if (SOCKET_ERROR == send(socketClient, szSendBuffer, strlen(szSendBuffer) + 1, 0))
			{
				printf("send ʧ�� error:%d\n", WSAGetLastError());
				break;
			}
		}
	}
	EndBatchDraw();
}
