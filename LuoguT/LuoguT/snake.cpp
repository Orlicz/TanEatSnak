#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "snake.h"

int Canvas[HIGHT][WIDTH] = { 0 };
Food f;
bool playing;
int players;
Snake player[2];

WSADATA ws;
SOCKET clientSocket,serverSocket, server_client_Socket;
sockaddr_in  clinetAddr, serverAddr;
SOCKADDR server_client_addr;
int nsize;
bool isServer = false, isClient = false;

void  ASCIIArt(){				//�ַ���
	cout << "                 ,]]]]                     .]             .]]]         ]]       " << '\n';
	cout << "              ./@@@@@@\\`        ,]]]]]]]. .@@@@           .@@O       ,@@@^      " << '\n';
	cout << "          ,]@@@@@`]],@@@@@@]]`  =@@@@@@@.,@@@@@@@@@@@@^.@@@@@@@@^=@@@@@@@@@@@@^ " << '\n';
	cout << "       ,@@@@@[`  \\@@`  ,\\@@@@@. =@@^ @@@/@@@/[[[[[[[[[`.@@[@@@\\@^=@@^      @@@^ " << '\n';
	cout << "        ,`.@@@@@@@@@@@@@@@      =@@^ @@@.,@`           .@@.@@O=@^ ,]]]          " << '\n';
	cout << "                     /@@@`      =@@^ @@@. @@@@@@@@@@^  .@@.@@O=@^ =@@@   ./@\\   " << '\n';
	cout << "         .@@@@@@@@@@@@@@@@@@.   =@@^ @@@.     ,/@@@`   .@@@@@@@@^ =@@@,/@@@@/.  " << '\n';
	cout << "         .@@@[[[[[[[[[[[[@@@.   =@@^ @@@.   /@@@/.     .@@[@@@[[` =@@@@@@[      " << '\n';
	cout << "         .@@@.   =@@^   .@@@.   =@@\\]@@@. /@@@`    =@@]   .@@O=@@ =@@@     =@\\` " << '\n';
	cout << "         .@@@. ./@@@@@@]`@@@.   =@@@@@@@./@@/      /@@^,]]]@@@@@@^=@@@    .@@@^ " << '\n';
	cout << "         .]]/@@@@@` ,\\@@@@@@]`  =@@^ @@@.\\@@@]]]]]@@@@.=@@@@@@@\\@@=@@@@@@@@@@@. " << '\n';
	cout << "        \\@@@@@@[        ,[@@@^            ,[@@@@@@@/[          ,[  ,@@@@@@@@[   " << '\n';
}

void startMenu()							//��ʼ�˵�
{
	//system("title ̰����");
	//system("mode con cols=90 lines=45");

	gotoxy(0, 4);
	ASCIIArt();

	gotoxy(40, 24);
	cout << "��ʼ��Ϸ" << '\n';
	gotoxy(40, 26);
	cout << "������Ϸ" << '\n';
	gotoxy(40, 28);
	cout << "����" << '\n';
	gotoxy(40, 30);
	cout << "�˳���Ϸ" << '\n';

	gotoxy(2, 43);
	cout << "v1.0";

	int choise = 23;
	char ch;
	selectBox(38, choise);
	while ((ch = keydown()) != '\r')
	{
		cleanSelectBox(38, choise);
		if (ch == 's' || ch == 'S')
			choise += 2;
		else if (ch == 'w' || ch == 'W')
			choise -= 2;

		if (choise == 21)
		{
			choise = 29;
		}
		else if (choise == 31)
		{
			choise = 23;
		}
		selectBox(38, choise);
		Sleep(100);
	}

	switch (choise)
	{
	case 23:
		system("cls");
		players = 1;
		initialized();
		break;
	case 25:
		system("cls");
		players = 2;
		multiplayerMenu();
		break;
	case 27:
		helpMenu();
		break;
	case 29:
		exit(0);
		break;
	}

}

void multiplayerMenu() {				//���˲˵�			


	gotoxy(0, 4);
	ASCIIArt();

	gotoxy(40, 24);
	cout << "������Ϸ" << '\n';
	gotoxy(40, 26);
	cout << "������Ϸ" << '\n';
	gotoxy(40, 28);
	cout << "�����˵�" << '\n';
	gotoxy(40, 30);
	cout << "�˳���Ϸ" << '\n';

	int choise = 23;
	char ch;
	selectBox(38, choise);
	while ((ch = keydown()) != '\r'){
		cleanSelectBox(38, choise);
		if (ch == 's' || ch == 'S')
			choise += 2;
		else if (ch == 'w' || ch == 'W')
			choise -= 2;

		if (choise == 21)
			choise = 29;
		else if (choise == 31)
			choise = 23;
		selectBox(38, choise);
		Sleep(100);
	}

	switch (choise){
	case 23:
		system("cls");
		players = 2;
		createServer();
		initialized();
		break;
	case 25:
		system("cls");
		players = 2;
		cout << "����������ip: ";
		char ch[10];
		cin >> ch;
		fflush(stdin);
		createClient(ch);
		initialized();
		break;
	case 27:
		startMenu();
		break;
	case 29:
		exit(0);
		break;
	}
}

void helpMenu(){
	system("cls");
	gotoxy(0, 4);
	ASCIIArt();
	gotoxy(33, 24);
	cout << "����� \"W\" \"S\" \"A\" \"D\"�ֱ��Ӧ";
	gotoxy(33, 25);
	cout << "\"��\"  \"��\"  \"��\"  \"��\"";
	gotoxy(33, 26);
	cout << "��������������˵�";
	auto ch = _getch();
	startMenu();
}

void gotoxy(int x, int y) {			//���ù��λ��
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD r;
	r.X = x;
	r.Y = y;
	SetConsoleCursorPosition(h, r);
}

void selectBox(int x, int y) {		//��ʾѡ�п�

	gotoxy(x, y);
	cout << "------------";
	gotoxy(x, y + 1);
	cout << "|";
	gotoxy(x + 11, y + 1);
	cout << "|";
	gotoxy(x, y + 2);
	cout << "------------";
}

void cleanSelectBox(int x, int y) {	   //���ѡ�п�

	gotoxy(x, y);
	cout << "            ";
	gotoxy(x, y + 1);
	cout << " ";
	gotoxy(x + 11, y + 1);
	cout << " ";
	gotoxy(x, y + 2);
	cout << "            ";
}

inline char keydown() {					//��ȡ����
	if (char input;_kbhit()){
		//�а�������
		fflush(stdin);
		input = tolower(_getch());
		if (strchr("wsad\r", input))
			return input;
	}
	return '\0';
}

void initialized() {					//���ݳ�ʼ��

	//��ͼ��ʼ�������߿�
	for (int i = 0; i < HIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			if (i == 0 || i == HIGHT - 1 || j == 0 || j == WIDTH - 1)
				Canvas[i][j] = 1;

	playing = true;

	//��ʼ�����1
	player[0].len = 3;
	player[0].pos[0] = { 5, 10 };
	player[0].pos[1] = { 4, 10 };
	player[0].pos[2] = { 3, 10 };
	player[0].camp = 1;
	player[0].move = 'd';
	player[0].hp = 1;
	player[0].eat = false;

	if (players == 2){
		player[1].len = 3;
		player[1].pos[0] = { 33, 30 };
		player[1].pos[1] = { 34, 30 };
		player[1].pos[2] = { 35, 30 };
		player[1].camp = 2;
		player[1].move = 'a';
		player[1].hp = 1;
		player[1].eat = false;
	}
	if (isClient == false)
		createFood(f);
}

void show() {						//��ʾ����
	gotoxy(0, 0);
	for (int i = 0; i < HIGHT; i++){
		for (int j = 0; j < WIDTH; j++){
			switch (Canvas[i][j]){
			case 0:	cout << "  ";	break;	//�յ�
			case 1:	cout << "��";	break;	//�߿��ϰ�
			case 2:	cout << "��";	break;	//���1����ͷ
			case 3:	cout << "��";	break;	//���1������
			case 4:	cout << "��";	break;	//���2����ͷ
			case 6:	cout << "��";	break;	//���2������
			case 5: cout << "��";   break;	//ʳ��
			}
		}
		cout << '\n';
	}

	for (int i = 0; i < players; i++){
		gotoxy(i * 20, 41);
		cout << "���" << player[i].camp << "��";
		gotoxy(i * 20, 42);
		if (i == 0) cout << " ����";
		else cout << " ����";
		gotoxy(i * 20, 43);
		cout << "  ���ȣ�" << player[i].len;
	}
	gotoxy(40, 41);
	cout << "                   ";
	gotoxy(40, 41);
	cout << "ʳ��λ�ã�(" << f.pos.x << "," << f.pos.y << ")";
}

void upSnake(Snake& s) {				//��¼�ߵ�λ��
	for (int i = 0; i < s.len; i++)
		if (i == 0)
			Canvas[s.pos[i].y][s.pos[i].x] = s.camp * 2;
		else
			Canvas[s.pos[i].y][s.pos[i].x] = s.camp * 3;
}

void moveSnake(Snake& s) {			        //���ƶ�
	if (!s.eat)
		Canvas[s.pos[s.len - 1].y][s.pos[s.len - 1].x] = 0;
	else
		s.len++;
		s.eat = false;

	for (int i = s.len - 1; i > 0; i--)
		s.pos[i] = s.pos[i - 1];

	switch (s.move){
	case 'w':
		s.pos[0].y--;break;
	case 's':
		s.pos[0].y++;break;
	case 'a':
		s.pos[0].x--;break;
	case 'd':
		s.pos[0].x++;break;
	}
}

void isCrash(Snake& s) {				//�ߵ���ײ�ж�
	if (Canvas[s.pos[0].y][s.pos[0].x] == 1 ||
		Canvas[s.pos[0].y][s.pos[0].x] == 3 ||
		Canvas[s.pos[0].y][s.pos[0].x] == 6) {	//ײǽ��
		s.hp = 0;
		playing = false;
		gotoxy(8 + (s.camp - 1) * 20, 41);
		if (cout << "������";players == 2){
			int temp = s.camp;
			if (temp == 2)
				temp = 0;
			gotoxy(8 + temp * 20, 41);
			cout << "��Ӯ��";
		}
		gotoxy(28, 20);
		cout << "3����˳�";
	}
	else if (Canvas[s.pos[0].y][s.pos[0].x] == 5) //�߳Ե���ʳ��
		if (s.eat = true;isClient == false)
			createFood(f);
}

void updateWithoutInput() {			//���û��޹ص�����
	Canvas[f.pos.y][f.pos.x] = 5;
	for (int i = 0; i < players; i++){
		moveSnake(player[i]);
		isCrash(player[i]);
		upSnake(player[i]);
	}
}

void updateWithInput() {				//���û��йص�����
	if (_kbhit()) {
		//�а�������
		fflush(stdin);
		if (char ch = tolower(_getch()); strchr("wsad", ch))
			if (isClient == true)
				if ((player[1].move == 'a' && ch != 'd') || (player[1].move == 'd' && ch != 'a') ||
					(player[1].move == 'w' && ch != 's') || (player[1].move == 's' && ch != 'w'))
					player[1].move = ch;
				else;
			else
				if ((player[0].move == 'a' && ch != 'd') || (player[0].move == 'd' && ch != 'a') ||
					(player[0].move == 'w' && ch != 's') || (player[0].move == 's' && ch != 'w'))
					player[0].move = ch;
	}
}

void createFood(Food& f)	{ 		//����ʳ��
	srand((unsigned int)time(NULL));
	while (true){
		f.pos.x = rand() % WIDTH + 1;
		f.pos.y = rand() % HIGHT + 1;
		if (Canvas[f.pos.y][f.pos.x] == 0)
			break;
	}
}

void createClient(const char* str) {					//�����ͻ���
	isClient = true;
	if (WSAStartup(MAKEWORD(2, 2), &ws)) MessageBoxA(NULL, "RP̫��", "��ʾ", MB_OK);
	memset(&clinetAddr, 0, sizeof(clinetAddr));		//��0���
	clinetAddr.sin_family = AF_INET;				//ipv4
	clinetAddr.sin_addr.s_addr = inet_addr(str);	//�󶨷�����ip��ַ
	clinetAddr.sin_port = htons(1234);				//��1234�˿�
}

void createServer()					//����������
{
	isServer = true;
	if (WSAStartup(MAKEWORD(2, 2), &ws)) MessageBoxA(NULL, "RP̫��", "��ʾ", MB_OK);

	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&serverAddr, 0, sizeof(serverAddr));				//��0���
	serverAddr.sin_family = AF_INET;							//ipv4
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);			//�󶨷�����ip��ַ
	serverAddr.sin_port = htons(1234);						//��1234�˿�
	bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR));	//�󶨷������׽���

	listen(serverSocket, 10);								//�����׽���

	nsize = sizeof(SOCKADDR);
}