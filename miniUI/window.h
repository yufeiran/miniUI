#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<iostream>
#include<tchar.h>
#include<fstream>
#include<random>
#include<time.h>
#include<string>
#include<WinUser.h>
#include<windowsx.h> //GET_X_LPARAM

using namespace std;
//���ڶ�ȡ��������FILE����
extern FILE* fp;

//������ʾ�����ȫ�ֱ���
//----------------------------------
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int bits = 24;
extern BYTE buffer[SCREEN_WIDTH * SCREEN_HEIGHT * bits / 8];



class Color
{
public:
	Color(int R, int G, int B,int A=0) :r(R), g(G), b(B) ,a(A){};
	Color() :r(255), g(255), b(255) {};
	int r, g, b,a;
};

void GameLoop();

void CleanScreen();
void DrawPoint(int& x, int& y, const Color& color = Color(255, 255, 255));


void PutBufferToScreen();

void initWindow();

extern HDC screen_hdc;
extern HDC hCompatibleDC;
extern HBITMAP hCompatibleBitmap;
extern HBITMAP hOldBitmap;
extern BITMAPINFO binfo;

extern HINSTANCE hInstance;
extern WNDCLASS Draw;
extern HWND hwnd;
extern MSG msg;




struct Point {
	int x;
	int y;
	Point(int tx = 0, int ty = 0) {
		x = tx;
		y = ty;
	}
};

class Picture {
public:
	int nErrorCode = 0;
	int nDataSize = 0;//���ݴ�С
	int nImgSize = 0;
	int nWidth = 0;
	int nHeight = 0;
	int nWidthBytes = 0;//ÿ���ֽ���
	int nBitCount = 0;//ÿ��������ռ������
	bool isBackward = true;
	Point centerPoint;

	/*
	���� BGRA��˳������
	*/
	//BYTE* pData = NULL;
	RGBQUAD* pColorPal = NULL;

	BYTE* pChannelR = NULL;
	BYTE* pChannelG = NULL;
	BYTE* pChannelB = NULL;
	BYTE* pChannelA = NULL;

	Picture() {
		;
	}
	Picture(const char* szPath) {
		loadImage((char*)szPath);
	}
	Picture(char* szPath) {
		loadImage(szPath);
	}
	~Picture() {
		delete[] pChannelR;
		pChannelR = NULL;
		delete[] pChannelG;
		pChannelG = NULL;
		delete[] pChannelB;
		pChannelB = NULL;
		delete[] pChannelA;
		pChannelA = NULL;
		//delete[] pData;
		//pData = NULL;
		delete[] pColorPal;
		pColorPal = NULL;
	}

	//Description:
	//	�ӱ��ؼ���ͼƬ���ڴ�
	//Paramter: 
	//	char* szPathҪ���ص�ͼƬ·��,���Բ����Ϸ��Խ��м��.
	//Return Value:
	//	0  ����
	//	-1 ��ȡ��Ϣͷ����!
	//	-2 λͼ�ļ����ͷǷ�biCompression
	//	-3 λͼ�ļ���ʧ��
	//	-4 �ڴ治��
	//	-5 ��ȡ���ݴ���
	//	-6  ��ȡ�ļ�ͷ����!
	int loadImage(const char* szPath) {
		return _loadImage((char*)szPath);
	}

	int getWidth() {
		return nWidth;
	}
	int getHeight() {
		return nHeight;
	}
	int getBitsPixel() {
		return nBitCount;
	}
	int getWidthBytes() {
		return nWidthBytes;
	}
	int getErrorCode() {
		return nErrorCode;
	}

	bool isIncludeAlpha() {
		return pChannelA != NULL;
	}

#define Ch_R 0
#define Ch_G 1
#define Ch_B 2
#define Ch_A 3
	BYTE& operator()(int nPos, int Channel) {
		switch (Channel) {
		case Ch_R: {
			return pChannelR[nPos];
		}
		case Ch_G: {
			return pChannelG[nPos];
		}
		case Ch_B: {
			return pChannelB[nPos];
		}
		case Ch_A: {
			return pChannelA[nPos];
		}
		default:
			return pChannelA[0];//��Ӧ�ó���
		}
	}
	BYTE& operator()(int row, int column, int Channel) {
		switch (Channel) {
		case Ch_R: {
			return pChannelR[row * nWidth + column];
		}
		case Ch_G: {
			return pChannelG[row * nWidth + column];
		}
		case Ch_B: {
			return pChannelB[row * nWidth + column];
		}
		case Ch_A: {
			return pChannelA[row * nWidth + column];
		}
		default:
			return pChannelA[0];//��Ӧ�ó���
		}
	}
private:
	int _loadImage(char* szPath);
};


//=====================================================================
// �����Ļ��ƺ���
void DrawString(int startX, int startY, const char* word);
void DrawWord(int startX, int startY, char CharToDraw, Color color = Color(255, 255, 255));
void DrawWord(int startX, int startY, char CharToDraw, Picture& pic ,Color color = Color(255, 255, 255));
void DrawRectangle(int x0, int y0, int x1, int y1, Color color = Color(255, 255, 255));
 void DrawPic(int x, int y, Picture* pic);

 void DrawPointOnPicture(int& x, int& y, const Color& color, Picture& pic);


 void GameInit();
 void GameLoop();
 void GameRender();

