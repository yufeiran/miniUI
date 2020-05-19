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
				if (uiVector[i].fun != NULL)
				{
					uiVector[i].fun();
				}
				uiVector[i].isOnFoucus = true;
			}
			else
			{
				uiVector[i].isOnFoucus = false;
			}
		}
		isClick = false;
	}
	if (isKeyPress == true)
	{
		for (int i = 0; i < uiVector.size(); i++)
		{
			if (uiVector[i].isInputBox == true&&uiVector[i].isOnFoucus==true)
			{
				if (KeyPressValue == 8)
				{
					if (uiVector[i].title.size() > 0)
					{
						uiVector[i].title.pop_back();

					}
					uiVector[i].WordToPic0();

				}
				else if(isalnum(KeyPressValue)!=0)
				{
					uiVector[i].title.push_back(KeyPressValue);
					uiVector[i].WordToPic0();
				}

			}
			
		}
		isKeyPress = false;
	}
}

void UIManager::OnClickPos()
{
	isClick = true;

}

void UIManager::MousePos(int x, int y)
{
	this->ClickX = x;
	this->ClickY = y;
}

void UIManager::OnKeyPress(int keyValue)
{
	isKeyPress = true;
	KeyPressValue = keyValue;
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
	if (pic0 == NULL||pic0->nWidth*pic0->nHeight<size)
	{
		if (pic0 != NULL)
		{
			delete pic0;
		}
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
