#ifndef APDESKTOP_H
#define APDESKTOP_H

#include "fcntl.h"
#include "types.h"
#include "user.h"
#include "stat.h"
#include "fs.h"
#include "APGui.h"
#include "APInclude.h"
#include "APObject.h"
#include "APPaint.h"
#include "APLib.h"
#include "APWindow.h"

void runApp(void * param);
//character_move
int judgeGridWalkable(int x, int y, AHwnd hwnd);

#endif
