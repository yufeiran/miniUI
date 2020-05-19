#include"window.h"
#include"miniUI.h"

UIManager uiManager;

Picture picL;
Picture picA;

UI ui0;
UI ui1;


void fun1()
{
	std::cout << "fun1" << std::endl;
}
void fun2()
{
	std::cout << "fun2" << std::endl;
	ui1.title = "23";
	ui1.WordToPic0();
}

void GameInit()
{

	picL.loadImage("L.bmp");
	ui0.x = 10;
	ui0.y = 20;
	ui0.width = picL.nWidth;
	ui0.height =picL.nHeight;
	ui0.pic0 = &picL;
	ui0.fun = fun1;

	//uiManager.AddUI(ui0);

	
	ui1.x = 500;
	ui1.y = 500;
	ui1.width = 100;
	ui1.height = 100;
	ui1.title = "Button1";
	ui1.WordToPic0();
	ui1.fun = fun2;
	uiManager.AddUI(ui1);
	

}


//ÓÎÏ·Âß¼­Ñ­»·
void GameLoop()
{
	uiManager.UILoop();
	
}

//ÓÎÏ·äÖÈ¾Ñ­»·
void GameRender()
{
	CleanScreen();

	DrawRectangle(0, 500, SCREEN_WIDTH, SCREEN_HEIGHT, Color(83, 61, 91));
	uiManager.DrawUI();


	int startX = 150;
	int startY = SCREEN_HEIGHT - 80;
	char TempMsg2[20];

	sprintf(TempMsg2, "Bridge: ");
	DrawString(startX, startY, TempMsg2);
	startX += 70;


	char TempMsg[40];
	sprintf(TempMsg, "[Enter] next step [Esc] exit");
	DrawString(150, SCREEN_HEIGHT - 40, TempMsg);

	PutBufferToScreen();
}
