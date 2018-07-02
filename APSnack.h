#ifndef APSNACK_H
#define APSNACK_H

#include "APInclude.h"
#include "APObject.h"
#include "user.h"
#include "APGui.h"
#include "APPaint.h"
#include "APLib.h"
#include "APWindow.h"

enum Direction
{
	NoDir,
	Up,
	Down,
	Left,
	Right
};

enum Status
{
	Run,
	Pause,
	Dead
};

int status;

#define BLOCK_WIDTH 10
#define BLOCK_NUM_X 80
#define BLOCK_NUM_Y 55

#define COLOR_BACK RGB(0,255,0)
#define COLOR_HEAD RGB(0,128,0)
#define COLOR_BODY RGB(0,255,255)
#define COLOR_FOOD RGB(255,0,0)
//颜色常量

int my_block[BLOCK_NUM_X][BLOCK_NUM_Y];//0->background;UP,Down,Left,RIGHT->direction;
bool my_food[BLOCK_NUM_X][BLOCK_NUM_Y];//0->no food

APoint head,tail;

int current_direction, current_direction_copy;

APoint nextpoint(APoint p,int direction);


void Move();
void init(AHwnd hwnd);
void timerUpdate(AHwnd hwnd);

void keyDown(AHwnd hwnd,AMessage msg);

void draw(AHwnd hwnd);
bool wndProc(AHwnd hwnd,AMessage msg);




bool Is_Dead(AHwnd hwnd);

bool updateFood();

#endif
