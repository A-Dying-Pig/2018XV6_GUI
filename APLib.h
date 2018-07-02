//
//  APLib.h
//  
//
//  Created by Poo Lei on 2018/6/6.
//

#ifndef APLib_h
#define APLib_h

#include "types.h"
#include "user.h"



#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? -(a) : (a))

#define Pi 3.14159265

void sprintf(char * dst, char * fmt, ...);
int random(int);

#endif /* APLib_h */
