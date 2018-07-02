//
//  APPaint.h
//  
//
//  Created by Poo Lei on 2018/6/6.
//

#ifndef APPaint_h
#define APPaint_h

#include "APObject.h"
#include "APInclude.h"

#define X_BIGGER -1
#define X_SMALLER -2
#define Y_BIGGER -3
#define Y_SMALLER -4

//ADc copy from one to the another
void APDcCopy(AHdc dst,int wx, int wy, AHdc src,int x,int y,int w,int h,AColor trans);

//draw bitmap
ABitmap APLoadBitmap (char * filename);
AHdc APCreateCompatibleDCFromBitmap(ABitmap bmp);

//set function
APen APSetPen(AHdc hdc, APen pen);
ABrush APSetBrush(AHdc hdc, ABrush brush);
AFont APSetFont(AHdc hdc,AFont font);

//drawing function
void APDrawPixel(AHdc hdc, int x, int y, AColor color);
void APDrawPoint(AHdc hdc, int x, int y);
void APDrawLine(AHdc hdc, int x1, int y1, int x2, int y2);
void APDrawRect(AHdc hdc, int x, int y, int w, int h);

//draw text
void APDrawText(AHdc hdc, char * str, int x, int y);

#define Alphabet_WIDTH 9
#define Alphabet_HEIGHT 18
#define Alphabet_NUMBER 96
extern unsigned char Alphabet[Alphabet_NUMBER - 1][Alphabet_HEIGHT][Alphabet_WIDTH];


#endif /* APPaint_h */
