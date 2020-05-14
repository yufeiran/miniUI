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
	
	Picture* pic0;
	void (* fun)(void);
	void WordToPic0();
};

class UIManager
{
public:
	void UILoop();

	void OnClickPos(int x, int y);
	void AddUI(UI& ui);
	void DrawUI();

	std::vector<UI>uiVector;
	bool isClick = false;
	int ClickX = 0;
	int ClickY = 0;
};

extern UIManager uiManager;