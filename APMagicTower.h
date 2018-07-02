#ifndef APMAGICTOWER_H
#define APMAGICTOWER_H

#include "APInclude.h"
#include "APObject.h"
#include "user.h"
#include "APGui.h"
#include "APPaint.h"
#include "APLib.h"
#include "APWindow.h"

#define BLOCK_WIDTH 32
#define BLOCK_NUM_X 14
#define BLOCK_NUM_Y 12

#define START_HP 500
#define START_ATK 10
#define START_DEF 10


#define MONSTER_NUM 3

#define FLOOR_NUM 2
enum Bmp
{
	Background,
	Wall,
	Monster1,
	Monster2,
	Monster3,
	Valiant,
	YellowDoor,
	BlueDoor,
	RedDoor,
	UpStair,
	DownStair,
	YellowKey,
	BlueKey,
	RedKey,
	SBlood,
	LBlood,
	Attack,
	Defend
};

ABitmap background;
ABitmap wall ;
ABitmap monster1;
ABitmap monster2;
ABitmap monster3 ;
ABitmap valiant;
ABitmap yellowdoor;
ABitmap bluedoor;
ABitmap reddoor;
ABitmap upstair;
ABitmap downstair;
ABitmap yellowkey;
ABitmap bluekey;
ABitmap redkey ;
ABitmap sblood;
ABitmap lblood ;
ABitmap attack;
ABitmap defend ;

int con = 0;
enum Direction
{
	Up,
	Down,
	Left,
	Right
};

enum Status
{
	Play,
	Menu,
	Dead
	
};

int status;

int floor;
APoint position,position_old;
int hp,atk,def;
int my_key[3];
int monster_info[MONSTER_NUM][3] = {{10,20,6},{20,15,8},{40,40,10}};//hp.atk,def
int my_tower[FLOOR_NUM][BLOCK_NUM_X][BLOCK_NUM_Y];



//颜色常量	
void KeyDown(AHwnd hwnd,AMessage msg);

APoint nextpoint(APoint p,int direction);
void TowerInit();
void init(AHwnd hwnd);
bool fight();



void draw(AHwnd hwnd);
void drawone(AHwnd hwnd,int i ,int j );

bool wndProc(AHwnd hwnd,AMessage msg);
#endif
