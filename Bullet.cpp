#include "hge.h"
#include "hgesprite.h"
#include <iostream>
using namespace std;
extern HGE *hge;

class Bullet
{
	private:
		hgeSprite* sprite;
		HTEXTURE tex;
		float x, y;
		float dx;
		float dy;
		float speed;
		double friction;
		enum direction {LEFT, RIGHT, UP};
		direction d;
		bool state;
	public:
		Bullet()
		{
			x = 0; y = 0;
			d = RIGHT;
			dx = 0; dy = 0;
			speed = 200;
			friction = 0.7;
			sprite = new hgeSprite(0, 7, 7, 7, 7);
			state = false;
		}
		void shoot(float x, float y, int d)
		{
			this->x = x; this->y = y; this->d = (direction)d;
			this->state = true;
			cout << "bang!\n";
		}
		void Update()
		{
			float dt=hge->Timer_GetDelta();
			switch(d)
			{
				case LEFT:
					dx-=speed*dt;
					// Do some movement calculations and collision detection	
					dx*=friction; dy*=friction; x+=dx; y+=dy;
					break;
				case RIGHT:
					dx+=speed*dt;
					// Do some movement calculations and collision detection	
					dx*=friction; dy*=friction; x+=dx; y+=dy;
					break;
				case UP:
					dy-=speed*dt;
					// Do some movement calculations and collision detection	
					dx*=friction; dy*=friction; x+=dx; y+=dy;
					break;
			}
		}
		void Render()
		{
			sprite->Render(x, y);
		}
		bool GetState()
		{
			return state;
		}
		void Reload()
		{
			state = false;
		}
		float GetX()
		{
			return x;
		}
		float GetY()
		{
			return y;
		}
		void LoadTexture()
		{
			tex = hge->Texture_Load("Bullet1.png");
			if(!tex)
			{
				MessageBoxA(NULL, "Can't load one of the following files:\n Bullet.png", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
				hge->System_Shutdown();
				hge->Release();
			}
			sprite->SetTexture(tex);
		}
		void Kill()
		{
			state = false;
		}

};

