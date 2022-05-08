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

void  ASCIIArt(){				//字符画
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

void startMenu()							//开始菜单
{
	//system("title 贪吃蛇");
	//system("mode con cols=90 lines=45");

	gotoxy(0, 4);
	ASCIIArt();

	gotoxy(40, 24);
	cout << "开始游戏" << '\n';
	gotoxy(40, 26);
	cout << "多人游戏" << '\n';
	gotoxy(40, 28);
	cout << "帮助" << '\n';
	gotoxy(40, 30);
	cout << "退出游戏" << '\n';

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

void multiplayerMenu() {				//多人菜单			


	gotoxy(0, 4);
	ASCIIArt();

	gotoxy(40, 24);
	cout << "创建游戏" << '\n';
	gotoxy(40, 26);
	cout << "加入游戏" << '\n';
	gotoxy(40, 28);
	cout << "回主菜单" << '\n';
	gotoxy(40, 30);
	cout << "退出游戏" << '\n';

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
		cout << "请输入主机ip: ";
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
	cout << "方向键 \"W\" \"S\" \"A\" \"D\"分别对应";
	gotoxy(33, 25);
	cout << "\"上\"  \"下\"  \"左\"  \"右\"";
	gotoxy(33, 26);
	cout << "按任意键返回主菜单";
	auto ch = _getch();
	startMenu();
}

void gotoxy(int x, int y) {			//设置光标位置
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD r;
	r.X = x;
	r.Y = y;
	SetConsoleCursorPosition(h, r);
}

void selectBox(int x, int y) {		//显示选中框

	gotoxy(x, y);
	cout << "------------";
	gotoxy(x, y + 1);
	cout << "|";
	gotoxy(x + 11, y + 1);
	cout << "|";
	gotoxy(x, y + 2);
	cout << "------------";
}

void cleanSelectBox(int x, int y) {	   //清除选中框

	gotoxy(x, y);
	cout << "            ";
	gotoxy(x, y + 1);
	cout << " ";
	gotoxy(x + 11, y + 1);
	cout << " ";
	gotoxy(x, y + 2);
	cout << "            ";
}

inline char keydown() {					//获取按键
	if (char input;_kbhit()){
		//有按键接受
		fflush(stdin);
		input = tolower(_getch());
		if (strchr("wsad\r", input))
			return input;
	}
	return '\0';
}

void initialized() {					//数据初始化

	//地图初始化：画边框
	for (int i = 0; i < HIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			if (i == 0 || i == HIGHT - 1 || j == 0 || j == WIDTH - 1)
				Canvas[i][j] = 1;

	playing = true;

	//初始化玩家1
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

void show() {						//显示画面
	gotoxy(0, 0);
	for (int i = 0; i < HIGHT; i++){
		for (int j = 0; j < WIDTH; j++){
			switch (Canvas[i][j]){
			case 0:	cout << "  ";	break;	//空地
			case 1:	cout << "■";	break;	//边框障碍
			case 2:	cout << "○";	break;	//玩家1的蛇头
			case 3:	cout << "¤";	break;	//玩家1的蛇身
			case 4:	cout << "●";	break;	//玩家2的蛇头
			case 6:	cout << "¤";	break;	//玩家2的蛇身
			case 5: cout << "☆";   break;	//食物
			}
		}
		cout << '\n';
	}

	for (int i = 0; i < players; i++){
		gotoxy(i * 20, 41);
		cout << "玩家" << player[i].camp << "：";
		gotoxy(i * 20, 42);
		if (i == 0) cout << " ¤¤○";
		else cout << " ●¤¤";
		gotoxy(i * 20, 43);
		cout << "  长度：" << player[i].len;
	}
	gotoxy(40, 41);
	cout << "                   ";
	gotoxy(40, 41);
	cout << "食物位置：(" << f.pos.x << "," << f.pos.y << ")";
}

void upSnake(Snake& s) {				//记录蛇的位置
	for (int i = 0; i < s.len; i++)
		if (i == 0)
			Canvas[s.pos[i].y][s.pos[i].x] = s.camp * 2;
		else
			Canvas[s.pos[i].y][s.pos[i].x] = s.camp * 3;
}

void moveSnake(Snake& s) {			        //蛇移动
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

void isCrash(Snake& s) {				//蛇的碰撞判定
	if (Canvas[s.pos[0].y][s.pos[0].x] == 1 ||
		Canvas[s.pos[0].y][s.pos[0].x] == 3 ||
		Canvas[s.pos[0].y][s.pos[0].x] == 6) {	//撞墙了
		s.hp = 0;
		playing = false;
		gotoxy(8 + (s.camp - 1) * 20, 41);
		if (cout << "你死了";players == 2){
			int temp = s.camp;
			if (temp == 2)
				temp = 0;
			gotoxy(8 + temp * 20, 41);
			cout << "你赢了";
		}
		gotoxy(28, 20);
		cout << "3秒后退出";
	}
	else if (Canvas[s.pos[0].y][s.pos[0].x] == 5) //蛇吃到了食物
		if (s.eat = true;isClient == false)
			createFood(f);
}

void updateWithoutInput() {			//与用户无关的输入
	Canvas[f.pos.y][f.pos.x] = 5;
	for (int i = 0; i < players; i++){
		moveSnake(player[i]);
		isCrash(player[i]);
		upSnake(player[i]);
	}
}

void updateWithInput() {				//与用户有关的输入
	if (_kbhit()) {
		//有按键接受
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

void createFood(Food& f)	{ 		//生成食物
	srand((unsigned int)time(NULL));
	while (true){
		f.pos.x = rand() % WIDTH + 1;
		f.pos.y = rand() % HIGHT + 1;
		if (Canvas[f.pos.y][f.pos.x] == 0)
			break;
	}
}

void createClient(const char* str) {					//创建客户端
	isClient = true;
	if (WSAStartup(MAKEWORD(2, 2), &ws)) MessageBoxA(NULL, "RP太差", "提示", MB_OK);
	memset(&clinetAddr, 0, sizeof(clinetAddr));		//用0填充
	clinetAddr.sin_family = AF_INET;				//ipv4
	clinetAddr.sin_addr.s_addr = inet_addr(str);	//绑定服务器ip地址
	clinetAddr.sin_port = htons(1234);				//绑定1234端口
}

void createServer()					//创建服务器
{
	isServer = true;
	if (WSAStartup(MAKEWORD(2, 2), &ws)) MessageBoxA(NULL, "RP太差", "提示", MB_OK);

	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&serverAddr, 0, sizeof(serverAddr));				//用0填充
	serverAddr.sin_family = AF_INET;							//ipv4
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);			//绑定服务器ip地址
	serverAddr.sin_port = htons(1234);						//绑定1234端口
	bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR));	//绑定服务器套接字

	listen(serverSocket, 10);								//监听套接字

	nsize = sizeof(SOCKADDR);
}