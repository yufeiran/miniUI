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
	int charWidth = 8 * this->title.size();
	int charHeight = 16;
	int size = charWidth * charHeight;

	if (pic0 == NULL)
	{
		pic0 = new Picture;
		pic0->pChannelR = new BYTE[size];
		pic0->pChannelG = new BYTE[size];
		pic0->pChannelB = new BYTE[size];
		pic0->pChannelA = new BYTE[size];
		pic0->nWidth = charWidth;
		pic0->nHeight = charHeight;

	}
	for (int i = 0; i < sizeof(pic0->pChannelR); i++)
	{
		
	}
	for (int i = 0; i < this->pic0->getHeight(); i++)
	{
		for (int j = 0; j < this->pic0->getWidth(); j++)
		{
			DrawPointOnPicture(j, i,  Color(255, 255, 255), *pic0);
		}
	}

	for (int i = 0; i < title.size(); i++)
	{
		DrawWord(i*8, 0, title[i], *pic0, Color(0, 0, 0));
	}

}
