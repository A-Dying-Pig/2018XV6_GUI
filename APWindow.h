//
//  APWindow.h
//  
//
//  Created by Poo Lei on 2018/6/5.
//

#ifndef APWindow_h
#define APWindow_h
#include "APInclude.h"
#include "APObject.h"
#include "APPaint.h"

//Icon on the desktop
ABitmap grid_wall;
AHdc g_wall;
ABitmap grid_lake;
AHdc g_lake;
ABitmap grid_grass;
AHdc g_grass;
ABitmap grid_river;
AHdc g_river;
ABitmap grid_forest;
AHdc g_forest;
ABitmap grid_stone;
AHdc g_stone;
//ABitmap grid_mountain;
//AHdc g_mountain;
ABitmap grid_snake;
AHdc g_snake;
ABitmap grid_tower;
AHdc g_tower;

//start a program
AHwnd APCreateWindow(char * title,int is_map,int page);

//Grid_Mode Translate
void APGridPaint(AHwnd wnd);
bool APPreJudge(AHwnd hwnd, AMessage * msg);
bool APWndProc(AHwnd hwnd, AMessage msg);
void APWndExec(AHwnd hwnd, bool (*wndProc)(AHwnd, AMessage));
void APSendMessage(AHwnd hwnd, AMessage msg);
void updateword(AHwnd hwnd,char* str);


#endif /* APWindow_h */
