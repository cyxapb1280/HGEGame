#define _CRT_SECURE_NO_WARNINGS
#include "hge.h"
#include "hgesprite.h"
#include "Player.cpp"




HGE *hge = 0; //��������� �� ������ � ����


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
bool Update() //���, ����������� ������ �����(����)
{
	if (hge->Input_GetKeyState(HGEK_ESCAPE))
		return true; //���� ���������� � �e����� update true, �� ���� ����������
	pl.Update();
	E.Update();
	hits();
	return false;//������� false =)
}
bool Render() //������(����� �� �����)
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
	hge->System_SetState(HGE_FRAMEFUNC, Update); //���������, ����� ������� �������� �� ������
	hge->System_SetState(HGE_RENDERFUNC, Render); //� ����� �� ����� �� �����
	hge->System_SetState(HGE_TITLE, "HGE Game"); //������ ��������� ����
	hge->System_SetState(HGE_WINDOWED, true); //������� ����� ���/����
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	if(hge->System_Initiate()) //���� ��� ���������������� ���������
	{
		LoadTextures();
		hge->System_Start(); //������� ���� �� ������
	}
	else
	{	
		MessageBoxA(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}
	hge->System_Shutdown(); //��������� �������
	hge->Release(); //������� �����

	return 0;
}

