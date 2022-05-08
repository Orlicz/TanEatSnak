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
extern Food f;						//ʳ������
extern Snake player[2];				//�������

extern WSADATA ws;
extern SOCKET serverSocket;			//�������׽���
extern SOCKET server_client_Socket;	//��������Ӧ�ͻ������ɵ��׽���
extern sockaddr_in  serverAddr;		//�������׽��ֵ�ַ
extern SOCKADDR server_client_addr;	//���������յĿͻ����׽��ֵ�ַ
extern int nsize;					//�׽��ֵ�ַ��С
extern bool isServer;				//�Ƿ��Ƿ�����
extern bool isClient;				//�Ƿ��ǿͻ���

extern sockaddr_in  clinetAddr;		//�ͻ����׽��ֵ�ַ
extern SOCKET clientSocket;			//�ͻ����׽���

void startMenu();					//��ʼ�˵�
void multiplayerMenu();				//���˲˵�
void helpMenu();					//����ҳ��
void gotoxy(int x, int y);			//���ù��λ��
void selectBox(int x, int y);		//��ʾѡ�п�
void cleanSelectBox(int x, int y);	//���ѡ�п�
char keydown();						//��ȡ����
void initialized();					//���ݳ�ʼ��
void show();						//��ʾ����
void upSnake(Snake& s);			//��¼�ߵ�λ��
void moveSnake(Snake& s);			//���ƶ�
void isCrash(Snake& s);			//�ߵ���ײ�ж�
void updateWithoutInput();			//���û��޹ص�����
void updateWithInput();				//���û��йص�����
void createFood(Food& f);			//����ʳ��

void createServer();				//����������
void createClient(const char* str);//�����ͻ���
