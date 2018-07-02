#ifndef APGUI_H_
#define APGUI_H_

#include "APObject.h"
#include "APInclude.h"

void APGuiInit(void);
void APCharacterInit(void);
void sendMessage(int wndId, struct AMessage *msg);
void APDrawCharacter(int is_grid);

//Window
void APWndListInit(AWndList * list);
void APWndListAddToHead(AWndList * list, AHwnd hwnd);
void APWndListAddToHead(AWndList * list, AHwnd hwnd);
void APWndListMoveToHead(AWndList * list, int wndId);
void APWndListRemove(AWndList * list, int wndId);
void APWndListDestroy(AWndList * list);


//Msg
void APMsgQueueInit(AMsgQueue * queue);
void APMsgQueueEnQueue(AMsgQueue * queue, AMessage msg);
AMessage APMsgQueueDeQueue(AMsgQueue * queue);

//Timer
//void setuptimer(AHwnd hwnd,int id, int interval);
//void deletetimer(AHwnd hwnd, int id);
void TimerCount();
void APTimerListInit(ATimerList * list);
//interval是所等的毫秒数
void APTimerListAddToHead(ATimerList * list, int wndId, int id, int interval);
void APTimerListRemoveWnd(ATimerList * list, int wndId);
void APTimerListRemoveID(ATimerList * list, int wndId, int id);





#endif
