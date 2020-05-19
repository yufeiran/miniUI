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
//用于读取字体点阵的FILE变量
extern FILE* fp;

//用于显示窗体的全局变量
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
	int nDataSize = 0;//数据大小
	int nImgSize = 0;
	int nWidth = 0;
	int nHeight = 0;
	int nWidthBytes = 0;//每行字节数
	int nBitCount = 0;//每个像素所占比特数
	bool isBackward = true;
	Point centerPoint;

	/*
	按照 BGRA的顺序排列
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
	//	从本地加载图片到内存
	//Paramter: 
	//	char* szPath要加载的图片路径,不对参数合法性进行检查.
	//Return Value:
	//	0  正常
	//	-1 读取信息头错误!
	//	-2 位图文件类型非法biCompression
	//	-3 位图文件打开失败
	//	-4 内存不足
	//	-5 读取数据错误
	//	-6  读取文件头错误!
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
			return pChannelA[0];//不应该出现
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
			return pChannelA[0];//不应该出现
		}
	}
private:
	int _loadImage(char* szPath);
};


//=====================================================================
// 基础的绘制函数
void DrawString(int startX, int startY, const char* word);
void DrawWord(int startX, int startY, char CharToDraw, Color color = Color(255, 255, 255));
void DrawWord(int startX, int startY, char CharToDraw, Picture& pic ,Color color = Color(255, 255, 255));
void DrawRectangle(int x0, int y0, int x1, int y1, Color color = Color(255, 255, 255));
 void DrawPic(int x, int y, Picture* pic);

 void DrawPointOnPicture(int& x, int& y, const Color& color, Picture& pic);


 void GameInit();
 void GameLoop();
 void GameRender();

