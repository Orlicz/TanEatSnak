#pragma once

#include <iostream>
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#include <time.h>


#pragma comment(lib, "ws2_32.lib")

#define	HIGHT 40
#define	WIDTH 40
#define SNAKESIZE 100

using std::cin;
using std::cout;
using std::endl;

struct Position{
	int x;
	int y;
};

struct Snake{
	Position pos[SNAKESIZE];
	int len;
	int camp;
	char move;
	int hp;
	bool eat;
};

struct Food{
	Position pos;
};

extern bool playing;
extern int players;
extern int Canvas[HIGHT][WIDTH];
extern Food f;						//食物坐标
extern Snake player[2];				//玩家数组

extern WSADATA ws;
extern SOCKET serverSocket;			//服务器套接字
extern SOCKET server_client_Socket;	//服务器响应客户端生成的套接字
extern sockaddr_in  serverAddr;		//服务器套接字地址
extern SOCKADDR server_client_addr;	//服务器接收的客户端套接字地址
extern int nsize;					//套接字地址大小
extern bool isServer;				//是否是服务器
extern bool isClient;				//是否是客户端

extern sockaddr_in  clinetAddr;		//客户端套接字地址
extern SOCKET clientSocket;			//客户端套接字

void startMenu();					//开始菜单
void multiplayerMenu();				//多人菜单
void helpMenu();					//帮助页面
void gotoxy(int x, int y);			//设置光标位置
void selectBox(int x, int y);		//显示选中框
void cleanSelectBox(int x, int y);	//清除选中框
char keydown();						//获取按键
void initialized();					//数据初始化
void show();						//显示画面
void upSnake(Snake& s);			//记录蛇的位置
void moveSnake(Snake& s);			//蛇移动
void isCrash(Snake& s);			//蛇的碰撞判定
void updateWithoutInput();			//与用户无关的输入
void updateWithInput();				//与用户有关的输入
void createFood(Food& f);			//生成食物

void createServer();				//创建服务器
void createClient(const char* str);//创建客户端
