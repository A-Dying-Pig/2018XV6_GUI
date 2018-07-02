#include "APGui.h"
#include "types.h"
#include "x86.h"
#include "memlayout.h"
#include "defs.h"


ushort screenWidth = 0;
ushort screenHeight = 0;
uchar bitsPerPixel = 0;
static AColor *screenAddr = 0;
static AColor *screenBuf = 0;
static AColor *screenContent = 0;
struct spinlock screenLock;


AColor character_img[GRID_WIDTH][GRID_WIDTH];
AColor character_img2[GRID_WIDTH][GRID_WIDTH];


//index of character in the grid
int character_pre_x = 0, character_pre_y = 0;
int character_x = 1,character_y = 1;
//0 -- left 1--right
int direction = 1;


//character_move
void APDrawCharacter(int is_grid)
{
    //cprintf("in drawCharacter!\n");
    acquire(&screenLock);
    if (is_grid)
    {
        int off = (character_pre_y * GRID_WIDTH + WND_TITLE_HEIGHT)* screenWidth + character_pre_x * GRID_WIDTH;
        int size = sizeof(AColor) * GRID_WIDTH;
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            memmove(screenBuf + off, screenContent + off,size);
            memmove(screenAddr + off,screenContent + off,size);
            off += screenWidth;
        }
        off = (character_y * GRID_WIDTH + WND_TITLE_HEIGHT) * screenWidth + character_x * GRID_WIDTH;
        
            
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            for (int i = 0; i < GRID_WIDTH; i++)
            {
                AColor c;
                if (direction == 1) c = character_img[i][j];
                else if (direction == 0)  c = character_img2[i][j];
                
                if (c.r != COLOR_TRANSPARENT || c.g != COLOR_TRANSPARENT || c.b != COLOR_TRANSPARENT)
                {
                    screenBuf[off + i] = c;
                    screenAddr[off + i] = c;
                }
            }
            off += screenWidth;
        }
    }
    release(&screenLock);
}


AWndList wndList;

ATimerList timerList;

int timerListReady = 0;

void APCharacterInit(void)
{
    for (int j = 0; j < GRID_WIDTH; j++)
        for (int i = 0; i < GRID_WIDTH; i++)
        {
            character_img[i][j] = RGB(COLOR_TRANSPARENT,COLOR_TRANSPARENT,COLOR_TRANSPARENT);
            character_img2[i][j] = RGB(COLOR_TRANSPARENT,COLOR_TRANSPARENT,COLOR_TRANSPARENT);
        }
    //

    int line=0;
  
    for(int j=line;j<line+3;j++)
	for(int i=10;i<25;i++)
		character_img[i][j] = RGB(0xff,0x00,0x00);
    line=line+3;
    for(int j=line;j<line+3;j++)
        for(int i=5;i<40;i++)
            character_img[i][j] = RGB(0xff,0x00,0x00);

    line=line+3;

    for(int j=line;j<line+3;j++){
        for(int i=5;i<30;i++){
               if(i<15)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=15&&i<22)
			character_img[i][j] = RGB(249,236,236);
		else if(i>=22&&i<26)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=26&&i<30)
			character_img[i][j] = RGB(249,236,236);

        }}
line=line+3;
  for(int j=line;j<line+3;j++){
	for(int i=0;i<40;i++){
               if(i<5)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=5&&i<10)
			character_img[i][j] = RGB(249,236,236);
		else if(i>=10&&i<13)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=13&&i<22)
			character_img[i][j] = RGB(249,236,236);
		else if(i>=22&&i<26)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=26&&i<35)
			character_img[i][j] = RGB(249,236,236);
}}
line=line+3;
  for(int j=line;j<line+3;j++){
	for(int i=0;i<44;i++){
               if(i<5)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=5&&i<10)
			character_img[i][j] = RGB(249,236,236);
		else if(i>=10&&i<16)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=16&&i<26)
			character_img[i][j] = RGB(249,236,236);
		else if(i>=26&&i<30)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=30&&i<40)
			character_img[i][j] = RGB(249,236,236);
}}
line=line+3;
  for(int j=line;j<line+3;j++){
	for(int i=0;i<40;i++){
               if(i<10)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=10&&i<22)
			character_img[i][j] = RGB(249,236,236);
		else if(i>=22&&i<35)
			character_img[i][j] = RGB(128,64,0);
		
}}
line=line+3;
  for(int j=line;j<line+3;j++){
	for(int i=10;i<40;i++){
               if(i<30)
			character_img[i][j] = RGB(249,236,236);
		
		
}}
line=line+3;
  for(int j=line;j<line+3;j++){
	for(int i=5;i<40;i++){
               if(i<11)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=11&&i<14)
			character_img[i][j] = RGB(255,0,0);	
		else if(i>=14&&i<25)
			character_img[i][j] = RGB(128,64,0);
		
		
}}
line=line+3;
  for(int j=line;j<line+3;j++){
	for(int i=3;i<40;i++){
               if(i<11)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=11&&i<14)
			character_img[i][j] = RGB(255,0,0);
		else if(i>=14&&i<22)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=22&&i<25)
			character_img[i][j] = RGB(255,0,0);
		else if(i>=25&&i<35)
			character_img[i][j] = RGB(128,64,0);
        
    }}line=line+3;
  for(int j=line;j<line+3;j++){
	for(int i=0;i<40;i++){
               if(i<11)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=11&&i<25)
			character_img[i][j] = RGB(255,0,0);
		else if(i>=25&&i<40)
			character_img[i][j] = RGB(128,64,0);
}}
line =line +3;
for(int j=line;j<line+3;j++){
	for(int i=0;i<40;i++){
               if(i<5)
			character_img[i][j] = RGB(249,236,236);
		else if(i>=5&&i<8)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=8&&i<11)
			character_img[i][j] = RGB(255,0,0);
		else if(i>=11&&i<14)
			character_img[i][j] = RGB(249,236,236);
		else if(i>=14&&i<22)
			character_img[i][j] = RGB(255,0,0);
		else if(i>=22&&i<25)
			character_img[i][j] = RGB(249,236,236);
		else if(i>=25&&i<28)
			character_img[i][j] = RGB(255,0,0);
		else if(i>=28&&i<32)
			character_img[i][j] = RGB(128,64,0);
		else if(i>=32&&i<40)
			character_img[i][j] = RGB(249,236,236);
}}
line =line +3;
for(int j=line;j<line+3;j++){
	for(int i=0;i<40;i++){
               if(i<8)
			character_img[i][j] = RGB(249,236,236);
		else if(i>=8&&i<28)
			character_img[i][j] = RGB(255,0,0);
		else if(i>=28&&i<40)
			character_img[i][j] = RGB(249,236,236);

		
}}
line =line +3;
for(int j=line;j<line+3;j++){
	for(int i=0;i<40;i++){
               if(i<5)
			character_img[i][j] = RGB(249,236,236);
	
		else if(i>=5&&i<32)
			character_img[i][j] = RGB(255,0,0);
		
		else if(i>=32&&i<40)
			character_img[i][j] = RGB(249,236,236);

		
}}line =line +3;
for(int j=line;j<line+3;j++){
	for(int i=0;i<40;i++){
               if(i>=5&&i<14)
			character_img[i][j] = RGB(255,0,0);
		
		else if(i>=22&&i<32)
			character_img[i][j] = RGB(255,0,0);

		
}}
 line =line +3;
for(int j=line;j<line+3;j++){
	for(int i=0;i<40;i++){
               if(i>=2&&i<11)
			character_img[i][j] = RGB(128,64,0);
		
		else if(i>=25&&i<34)
			character_img[i][j] = RGB(128,64,0);

		
}}
line =line +3;
for(int j=line;j<line+3;j++){
	for(int i=0;i<40;i++){
               if(i<11)
			character_img[i][j] = RGB(128,64,0);
		
		else if(i>=25&&i<35)
			character_img[i][j] = RGB(128,64,0);

		
}}

   for(int j=0;j<GRID_WIDTH;j++)
   	for(int i=0;i<GRID_WIDTH;i++)
      		character_img2[GRID_WIDTH-1-i][j] = character_img[i][j];
}

void APGuiInit(void)
{
    screenAddr = (AColor *)(*((uint*)P2V(0x1028)));
    screenWidth = *((ushort *)P2V(0x1012));
    screenHeight = *((ushort *)P2V(0x1014));
    bitsPerPixel = *((uchar*)P2V(0x1019));
    screenBuf = screenAddr + screenWidth * screenHeight;
    screenContent = screenBuf + screenWidth * screenHeight;
    
    cprintf("screen addr : %x, screen width : %d, screen height : %d, bitsPerPixel: %d \n",
            screenAddr, screenWidth,screenHeight,bitsPerPixel);
    
    initlock(&screenLock,"sreenLock");
    APCharacterInit();
    APTimerListInit(&timerList);
    APWndListInit(&wndList);
}

//将左上角坐标为(x1,y1),右下角坐标为(x2,y2)的矩形区域从Buf绘制到屏幕上
void APBufPaint(int x1,int y1,int x2,int y2,int is_grid)
{
    acquire(&screenLock);
    x2 -= x1;
    x2 *= sizeof(AColor);
    int off = x1 + y1 * screenWidth;
    for (int y = y1 ; y <= y2; y++)
    {
        memmove(screenBuf + off , screenContent + off, x2);
        memmove(screenAddr + off, screenContent + off, x2);
        off += screenWidth;
    }
    
    if (is_grid)
    {
        
        if (x1 <= character_x * GRID_WIDTH + GRID_WIDTH && x2 >= character_x * GRID_WIDTH
            && y1 <= character_y * GRID_WIDTH + GRID_WIDTH + WND_TITLE_HEIGHT && y2 >= character_y * GRID_WIDTH + WND_TITLE_HEIGHT)
        {
            for (int j = 0; j < GRID_WIDTH ; j++)
            {
                off = (character_y * GRID_WIDTH + WND_TITLE_HEIGHT + j) * screenWidth + character_x * GRID_WIDTH;
                if (character_y * GRID_WIDTH + j < y1)
                    continue;
                if (character_y * GRID_WIDTH + j > y2)
                    break;
                for (int i = 0; i < GRID_WIDTH; i++)
                {
                    if (character_x * GRID_WIDTH + i < x1)
                        continue;
                    if (character_x * GRID_WIDTH + i > x2)
                        break;
                    
                    AColor c;
                    if (direction == 1) c = character_img[i][j];
                    else if (direction == 0)  c = character_img2[i][j];
                    
                    if (c.r != COLOR_TRANSPARENT || c.g!=COLOR_TRANSPARENT || c.b !=COLOR_TRANSPARENT)
                    {
                        screenBuf [off + i] = c;
                        screenAddr[off + i] = c;
                    }
                }
            }
        }
    }
    //cprintf("arbitrary set window color!\n");
    //memset(screenAddr, DEFAULT_WINDOW_COLOR, sizeof(AColor) * screenWidth * screenHeight);
    release(&screenLock);
}

//paintwindow: (hwnd,wx,wy,hdc,sx,sy,w,h,is_grid,pos_x,pos_y)
int sys_paintWindow(void)
{
    //cprintf("in paintWindow function:---- 1  \n");
    AHwnd hwnd = 0;
    AHdc hdc = 0;
    int wx,wy,sx,sy,w,h,is_grid,pos_x,pos_y;
    //从控制台获取数据，并检验值是否合法
    if (argstr(0, (char **)&hwnd) < 0 || argint(1, &wx) < 0 || argint(2, &wy) < 0
        || argstr(3, (char **)&hdc) < 0 || argint(4, &sx) < 0
        || argint(5, &sy) < 0 || argint(6, &w) < 0 || argint(7, &h) < 0
        || argint(8, &is_grid) < 0 ||argint(9, &pos_x) < 0 || argint(10, &pos_y) < 0)
        return -1;
    
    if (sx < 0 || sy < 0 || h <= 0 || w <= 0 || sx + w > hdc->size.cx || sy + h > hdc->size.cy)
        return 0;
    
    if (wx < 0 || wy < 0 || wx + w > screenWidth || wy + h > screenHeight)
        return 0;
    
    character_x = pos_x;
    character_y = pos_y;
    //wx,wy是window重绘左上角坐标
    //int id = hwnd ->id;
    //cprintf("in paintWindow function:-----2  \n");
    AColor *data = hdc->content;
    
    int j;
    for (int i = 0; i < h;i++)
    {
        if (wy + i < 0)
        {
            i = -wy - 1;
            continue;
        }
        else if (wy + i >= screenHeight)
            break;
        int off_x = (sy + i) * hdc->size.cx + sx;
        int screen_off_x = (wy + i) * screenWidth + wx;
        for (j = 0; j < w; ++j)
        {
            if (wx + j < 0)
            {
                j = -wx - 1;
                continue;
            }
            else if (wx + j >= screenWidth)
                break;
            
            AColor c = data[off_x + j];
            if (c.r != COLOR_TRANSPARENT || c.g != COLOR_TRANSPARENT || c.b != COLOR_TRANSPARENT )
                screenContent[screen_off_x + j] = c;
        }
    }
    w += wx - 1;
    h += wy - 1;
    if (wx < 0)
        wx = 0;
    if (wy < 0)
        wy = 0;
    if (h >= screenHeight)
        h = screenHeight - 1;
    if (w >= screenWidth)
        w = screenWidth - 1;
    //release(&videoLock);
    APBufPaint(wx, wy, w, h,is_grid);
    return 0;
}

int sys_changePosition(void)
{
    int x,y,d;
    if (argint(0, &x) < 0 || argint(1, &y) < 0 || argint(2, &d) < 0)
        return -1;
    
    //cprintf("in changePosition\n");
    character_pre_y = character_y;
    character_pre_x = character_x;
    character_x = x;
    character_y = y;
    if (d != 2)
        direction = d;
    APDrawCharacter(True);
    return 0;
}

int sys_sendMessage(void)
{
    int wndId = 0;
    AMessage * msg = 0;
    if (argint(0, &wndId) < 0 || argstr(1, (char**)&msg) < 0)
        return -1;
    
    //cprintf("in sys_sendMessage\n");
    
    sendMessage(wndId, msg);
    return 0;
}

int sys_registWindow(void)
{
    AHwnd hwnd = 0;
    if (argstr(0, (char **)&hwnd) < 0)
        return -1;
    APWndListAddToHead(&wndList, hwnd);
    return 0;
}

int sys_removeWindow(void)
{
    int id = 0;
    if (argint(0, &id) < 0)
        return -1;
    
    APTimerListRemoveWnd(&timerList, id);
    APWndListRemove(&wndList,id);
    APWndListMoveToHead(&wndList, 0);
    return 0;
}

int sys_getMessage(void)
{

    AHwnd hwnd = 0;
    if (argstr(0, (char **)&hwnd) < 0)
        return -1;
    int wndId = hwnd->id;
    //int pid = hwnd->pid;
    
    //cprintf("in function --- getMessage:WndId: %d\n",wndId);
    
    acquire(&wndList.data[wndId].lock);
    AMsgQueue * queue = &wndList.data[wndId].msgQueue;
    
    //cprintf("head:%d,tail:%d \n",queue->head,queue->tail);
    if (queue->head == queue->tail)
    {
        //cprintf("WND: %d is sleeping\n",wndId);
        //sleep((void *)pid,&wndList.data[wndId].lock);
    }
    if (wndList.data[wndId].hwnd->msg.type == MSG_NULL)
    {
      //  cprintf("poping msg!\n");
        wndList.data[wndId].hwnd->msg = APMsgQueueDeQueue(queue);
    }
    
    release(&wndList.data[wndId].lock);
    return 0;
}


void sendMessage(int wndId, AMessage *msg)
{
    //cprintf("sendMessage,Messgaetype:%d\n",msg->type);
    if (wndId == -1 || wndList.data[wndId].hwnd == 0)
        return;
    //cprintf("in send Message\n");
    //cprintf("send message: WndID:%d \n",wndId);
    AMsgQueue * queue = &wndList.data[wndId].msgQueue;
    msg->wndID = wndId;
    APMsgQueueEnQueue(queue, *msg);
    //cprintf("message has entered the queue\n",wndId);
    acquire(&wndList.data[wndId].lock);
    //cprintf("lock has acquired!\n");
    //wakeup((void *)wndList.data[wndId].hwnd->pid);
    release(&wndList.data[wndId].lock);
    //cprintf("Wnd %d has waken up!\n",wndId);
}

//------------------------------------------------------------------------------------
//WndList

//space--insert_position
void APWndListInit(AWndList * list)
{
    int i = 0;
    for (i = 0; i < MAX_WND_NUM; ++i)
    {
        list->data[i].hwnd = 0;
        list->data[i].prev = -1;
        list->data[i].next = i + 1;
        APMsgQueueInit(&list->data[i].msgQueue);
        initlock(&list->data[i].lock, "msglock");
    }
    list->data[i - 1].next = -1;
    initlock(&list->lock, "wndListLock");
    list->head = list->tail  = -1;
    list->desktop = 0;
    list->space = 0;
}

void APWndListAddToHead(AWndList * list, AHwnd hwnd)
{
    acquire(&list->lock);
    int p = list->space;
    if (p == -1)
    {
        cprintf("too much window\n");
        return;
    }
    list->space = list->data[list->space].next;
    list->data[p].hwnd = hwnd;
    
    hwnd->id = p;
    
    //desktop ---- id = 0
    list->data[p].next = list->head;
    list->data[p].prev = -1;
    if (list->head == -1)
        list->tail = p;
    else
        list->data[list->head].prev = p;
    
    list->head = p;
    //cprintf("the wndlist head is %d\n",p);
    release(&list->lock);
}

void APWndListMoveToHead(AWndList * list, int wndId)
{
    AMessage msg;
    msg.type = MSG_PAINT;
    sendMessage(wndId,&msg);
    if (wndId < 0)
        return;
    acquire(&list->lock);
    if (wndId != list->head)
    {
        list->data[list->data[wndId].prev].next = list->data[wndId].next;
        if (list->data[wndId].next == -1)
            list->tail = list->data[wndId].prev;
        else
            list->data[list->data[wndId].next].prev = list->data[wndId].prev;

        list->data[list->head].prev = wndId;
        list->data[wndId].prev = -1;
        list->data[wndId].next = list->head;
        list->head = wndId;
    }
    release(&list->lock);
}

void APWndListRemove(AWndList * list, int wndId)
{
    if (wndId < 0)
        return;
    acquire(&list->lock);
    if (wndId == list->head)
    {
        if (list->data[wndId].next == -1)
            list->head = list->tail = -1;
        else
        {
            list->head = list->data[list->head].next;
            list->data[list->head].prev = -1;
        }
    }
    else if (wndId == list->tail)
    {
        list->tail = list->data[list->tail].prev;
        list->data[list->tail].next = -1;
    }
    list->data[wndId].prev = -1;
    list->data[wndId].next = list->space;
    list->data[wndId].hwnd = 0;
    list->space = wndId;

    APMsgQueueInit(&list->data[wndId].msgQueue);
    
    release(&list->lock);
}

void APWndListDestroy(AWndList * list)
{
    acquire(&list->lock);
    release(&list->lock);
}



//------------------------------------------------------------------------------------
//Msg

//Msg Queue
//head = start, tail = end next

void APMsgQueueInit(AMsgQueue * queue)
{
    // as an array
    queue->head = queue->tail = 0;
}

void APMsgQueueEnQueue(AMsgQueue * queue, AMessage msg)
{
    if ((queue->tail + 1) % MESSAGE_QUEUE_SIZE == queue->head)
    {
        cprintf("Error! Message Queue is full\n");
        return;
    }
    
    switch (msg.type)
    {
        default:
            break;
    }
    //cprintf("MsgQueue-En-Queue:tail %d \n",queue->tail);
    queue->data[queue->tail] = msg;
    queue->tail = (queue->tail + 1) % MESSAGE_QUEUE_SIZE;
    //cprintf("MsgQueue-En-Queue:after add tail %d \n",queue->tail);
}

//弹出消息队列顶端
AMessage APMsgQueueDeQueue(AMsgQueue * queue)
{
    if (queue->head == queue->tail)
    {
        AMessage msg;
        msg.type = MSG_NULL;
        return msg;
    }
    int p = queue->head;
    queue->head = (queue->head + 1) % MESSAGE_QUEUE_SIZE;
    return queue->data[p];
}

//-----------------------------------------------------------------------------
//Timer
void TimerCount()
{
    if (!timerListReady)
        return;
    acquire(&timerList.lock);
    int p = timerList.head;
    while(p != -1)
    {
        timerList.data[p].count ++;
        if (timerList.data[p].count >= timerList.data[p].interval)
        {
            timerList.data[p].count = 0;
            AMessage msg;
            msg.type = MSG_TIMEOUT;
            sendMessage(timerList.data[p].wndId,&msg);
        }
        p = timerList.data[p].next;
    }
    release(&timerList.lock);
}


void APTimerListInit(ATimerList * list)
{
    int i;
    for (i = 0; i < MAX_TIMER_NUM; i++)
        list->data[i].next = i + 1;
    list->head = -1;
    list->space = 0;
    list->data[i].next = -1;
    initlock(&list->lock, "timerLock");
    timerListReady = 1;
}

void APTimerListAddToHead(ATimerList * list, int wndId, int id, int interval)
{
    acquire(&list->lock);
    int p = list->space;
    if (p == -1)
    {
        cprintf("Error! Too much Timer!\n");
        return;
    }
    list->space = list->data[p].next;
    list->data[p].next = list->head;
    list->head = p;
    list->data[p].wndId = wndId;
    list->data[p].id = id;
    list->data[p].interval = interval;
    list->data[p].count = 0;
    release(&list->lock);
    
}

void APTimerListRemoveWnd(ATimerList * list, int wndId)
{
    acquire(&list->lock);
    int p = list->head;
    int q = p;
    while (p != -1)
    {
        if (list->data[p].wndId == wndId)
        {
            if (p == list->head)
            {
                list->head = list->data[p].next;
                list->data[p].next = list->space;
                list->space = p;
                p = list->head;
                q = p;
            }
            else
            {
                list->data[q].next = list->data[p].next;
                list->data[p].next = list->space;
                list->space = p;
                p = list->data[q].next;
            }
        }
        else
        {
            q = p;
            p = list->data[p].next;
        }
    }
    release(&list->lock);
}

void APTimerListRemoveID(ATimerList * list, int wndId, int id)
{
    acquire(&list->lock);
    int p = list->head;
    int q = p;
    while (p != -1)
    {
        if (list->data[p].wndId == wndId && list->data[p].id == id)
        {
            if (p == list->head)
            {
                list->head = list->data[p].next;
                list->data[p].next = list->space;
                list->space = p;
                p = list->head;
                q = p;
            }
            else
            {
                list->data[q].next = list->data[p].next;
                list->data[p].next = list->space;
                list->space = p;
                p = list->data[q].next;
            }
        }
        else
        {
            q = p;
            p = list->data[p].next;
        }
    }
    release(&list->lock);
}

void sys_setupTimer(void)
{
    AHwnd hwnd;
    int id,interval;
    if (argstr(0, (char **)&hwnd) < 0 || argint(1, &id) < 0 || argint(2, &interval) < 0)
        return ;
    APTimerListAddToHead(&timerList,hwnd->id,id,interval/10);
}
void sys_deleteTimer(void)
{
    AHwnd hwnd;
    int id;
    if (argstr(0, (char **)&hwnd) < 0 || argint(1, &id) < 0)
        return ;
    APTimerListRemoveID(&timerList,hwnd->id,id);
}

int sys_getCurrentTime()
{
    uint t = 0;
    outb(0x70, 0x00);
    uchar d = inb(0x71);
    uchar n = (d >> 4) * 10 + (d & 0xf);
    t |= (n & 0xff);
    outb(0x70, 0x02);
    d = inb(0x71);
    n = (d >> 4) * 10 + (d & 0xf);
    t |= ((n & 0xff) << 8);
    outb(0x70, 0x04);
    d = inb(0x71);
    n = (d >> 4) * 10 + (d & 0xf);
    n = (n + 8) % 24;
    t |= (n << 16);
    return t;
}



