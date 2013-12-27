#define _CRT_SECURE_NO_WARNINGS
#include "hge.h"
#include "hgesprite.h"
#include "Player.cpp"




HGE *hge = 0; //указатель на версию и ядро


Player pl;
Enemy E(500, 530);

void hits()
{
	for(int i = 0; i < 9; i++)
	{
		if((pl.B[i].GetX() < E.GetX() + 16) && (pl.B[i].GetX() > E.GetX() - 16)){
			E.kill();
			pl.B[i].Kill();
		}
		if((E.B[i].GetX() < pl.GetX() + 16) && (E.B[i].GetX() > pl.GetX() - 16)){
			pl.Kill();
			E.B[i].Kill();
		}
	}

}
bool Update() //Код, выполняемый каждый фрейм(кадр)
{
	if (hge->Input_GetKeyState(HGEK_ESCAPE))
		return true; //Если возвратить в фeнкции update true, то игра завершится
	pl.Update();
	E.Update();
	hits();
	return false;//поэтому false =)
}
bool Render() //Рендер(вывод на экран)
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	pl.Render();
	E.Render();
	hge->Gfx_EndScene();
        return false;
}
void LoadTextures()
{
	pl.LoadTexture();
	E.LoadTexture();
}

int main()
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_FRAMEFUNC, Update); //Указываем, какая функция отвечает за фреймы
	hge->System_SetState(HGE_RENDERFUNC, Render); //А какая за вывод на экран
	hge->System_SetState(HGE_TITLE, "HGE Game"); //Задаем заголовок окна
	hge->System_SetState(HGE_WINDOWED, true); //Оконный режим вкл/выкл
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	if(hge->System_Initiate()) //Если все инициализировано правильно
	{
		LoadTextures();
		hge->System_Start(); //потекла моча по трубам
	}
	else
	{	
		MessageBoxA(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}
	hge->System_Shutdown(); //выгружаем ресурсы
	hge->Release(); //ложимся спать

	return 0;
}

