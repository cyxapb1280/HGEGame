#include "hge.h"
#include "hgesprite.h"
#include <deque>
#include <time.h>
#include "Bullet.cpp"
using namespace std;

extern HGE *hge;

class Player
{
	private:
		hgeSprite* sprite;
		HTEXTURE tex;
		float x, y;
		float dx, dy;
		float speed, friction;
		int life;
	public:
		deque <Bullet> B;
		Player()
		{
			x = 400; y = 530;
			dx = 0; dy = 0;
			speed = 180;
			friction = 0.7;
			sprite = new hgeSprite(0, 32, 64, 32, 64);
			for(int i = 0; i <9; i++){
				Bullet b;
				B.push_back(b);
			}
			life = 10;
 		}
		void shooting()
		{
			if (hge->Input_GetKeyState(HGEK_LEFT) && hge->Input_KeyDown(HGEK_CTRL)){
				for(int i = 0; i < 9; i++){
					if(!B[i].GetState()){
						B[i].shoot(x, y+13, 0);
						break;
					}
				}
			}
			if (hge->Input_GetKeyState(HGEK_RIGHT) && hge->Input_KeyDown(HGEK_CTRL)){
				for(int i = 0; i < 9; i++){
					if(!B[i].GetState()){
						B[i].shoot(x, y+13, 1);
						break;
					}
				}
			}
			if (hge->Input_GetKeyState(HGEK_UP) && hge->Input_KeyDown(HGEK_CTRL)){
				for(int i = 0; i < 9; i++){
					if(!B[i].GetState()){
						B[i].shoot(x, y+13, 2);
						break;
					}
				}
			}
		}
		void reload()
		{
			if (hge->Input_GetKeyState(HGEK_SHIFT)){
				for(int i = 0; i < 9; i++)
					B[i].Reload();
			}
		}
		void Render()
		{
			if(life>0){
				for(int i = 0; i < 9; i++){
					if(B[i].GetState())
						B[i].Render();
				}
				sprite->Render(x, y);
			}
		}
		void Update()
		{
			float dt=hge->Timer_GetDelta();
			float t = hge->Timer_GetTime();
			// Process keys
			if (hge->Input_GetKeyState(HGEK_LEFT) && !hge->Input_GetKeyState(HGEK_CTRL))
				dx-=speed*dt;
			if (hge->Input_GetKeyState(HGEK_RIGHT) && !hge->Input_GetKeyState(HGEK_CTRL))
				dx+=speed*dt;
			// Do some movement calculations and collision detection	
			dx*=friction; dy*=friction; x+=dx;
			if(x>800) {x=800;dx=0;}
			if(x<0) {x=0;dx=0;}
			shooting();
			reload();
			for(int i = 0; i < 9; i++){
				if(B[i].GetState())
					B[i].Update();
			}
			if(life<0) { x = 0; y = 0;}
		}
		void LoadTexture()
		{
			
			tex = hge->Texture_Load("man1.png");
			if(!tex)
			{
				MessageBoxA(NULL, "Can't load one of the following files:\n Man1.png", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
				hge->System_Shutdown();
				hge->Release();
			}
			sprite->SetTexture(tex);
			for(int i = 0; i < 9; i++)
				B[i].LoadTexture();
		}
		float GetX()
		{
			return x;
		}
		float GetY()
		{
			return y;
		}
		void Kill()
		{
			life--;
		}
};

class Enemy
{
	private:
		hgeSprite* sprite;
		HTEXTURE tex;
		float x, y;
		bool state;
	public:
		deque <Bullet> B;
		Enemy()
		{
			x = 0; y = 0;
			sprite = new hgeSprite(0, 32, 64, 32, 64);
			for(int i = 0; i <9; i++){
				Bullet b;
				B.push_back(b);
			}
			state = true;
 		}
		Enemy(float x, float y)
		{
			this->x = x; this->y = y;
			sprite = new hgeSprite(0, 32, 64, 32, 64);
			for(int i = 0; i <9;i++){
				Bullet b;
				B.push_back(b);
			}
			state = true;
		}
		void LoadTexture()
		{
			tex = hge->Texture_Load("enemy.png");
				if(!tex)
				{
					MessageBoxA(NULL, "Can't load one of the following files:\n enemy.png", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
					hge->System_Shutdown();
					hge->Release();
				}
				sprite->SetTexture(tex);
				for(int i = 0; i < 9; i++)
					B[i].LoadTexture();
		}
		void shooting()
		{
			int t = hge->Timer_GetTime();
			if (t%3 == 0){
				for(int i = 0; i < 9; i++){
					if(!B[i].GetState()){
						B[i].shoot(x, y+13, 0);
						break;
					}
				}
			}
			/*if (hge->Input_GetKeyState(HGEK_RIGHT) && hge->Input_KeyDown(HGEK_CTRL)){
				for(int i = 0; i < 9; i++){
					if(!B[i].GetState()){
						B[i].shoot(x, y, 1);
						break;
					}
				}
			}
			if (hge->Input_GetKeyState(HGEK_UP) && hge->Input_KeyDown(HGEK_CTRL)){
				for(int i = 0; i < 9; i++){
					if(!B[i].GetState()){
						B[i].shoot(x, y, 2);
						break;
					}
				}
			}*/
		}
		void reload()
		{
			if (hge->Input_GetKeyState(HGEK_SHIFT)){
				for(int i = 0; i < 9; i++)
					B[i].Reload();
			}
		}
		void Render()
		{
			if(state){
				for(int i = 0; i < 9; i++){
					if(B[i].GetState())
						B[i].Render();
				}
				sprite->Render(x, y);
			}
		}
		void Update()
		{
			shooting();
			reload();
			for(int i = 0; i < 9; i++){
				if(B[i].GetState())
					B[i].Update();
			}
		}
		float GetX()
		{
			return x;
		}
		float GetY()
		{
			return y;
		}
		void kill()
		{
			state = false;
			x = 0;
			y = 0;
		}
};