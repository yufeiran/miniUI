#include"window.h"
#include"miniUI.h"

FILE* fp;

void DrawPointOnPicture(int& x, int& y, const Color& color,Picture &pic)
{
	int pos = y * pic.nWidth + x;
	pic.pChannelR[pos]= color.r;
	pic.pChannelG[pos] = color.g;
	pic.pChannelB[pos] = color.b;
	pic.pChannelA[pos] = color.a;


}

void DrawPoint(int &x, int &y, const Color &color)
{
	if (x <= 0 || x >= SCREEN_WIDTH)return;
	if (y <= 0 || y >= SCREEN_HEIGHT)return;

	buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 1] = color.r;
	buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 2] = color.g;
	buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 3] = color.b;
}

void DrawLine(int x1, int y1, int x2, int y2, Color color = Color(255, 255, 255))
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int ux = ((dx > 0) << 1) - 1;
	int uy = ((dy > 0) << 1) - 1;
	int x = x1, y = y1, eps;

	eps = 0; dx = abs(dx); dy = abs(dy);

	if (dx > dy)
	{
		for (x = x1; x != x2; x += ux)
		{

			DrawPoint(x, y, color);
			eps += dy;
			if ((eps << 1) >= dx)
			{
				y += uy; eps -= dx;
			}
		}

	}
	else
	{
		for (y = y1; y != y2; y += uy)
		{
			DrawPoint(x, y, color);
			eps += dx;
			if ((eps << 1) >= dy)
			{
				x += ux; eps -= dy;
			}
		}
	}
}

void DrawRectangle(int x0, int y0, int x1, int y1, Color color)
{
	int minY = min(y0, y1);
	int maxY = max(y0, y1);
	int minX = min(x0, x1);
	int maxX = max(x0, x1);
	for (int y = minY; y < maxY; y++)
	{
		for (int x = minX; x < maxX; x++)
		{
			DrawPoint(x, y, color);
		}
	}
}


void DrawWord(int startX, int startY, char CharToDraw, Color color)
{
	int START = 0x20;
	int DATANUM = 16;
	int location = (CharToDraw - START) * DATANUM;

	int x = startY;  //由于储存数据方式问题，这里需要颠倒
	int y = startX;

	int i = 0;
	int buf = 0;

	fseek(fp, location, SEEK_SET);

	int DataX, DataY, DrawX, DrawY;
	for (int i = 0; i < 16; i++)
	{

		buf = fgetc(fp);
		//显示一个字节
		for (int j = 0; j < 8; j++)
		{
			if (buf % 2 == 1)
			{

				if (i < 8)
				{
					DataX = x + j;
					DataY = y + i;
				}
				else
				{
					DataX = x + j + 8;
					DataY = y + i - 8;
				}
				DrawX = DataY;
				DrawY = DataX;
				DrawPoint(DrawX, DrawY, color);
			}
			buf = buf / 2;
		}
	}
}

void DrawWord(int startX, int startY, char CharToDraw, Picture& pic, Color color )
{
	int START = 0x20;
	int DATANUM = 16;
	int location = (CharToDraw - START) * DATANUM;

	int x = startY;  //由于储存数据方式问题，这里需要颠倒
	int y = startX;

	int i = 0;
	int buf = 0;

	fseek(fp, location, SEEK_SET);

	int DataX, DataY, DrawX, DrawY;
	for (int i = 0; i < 16; i++)
	{

		buf = fgetc(fp);
		//显示一个字节
		for (int j = 0; j < 8; j++)
		{
			if (buf % 2 == 1)
			{

				if (i < 8)
				{
					DataX = x + j;
					DataY = y + i;
				}
				else
				{
					DataX = x + j + 8;
					DataY = y + i - 8;
				}
				DrawX = DataY;
				DrawY = DataX;
				DrawPointOnPicture(DrawX, DrawY, color,pic);
			}
			buf = buf / 2;
		}
	}
}

void DrawString(int startX, int startY, const char* word)
{
	if (word == NULL)
	{
		return;
	}
	int len = strlen(word);
	for (int i = 0; i < len; i++)
	{
		DrawWord(startX + i * 8, startY, word[i]);
	}

}


void DrawCircle(int x, int y, int r, Color color = Color(255, 255, 255))
{
	for (int ny = y - r; ny < y + r; ny++)
	{
		for (int nx = x - r; nx < x + r; nx++)
		{
			float d = sqrt((ny - y) * (ny - y) + (nx - x) * (nx - x));
			if (d < r)
			{
				DrawPoint(nx, ny, color);
			}
		}
	}
}

//===================================================================



void CleanScreen()
{
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{

			buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 1] = 139;
			buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 2] = 129;
			buffer[int(y) * SCREEN_WIDTH * 3 + (int(x) + 1) * 3 - 3] = 195;
		}
	}
}



BYTE buffer[SCREEN_WIDTH * SCREEN_HEIGHT * bits / 8];

HDC screen_hdc;
HDC hCompatibleDC;
HBITMAP hCompatibleBitmap;
HBITMAP hOldBitmap;
BITMAPINFO binfo;

HINSTANCE hInstance;
WNDCLASS Draw;
HWND hwnd;
MSG msg;


LRESULT CALLBACK WindowProc(
	_In_	HWND hwnd,
	_In_	UINT uMsg,
	_In_	WPARAM wParam,
	_In_	LPARAM lParam
)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN:
	{
		uiManager.OnKeyPress(wParam);
		if (wParam == VK_ESCAPE)
			exit(0);
		if (wParam == VK_RETURN)
		{
		
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		std::cout << "Key Press" << std::endl;
		uiManager.MousePos(x, y);
		uiManager.OnClickPos();
		break;
	}
	case WM_MOUSEMOVE:
	{

		
	}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void PutBufferToScreen()
{
	SetDIBits(screen_hdc, hCompatibleBitmap, 0, SCREEN_HEIGHT, buffer, (BITMAPINFO*)&binfo, DIB_RGB_COLORS);
	BitBlt(screen_hdc, -1, -1, SCREEN_WIDTH, SCREEN_HEIGHT, hCompatibleDC, 0, 0, SRCCOPY);
}

void initWindow()
{
	hInstance = GetModuleHandle(NULL);

	Draw.cbClsExtra = 0;
	Draw.cbWndExtra = 0;
	Draw.hCursor = LoadCursor(hInstance, IDC_ARROW);
	Draw.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	Draw.lpszMenuName = NULL;
	Draw.style = WS_MINIMIZEBOX | CS_HREDRAW | CS_VREDRAW;
	Draw.hbrBackground = (HBRUSH)COLOR_WINDOW;
	Draw.lpfnWndProc = WindowProc;
	Draw.lpszClassName = L"DDraw";
	Draw.hInstance = hInstance;

	RegisterClass(&Draw);

	hwnd = CreateWindow(
		L"DDraw",
		L"Draw",
		WS_OVERLAPPEDWINDOW,
		38,
		20,
		SCREEN_WIDTH + 15,
		SCREEN_HEIGHT + 38,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	//init bitbuffer
	ZeroMemory(&binfo, sizeof(BITMAPINFO));
	binfo.bmiHeader.biBitCount = bits;
	binfo.bmiHeader.biCompression = BI_RGB;
	binfo.bmiHeader.biHeight = -SCREEN_HEIGHT;
	binfo.bmiHeader.biPlanes = 1;
	binfo.bmiHeader.biSizeImage = 0;
	binfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	binfo.bmiHeader.biWidth = SCREEN_WIDTH;

	screen_hdc = GetDC(hwnd);
	hCompatibleDC = CreateCompatibleDC(screen_hdc);
	hCompatibleBitmap = CreateCompatibleBitmap(screen_hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hCompatibleBitmap);
}


int Picture::_loadImage(char* szPath) {
	/*
	if (hImage != NULL) {
		DeleteObject(hImage);
	}
	//从文件加载位图
	hImage = (HBITMAP)LoadImage(0, szPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//读取属性
	GetObject(hImage, sizeof(BITMAP), &bm);*/

	FILE* fp = fopen(szPath, "rb");
	if (fp == NULL) {
		nErrorCode = -3;
		return nErrorCode;
	}
	BITMAPFILEHEADER fileHeader;
	if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp) != 1) {
		fclose(fp);
		nErrorCode = -6;
		return nErrorCode;
	}
	BITMAPINFOHEADER infoHeader;
	if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp) != 1) {
		fclose(fp);
		nErrorCode = -1;
		return nErrorCode;
	}

	nWidth = infoHeader.biWidth;
	if (infoHeader.biHeight < 0) {
		//正向
		isBackward = false;
		nHeight = -infoHeader.biHeight;
	}
	else {
		//倒向
		isBackward = true;
		nHeight = infoHeader.biHeight;
	}
	//计算图像中心点
	centerPoint.x = nWidth / 2;
	centerPoint.y = nHeight / 2;

	nBitCount = infoHeader.biBitCount;

	nImgSize = nWidth * nHeight;

	nWidthBytes = (((nWidth * nBitCount) + 31) >> 5) << 2;

	switch (infoHeader.biCompression) {
	case BI_RGB: {
		//不压缩
		if (nBitCount == 24) {
			pChannelR = new BYTE[nImgSize];
			pChannelG = new BYTE[nImgSize];
			pChannelB = new BYTE[nImgSize];
			//pChannelA = new BYTE[nImgSize];
			if (pChannelR == NULL || pChannelG == NULL || pChannelB == NULL /*|| pChannelA==NULL*/) {
				fclose(fp);
				nErrorCode = -4;
				return nErrorCode;
			}
			if (isBackward) {
				//倒立
				for (int i = nHeight - 1; i >= 0; --i) {
					for (int j = 0; j < nWidth; ++j) {
						if (fread(&pChannelB[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelG[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelR[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
					}
					fseek(fp, nWidthBytes - nWidth * nBitCount / 8, SEEK_CUR);
				}
			}
			else {
				for (int i = 0; i < nHeight; ++i) {
					for (int j = 0; j < nWidth; ++j) {
						if (fread(&pChannelB[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelG[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelR[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
					}
					fseek(fp, nWidthBytes - nWidth * nBitCount / 8, SEEK_CUR);
				}
			}
		}
		else {
			//32bit
			pChannelR = new BYTE[nImgSize];
			pChannelG = new BYTE[nImgSize];
			pChannelB = new BYTE[nImgSize];
			pChannelA = new BYTE[nImgSize];
			if (pChannelR == NULL || pChannelG == NULL || pChannelB == NULL || pChannelA == NULL) {
				fclose(fp);
				nErrorCode = -4;
				return nErrorCode;
			}
			if (isBackward) {
				//倒立
				for (int i = nHeight - 1; i >= 0; --i) {
					for (int j = 0; j < nWidth; ++j) {
						if (fread(&pChannelB[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelG[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelR[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelA[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
					}
					fseek(fp, nWidthBytes - nWidth * nBitCount / 8, SEEK_CUR);
				}
			}
			else {
				for (int i = 0; i < nHeight; ++i) {
					for (int j = 0; j < nWidth; ++j) {
						if (fread(&pChannelB[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelG[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelR[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelA[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
					}
					fseek(fp, nWidthBytes - nWidth * nBitCount / 8, SEEK_CUR);
				}
			}
		}
		break;
	}
	case BI_RLE8: {
		//8bit rle压缩
		//infoHeader.biBitCount=8
		break;
	}
	case BI_RLE4: {
		//4bit rle压缩
		//infoHeader.biBitCount=4
		break;
	}
	case BI_BITFIELDS: {
		//比特域用于16/32位
		if (nBitCount == 32) {
			//32bit B8 G8 R8 A8
			pChannelR = new BYTE[nImgSize];
			pChannelG = new BYTE[nImgSize];
			pChannelB = new BYTE[nImgSize];
			pChannelA = new BYTE[nImgSize];
			if (pChannelR == NULL || pChannelG == NULL || pChannelB == NULL || pChannelA == NULL) {
				fclose(fp);
				nErrorCode = -4;
				return nErrorCode;
			}
			if (isBackward) {
				//倒立
				for (int i = nHeight - 1; i >= 0; --i) {
					for (int j = 0; j < nWidth; ++j) {
						if (fread(&pChannelB[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelG[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelR[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelA[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
					}
					fseek(fp, nWidthBytes - nWidth * nBitCount / 8, SEEK_CUR);
				}
			}
			else {
				for (int i = 0; i < nHeight; ++i) {
					for (int j = 0; j < nWidth; ++j) {
						if (fread(&pChannelB[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelG[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelR[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
						if (fread(&pChannelA[i * nWidth + j], sizeof(BYTE), 1, fp) != 1) {
							nErrorCode = -5;
							return nErrorCode;
						}
					}
					fseek(fp, nWidthBytes - nWidth * nBitCount / 8, SEEK_CUR);
				}
			}
		}

		break;
	}
	case BI_JPEG: {
		//包含jpeg图像
		break;
	}
	case BI_PNG: {
		//包含png图像
		break;
	}
	default: {
		nErrorCode = -2;
		return nErrorCode;
	}
	}//end switch


	fclose(fp);
	nErrorCode = 0;
	return nErrorCode;
}


int main()
{
	clock_t start, finish;

	initWindow();
	SetWindowText(hwnd, _T("七桥问题"));
	fp = fopen("ascii_zk.bin", "r");

	GameInit();
	int frame = 0;
	start = clock();
	while (1)
	{
		finish = clock();
		GameLoop();
		GameRender();
		if (finish - start >= 1000)
		{
			start = finish;
			char strFps[10];
			sprintf(strFps, "FPS %d", frame);
			SetWindowTextA(hwnd, (strFps));
			frame = 0;
		}

		frame++;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}

	fclose(fp);

	return 0;
}


//uncheck
inline void DrawPicA(int x, int y, Picture* pic, RECT rect) {
	int xBuffer = 0, yBuffer = 0;
	int xPic, yPic;
	int NowDrawX, NowDrawY;

	for (yPic = rect.top; yPic < rect.bottom; ++yPic) {
		int posBuffer = (SCREEN_WIDTH * (y + yBuffer++) + x) * 4;
		for (xPic = rect.left; xPic < rect.right; ++xPic) {
			NowDrawX = x + xPic;
			NowDrawY = y + yPic;
			int posPic = pic->getWidth() * yPic + xPic;
			Color(1, 2, 3, 4);
			
			DrawPoint(NowDrawX, NowDrawY,Color(pic->pChannelR[posPic], pic->pChannelG[posPic], pic->pChannelB[posPic], pic->pChannelA[posPic]));

			posBuffer += 4;
			++posPic;
		}
	}
}

void DrawPic(int x, int y, Picture* pic) {
	RECT rect;
	int _x, _y;
	//纵向检查
	if ((y + pic->getHeight()) < 0) {
		//完全超出上边界
		//不绘制
		return;
	}
	else if (y < 0) {
		//部分超出上边界
		rect.top = -y;
		rect.bottom = pic->getHeight();
		//_x = x;
		_y = 0;
	}
	else if ((y + pic->getHeight()) < SCREEN_HEIGHT) {
		//完全在窗口内
		rect.top = 0;
		rect.bottom = pic->getHeight();
		//_x = x;
		_y = y;
	}
	else if (y < SCREEN_HEIGHT) {
		//部分超出下边界
		rect.top = 0;
		rect.bottom = SCREEN_HEIGHT - y;
		//_x = x;
		_y = y;
	}
	else {
		//完全超出下边界
		//不绘制
		return;
	}

	//横向检查
	if ((x + pic->getWidth()) < 0) {
		//完全超出左边界
		//不绘制
		return;
	}
	else if (x < 0) {
		//部分超出左边界
		rect.left = -x;
		rect.right = pic->getWidth();
		_x = 0;
		//_y = y;
	}
	else if ((x + pic->getWidth()) < SCREEN_WIDTH) {
		//完全在窗口内
		rect.left = 0;
		rect.right = pic->getWidth();
		_x = x;
		//_y = y;
	}
	else if (x < SCREEN_WIDTH) {
		//部分超出右边界
		rect.left = 0;
		rect.right = SCREEN_WIDTH - x;
		_x = x;
		//_y = y;
	}
	else {
		//完全超出下边界
		//不绘制
		return;
	}
	if (pic->isIncludeAlpha()) {
		DrawPicA(_x, _y, pic, rect);
	}
	

}