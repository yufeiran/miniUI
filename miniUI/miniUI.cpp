#include"miniUI.h"
#include"window.h"

void UIManager::UILoop()
{
	if (isClick == true)
	{
		for (int i = 0; i < uiVector.size(); i++)
		{
			if (uiVector[i].x <= ClickX && uiVector[i].x + uiVector[i].width>=ClickX
				&& uiVector[i].y<=ClickY && uiVector[i].y + uiVector[i].height >= ClickY)
			{
				uiVector[i].fun();
				break;
			}
		}
		isClick = false;
	}

}

void UIManager::OnClickPos(int x, int y)
{
	isClick = true;
	ClickX = x;
	ClickY = y;
}

void UIManager::AddUI(UI& ui)
{
	uiVector.push_back(ui);

}

void UIManager::DrawUI()
{
	for (int i = 0; i < uiVector.size(); i++)
	{
		DrawPic(uiVector[i].x, uiVector[i].y, uiVector[i].pic0);
	}
}

int  UI::getWidth()
{
	return pic0->nWidth;
}

int UI::getHeight()
{

	return pic0->nHeight;
}

void UI::WordToPic0()
{
	int charWidth = 8;
	int charHeight = 16;
	int size = charWidth * charHeight;
	pic0 = new Picture;
	pic0->pChannelR = new BYTE[size]; 
	pic0->pChannelG = new BYTE[size];
	pic0->pChannelB = new BYTE[size];
	pic0->pChannelA = new BYTE[size];
	pic0->nWidth = charWidth;
	pic0->nHeight = charHeight;
	DrawWord(0, 0, title[0], *pic0,Color(0,0,0));


}
