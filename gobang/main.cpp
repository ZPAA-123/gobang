#include "ALL.h"



int main()
{
	while (1)
	{
		cout << "1.˫�˶�ս" << endl << "2.�����ս" << endl << "3.�˻���ս" << endl;
		int gameflash;
		cin >> gameflash;
		switch (gameflash)
		{
		case 1:
		{
			int g = 1;
			pieces gamemod2;
			Draw_map();
			BeginBatchDraw();
			int x_t = 9, y_t = 9;   //���ú��ӳ�ʼλ��
			while (g)
			{
				if (g == 1)
					g = WB(gamemod2);
				else if (g == 2)
					g = BB(gamemod2, x_t, y_t);
			}
			EndBatchDraw();
			system("cls");
			break;
		}
		case 2:
		{
			pieces gamemod1;
			SOCKET socketClient;
			SOCKET socketServer;
			cout << "1.ѡ�񱾻���Ϊ�����" << endl << "2.ѡ�񱾻���Ϊ�ͻ���" << endl;
			int network;
			cin >> network;
			switch (network)
			{
			case 1:
			{
				open_server(socketServer, socketClient);
				server_start(gamemod1, socketServer, socketClient);
				break;
			}
			case 2:
			{
				open_client(socketServer, socketClient);
				client_start(gamemod1, socketServer, socketClient);
				break;
			}
			}
			break;
		}
		case 3:
		{
			pieces gamemodr;
			int setlevel;
			int g = 1;
			cout << "�Ѷ�ѡ��0-7����";
			cin >> setlevel;
			ChessEngine::setLevel(setlevel);
			Draw_map();
			BeginBatchDraw();
			while (g)
			{
				if (g == 1)
					g = WBAI(gamemodr);
				if (g == 2)
				{
					ChessEngine::nextStep(gamemodr);
					g = BBAI(gamemodr);
				}

			}

			EndBatchDraw();

			break;
		}

		}
	}

	system("pause");
	return 0;
}