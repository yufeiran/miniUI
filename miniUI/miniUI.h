#pragma once
#include<vector>
#include"window.h"


class UI
{
public:
	int x;
	int y;
	int width;
	int height;
	int  getWidth();
	int getHeight();
	string title;
	bool isInputBox = false;
	bool isOnFoucus = false;
	Picture* pic0;
	void (* fun)(void);
	void WordToPic0();
};

class UIManager
{
public:
	void UILoop();

	void OnClickPos();
	void MousePos(int x, int y);
	void OnKeyPress(int keyValue);
	void AddUI(UI& ui);
	void DrawUI();

	std::vector<UI>uiVector;
	bool isClick = false;
	bool isKeyPress = false;
	

	int KeyPressValue = 0;

	int ClickX = 0;
	int ClickY = 0;
};

extern UIManager uiManager;