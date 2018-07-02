#ifndef APINCLUDE_H
#define APINCLUDE_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define MAX_DC_HEIGHT 1600

#define MAX_TIMER_NUM 10
#define MESSAGE_QUEUE_SIZE 64
#define MAX_WND_NUM 10
#define MAX_WND_TITLE_LENGTH 20

#define WND_TITLE_HEIGHT 50

#define GRID_WIDTH 50
#define GRID_W_NUMBER   16
#define GRID_H_NUMBER   11

#define DEFAULT_WINDOW_COLOR 0xffffff
#define DEFAULT_TITLE_COLOR 0x0000ff

enum GRID {
   //basic element
   GRID_WALL,
   GRID_ROAD,
   GRID_GRASS,
   GRID_RIVER,
   GRID_FOREST,
   GRID_STONE,
   GRID_MOUNTAIN,
   GRID_LAKE,
    
   //control level icon
   GRID_UP_1,
   GRID_DOWN_1,
    
   //program icon
   GRID_PROGRAM_SNAKE,
   GRID_PROGRAM_TOWER,
};

#define COLOR_TRANSPARENT 0x0c
#define COLOR_NULL RGB(COLOR_TRANSPARENT, COLOR_TRANSPARENT, COLOR_TRANSPARENT)


typedef char bool;
#define true (char)1
#define false (char)0
#define True true
#define False false



enum MSG {
    MSG_NULL,
	MSG_DRAWMAINWINDOW,
    
    MSG_INIT,
    MSG_PAINT,
    MSG_TIMEOUT,

	MSG_KEY_UP,
	MSG_KEY_DOWN,

	MSG_HANDLE_DOWN,
	MSG_HANDLE_UP,
    
    MSG_ESC,
    MSG_WORD,
    
};


#define VK_NULL 0
#define VK_UP 1
#define VK_LEFT 2
#define VK_DOWN 3
#define VK_RIGHT 4
#define VK_ESC 5
#define VK_ENTER 6

//键盘常量


#endif
